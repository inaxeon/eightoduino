/*
 *   8OD - Arduino form factor i8086 based SBC
 *   Matthew Millman (tech.mattmillman.com)
 *
 *   DS18X20 Driver
 *
 *   This is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 2 of the License, or
 *   (at your option) any later version.
 *
 *   This software is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this software.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdint.h>
#include <stdbool.h>

#include "onewire.h"
#include "ds18x20.h"
#include "crc8.h"

#define OW_SEARCH_FIRST           0xFF
#define OW_PRESENCE_ERR           0xFF
#define OW_DATA_ERR               0xFE
#define OW_LAST_DEVICE            0x00

#define DS18S20_FAMILY_CODE       0x10
#define DS18B20_FAMILY_CODE       0x28
#define DS1822_FAMILY_CODE        0x22

#define DS18X20_READ_ROM          0x33
#define DS18X20_SP_SIZE           9
#define DS18X20_READ              0xBE
#define DS18X20_CONVERT_T         0x44

#define DS18B20_CONF_REG          4
#define DS18B20_9_BIT             0
#define DS18B20_10_BIT            (1 << 5)
#define DS18B20_11_BIT            (1 << 6)
#define DS18B20_12_BIT            ((1 << 6) | (1 << 5))
#define DS18B20_RES_MASK          ((1 << 6) | (1 << 5))
#define DS18B20_9_BIT_UNDF        ((1 << 0) | (1 << 1) | (1 << 2))
#define DS18B20_10_BIT_UNDF       ((1 << 0) | (1 << 1))
#define DS18B20_11_BIT_UNDF       ((1 << 0))
#define DS18B20_12_BIT_UNDF       0

#define DS18X20_INVALID_DECICELSIUS  2000

static bool ds18x20_read_scratchpad(uint8_t *id, uint8_t *sp, uint8_t n)
{
    uint8_t i;

#ifdef _DS18X20_SINGLE_DEV_PER_CHANNEL_
    if (!ow_select_channel(*id))
        return false;
#endif /* _DS18X20_SINGLE_DEV_PER_CHANNEL_ */

#ifdef _DS18X20_SINGLE_DEV_PER_CHANNEL_            
    if (!ow_command(DS18X20_READ, NULL))    
#else
    if (!ow_command(DS18X20_READ, id))    
#endif /* _DS18X20_SINGLE_DEV_PER_CHANNEL_ */
        return false;

    for (i = 0; i < n; i++)
    {
        if (!ow_read_byte(&sp[i]))
            return false;
    }

    if (crc8(sp, DS18X20_SP_SIZE))
        return false;

    return true;
}

/* Convert scratchpad data to physical value in unit decicelsius */
static int16_t ds18x20_raw_to_decicelsius(uint8_t familycode, uint8_t *sp)
{
    uint16_t measure;
    uint8_t  negative;
    int16_t  decicelsius;
    uint16_t fract;

    measure = sp[0] | (sp[1] << 8);

    if (familycode == DS18S20_FAMILY_CODE)
    {   /* 9 -> 12 bit if 18S20 */
        /* Extended measurements for DS18S20 contributed by Carsten Foss */
        measure &= (uint16_t)0xfffe;   /* Discard LSB, needed for later extended precicion calc */
        measure <<= 3;                 /* Convert to 12-bit, now degrees are in 1/16 degrees units */
        measure += (16 - sp[6]) - 4;   /* Add the compensation and remember to subtract 0.25 degree (4/16) */
    }

    /* Check for negative */
    if (measure & 0x8000)
    {
        negative = 1;       /* Mark negative */
        measure ^= 0xffff;  /* convert to positive => (twos complement)++ */
        measure++;
    }
    else
    {
        negative = 0;
    }

    /* Clear undefined bits for DS18B20 != 12bit resolution */
    if (familycode == DS18B20_FAMILY_CODE || familycode == DS1822_FAMILY_CODE)
    {
        switch(sp[DS18B20_CONF_REG] & DS18B20_RES_MASK)
        {
        case DS18B20_9_BIT:
            measure &= ~(DS18B20_9_BIT_UNDF);
            break;
        case DS18B20_10_BIT:
            measure &= ~(DS18B20_10_BIT_UNDF);
            break;
        case DS18B20_11_BIT:
            measure &= ~(DS18B20_11_BIT_UNDF);
            break;
        default:
            /* 12 bit - all bits valid */
            break;
        }
    }

    decicelsius = (measure >> 4);
    decicelsius *= 10;

    /* decicelsius += ((measure & 0x000F) * 640 + 512) / 1024;
     * 625/1000 = 640/1024
     */
    fract = (measure & 0x000F) * 640;
    if (!negative)
        fract += 512;
    fract /= 1024;
    decicelsius += fract;

    if (negative)
        decicelsius = -decicelsius;

    if (/* decicelsius == 850 || */ decicelsius < -550 || decicelsius > 1250)
        return DS18X20_INVALID_DECICELSIUS;
 
    return decicelsius;
}

