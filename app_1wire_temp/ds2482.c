/*
 *   8OD - Arduino form factor i8086 based SBC
 *   Matthew Millman (tech.mattmillman.com)
 *
 *   DS2482 Driver
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

#include "ds2482.h"
#include "onewire.h"
#include "i2c.h"

#ifdef _OW_DS2482_

#define DS2482_WAIT_CYCLES              255

#define DS2482_CMD_RESET                0xF0    /* No param */
#define DS2482_CMD_SET_READ_PTR         0xE1    /* Param: DS2482_PTR_CODE_xxx */
#define DS2482_CMD_CHANNEL_SELECT       0xC3    /* Param: Channel byte - DS2482-800 only */
#define DS2482_CMD_WRITE_CONFIG         0xD2    /* Param: Config byte */
#define DS2482_CMD_1WIRE_RESET          0xB4    /* Param: None */
#define DS2482_CMD_1WIRE_SINGLE_BIT     0x87    /* Param: Bit byte (bit7) */
#define DS2482_CMD_1WIRE_WRITE_BYTE     0xA5    /* Param: Data byte */
#define DS2482_CMD_1WIRE_READ_BYTE      0x96    /* Param: None */

/* Note to read the byte, Set the ReadPtr to Data then read (any addr) */
#define DS2482_CMD_1WIRE_TRIPLET        0x78    /* Param: Dir byte (bit7) */
#define DS2482_CMD_1WIRE_TRIPLET_DIR    0x80

/* Values for DS2482_CMD_SET_READ_PTR */
#define DS2482_PTR_CODE_STATUS          0xF0
#define DS2482_PTR_CODE_DATA            0xE1
#define DS2482_PTR_CODE_CHANNEL         0xD2    /* DS2482-800 only */
#define DS2482_PTR_CODE_CONFIG          0xC3

/*
 * Configure Register bit definitions
 * The top 4 bits always read 0.
 * To write, the top nibble must be the 1's compl. of the low nibble.
 */
#define DS2482_REG_CFG_1WS              0x08    /* 1-wire speed */
#define DS2482_REG_CFG_SPU              0x04    /* strong pull-up */
#define DS2482_REG_CFG_PPM              0x02    /* presence pulse masking */
#define DS2482_REG_CFG_APU              0x01    /* active pull-up */

#define DS2482_REG_STATUS_1WB           0x01    /* busy */
#define DS2482_REG_STATUS_PPD           0x02    /* presense pulse detect */
#define DS2482_REG_STATUS_SD            0x04    /* short detect */
#define DS2482_REG_STATUS_SBR           0x20    /* single bit result */
#define DS2482_REG_STATUS_TSB           0x40    /* triple second bit */
#define DS2482_REG_STATUS_DIR           0x80    /* direction chosen */

#define DS2482_DEV_ADDR                 0x18

#ifdef _OW_DS2482_800_
static const uint8_t ds2482_chan_wr[8] =
    { 0xF0, 0xE1, 0xD2, 0xC3, 0xB4, 0xA5, 0x96, 0x87 };
#endif /* _OW_DS2482_800_ */

static uint8_t _g_devAddr;

static bool ds2482_reset(void);

bool ds2482_init(void)
{
    uint8_t cfg = DS2482_REG_CFG_APU;
    
    _g_devAddr = DS2482_DEV_ADDR;

    if (!ds2482_reset())
        return false;

    if (!i2c_write(_g_devAddr, DS2482_CMD_WRITE_CONFIG, (cfg) | (~cfg) << 4))
        return false;

    return true;
}

static bool ds2482_reset(void)
{
    uint8_t status;
    
    if (!i2c_write_byte(_g_devAddr, DS2482_CMD_RESET))
        return false;
    
    if (!i2c_read_byte(_g_devAddr, &status))
        return false;

    if ((status & 0xF7) != 0x10)
        return false;

    return true;
}

bool ds2482_bus_reset(bool *presense_detect)
{
    uint8_t status;

    *presense_detect = true;

    if (!i2c_write_byte(_g_devAddr, DS2482_CMD_1WIRE_RESET))
        return false;

    if (!i2c_await_flag(_g_devAddr, DS2482_REG_STATUS_1WB, &status, DS2482_WAIT_CYCLES))
        return false;

    /* Check for short condition */
    if (status & DS2482_REG_STATUS_SD)
        return false;

    /* Check for presence detect */
    if (!(status & DS2482_REG_STATUS_PPD))
        *presense_detect = false;

    return true;
}