bool ds18x20_read_decicelsius(uint8_t *id, int16_t *decicelsius)
{
    bool presense;
    int16_t ret;
    uint8_t sp[DS18X20_SP_SIZE];

    if (!ow_bus_reset(&presense) || !presense)
        return false;

    if (!ds18x20_read_scratchpad(id, sp, DS18X20_SP_SIZE))
        return false;

    ret = ds18x20_raw_to_decicelsius(id[0], sp);
    if (ret == DS18X20_INVALID_DECICELSIUS)
        return false;

    *decicelsius = ret;
    return true;
}

bool ds18x20_start_meas(uint8_t *id)
{
    bool presense;
    
#ifdef _DS18X20_SINGLE_DEV_PER_CHANNEL_
    if (!ow_select_channel(*id))
        return false;
#endif /* _DS18X20_SINGLE_DEV_PER_CHANNEL_ */

    if (!ow_bus_reset(&presense) || !presense)
        return false;

    if (ow_bus_idle())
    {   /* only send if bus is "idle" = high */
#ifdef _DS18X20_SINGLE_DEV_PER_CHANNEL_
        if (!ow_command(DS18X20_CONVERT_T, NULL))
#else
        if (!ow_command(DS18X20_CONVERT_T, id))
#endif /* _DS18X20_SINGLE_DEV_PER_CHANNEL_ */
            return false;
    }
    return true;
}

#ifndef _DS18X20_SINGLE_DEV_PER_CHANNEL_

bool ds18x20_find_sensor(uint8_t *diff, uint8_t *id)
{
    uint8_t go = 1;

    do
    {
        *diff = ow_rom_search(*diff, id);
        if (*diff == OW_PRESENCE_ERR || *diff == OW_DATA_ERR || *diff == OW_LAST_DEVICE)
        {
            go = 0;
        }
        else if (*diff == OW_COMMS_ERR)
        {
            return false;
        }
        else
        {
            if (id[0] == DS18B20_FAMILY_CODE || id[0] == DS18S20_FAMILY_CODE ||
                id[0] == DS1822_FAMILY_CODE)
            {
                go = 0;
            }
        }
    } while (go);

    return true;
}

bool ds18x20_search_sensors(uint8_t *count, uint8_t(*sensor_ids)[DS18X20_ROMCODE_SIZE])
{
    bool presense;
    uint8_t i;
    uint8_t id[DS18X20_ROMCODE_SIZE];
    uint8_t diff;
    
    *count = 0;
    
    if (!ow_bus_reset(&presense))
        return false;
    if (!presense)
        return true;
    
    diff = OW_SEARCH_FIRST;
    while (diff != OW_LAST_DEVICE && *count < MAX_SENSORS)
    {
        if (!ds18x20_find_sensor(&diff, id))
            return false;
        
        if (diff == OW_PRESENCE_ERR)
            break;
        if (diff == OW_DATA_ERR)
            break;
        for (i = 0; i < DS18X20_ROMCODE_SIZE; i++)
            sensor_ids[*count][i] = id[i];
        (*count)++;
    }

    return true;
}

#endif /* !_DS18X20_SINGLE_DEV_PER_CHANNEL_ */

#ifdef _DS18X20_SINGLE_DEV_PER_CHANNEL_

bool ds18x20_search_sensors(uint8_t *count, uint8_t(*sensor_ids)[DS18X20_ROMCODE_SIZE])
{
    bool presense;
    uint8_t i;
    uint8_t id;

    *count = 0;

    for (i = 0; (i < 8) && (*count < MAXSENSORS); i++)
    {
        if (!ow_select_channel(i))
            return false;
        
        if (!ow_bus_reset(&presense))
            return false;

        if (!presense)
            continue;

        if (!ow_write_byte(OW_READ_ROM))
            continue;

        if (!ow_read_byte(&id))
            return false;

        /* Throw away the rest of the ROM ID */
        if (!ow_bus_reset(&presense))
            return false;

        if (id == DS18B20_FAMILY_CODE || id == DS18S20_FAMILY_CODE ||
            id == DS1822_FAMILY_CODE)
        {
            /* Only store the channel number, because we won't be needing full IDs in this mode! */
            sensor_ids[*count][0] = i;
            (*count)++;
        }
    }

    return true;
}

#endif /* _DS18X20_SINGLE_DEV_PER_CHANNEL_ */