bool ds2482_command(uint8_t command, uint8_t *id)
{
    uint8_t i;
    bool presense;

    if (!ds2482_bus_reset(&presense))
        return false;
    if (!presense)
        return false;

    if (id)
    {
        if (!ds2482_write_byte(OW_MATCH_ROM)) /* To a single device */
            return false;
        i = DS18X20_ROMCODE_SIZE;
        do
        {
            if (!ds2482_write_byte(*id))
                return false;
            id++;
        } while (--i);
    }
    else
    {
        if (!ds2482_write_byte(OW_SKIP_ROM))  /* To all devices */
            return false;
    }

    if (!ds2482_write_byte(command))
        return false;

    return true;
}

bool ds2482_read_byte(uint8_t *ret)
{
    uint8_t data;
    uint8_t status;

    if (!i2c_write_byte(_g_devAddr, DS2482_CMD_1WIRE_READ_BYTE))
        return false;

    if (!i2c_await_flag(_g_devAddr, DS2482_REG_STATUS_1WB, &status, DS2482_WAIT_CYCLES))
        return false;

    if (!i2c_write(_g_devAddr, DS2482_CMD_SET_READ_PTR, DS2482_PTR_CODE_DATA))
        return false;

    if (!i2c_read_byte(_g_devAddr, &data))
        return false;

    *ret = data;
    return true;
}

bool ds2482_write_byte(uint8_t data)
{
    uint8_t status;

    if (!i2c_write(_g_devAddr, DS2482_CMD_1WIRE_WRITE_BYTE, data))
        return false;

    if (!i2c_await_flag(_g_devAddr, DS2482_REG_STATUS_1WB, &status, DS2482_WAIT_CYCLES))
        return false;

    return true;
}

uint8_t ds2482_rom_search(uint8_t diff, uint8_t *id)
{
    uint8_t status;
    uint8_t i;
    uint8_t j;
    uint8_t next_diff;
    bool presense;

    if (!ds2482_bus_reset(&presense))
        return OW_COMMS_ERR;
    if (!presense)
        return OW_PRESENCE_ERR;            /* No device found. early exit. */
    if (!ds2482_write_byte(OW_SEARCH_ROM)) /* ROM search command */
        return OW_COMMS_ERR;

    next_diff = OW_LAST_DEVICE;            /* Unchanged on last device */

    i = DS18X20_ROMCODE_SIZE * 8;          /* 8 bytes */

    do
    {
        j = 8;                             /* 8 bits */
        do
        {
            uint8_t search_direction = 0x00;

            if (diff > i || (*id & 1) && diff != i) /* Use '1' on this pass */
                search_direction = DS2482_CMD_1WIRE_TRIPLET_DIR;

            if (!i2c_write(_g_devAddr, DS2482_CMD_1WIRE_TRIPLET, search_direction))
                return OW_COMMS_ERR;

            if (!i2c_await_flag(_g_devAddr, DS2482_REG_STATUS_1WB, &status, DS2482_WAIT_CYCLES))
                return OW_COMMS_ERR;

            if ((status & DS2482_REG_STATUS_SBR) && (status & DS2482_REG_STATUS_TSB))
                return OW_DATA_ERR;        /* Data error. Early exit. */

            if (!(status & DS2482_REG_STATUS_SBR) && !(status & DS2482_REG_STATUS_TSB))
            {
                if (diff > i ||            /* true if last result wasn't a discrepancy */ 
                  ((*id & 1) && diff != i) /* true when the the search has ended */)
                    next_diff = i;         /* Setup next pass to use '0' */
            }
            
            *id >>= 1;

            if (status & DS2482_REG_STATUS_DIR)
                *id |= 0x80;               /* Store bit */

            i--;
        } while (--j);
        id++;                              /* Next byte */
    } while (i);

    return next_diff;                      /* To continue search */
}

#ifdef _OW_DS2482_800_

bool ds2482_select_channel(uint8_t channel)
{
    if (channel >= 8)
        return false;
    
    if (!i2c_write(_g_devAddr, DS2482_CMD_CHANNEL_SELECT, ds2482_chan_wr[channel]))
        return false;
    
    return true;
}

#endif /* _OW_DS2482_800_ */

#endif /* _OW_DS2482_ */
