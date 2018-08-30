/*
 *   8OD - Arduino form factor i8086 based SBC
 *   Matthew Millman (tech.mattmillman.com)
 *
 *   PCF8584 I2C Master driver
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

#include "eod_io.h"
#include "eod_map.h"
#include "i2c.h"
#include "util.h"

#define PCF8584_SX      (I2C_BASE + 0)
#define PCF8584_S1      (I2C_BASE + 1)

/* S1 Write */
#define S1_PIN          (1 << 7)
#define S1_ESO          (1 << 6)
#define S1_ENI          (1 << 3)
#define S1_STA          (1 << 2)
#define S1_STO          (1 << 1)
#define S1_ACK          (1 << 0)
#define S1_ESMSK        ((1 << 5) | (1 << 4))
/* ESO = 0 */
#define S1_S0SEL        0
#define S1_S3SEL        (1 << 4)
#define S1_S2SEL        (1 << 5)
/* ESO = 1 */
#define S1_DATASEL      0

/* S1 Read */
#define S1_STS          (1 << 5)
#define S1_BER          (1 << 4)
#define S1_LRB          (1 << 3)
#define S1_AAS          (1 << 2)
#define S1_LAB          (1 << 1)
#define S1_BB           (1 << 0)

void i2c_init(uint8_t iclkdiv, uint8_t oclkdiv)
{
    /* PCF8584 Intel/Motorola bus selection is done in the
     * bootrom by the master reset handler (cstrt086.asm)
     */

    /* Mandatory: Setup own address */
    outp(PCF8584_S1, S1_PIN | S1_S0SEL);
    outp(PCF8584_SX, 0x01);

    /* Setup clock. See i2c.h for more detail. */
    outp(PCF8584_S1, S1_PIN | S1_S2SEL);
    outp(PCF8584_SX, iclkdiv | oclkdiv);

    /* Enter operational mode */
    outp(PCF8584_S1, S1_PIN | S1_ESO | S1_DATASEL | S1_ACK);
}

bool i2c_read_byte(uint8_t devaddr, uint8_t *data)
{
    uint8_t s1reg;
    bool ret = true;

    /* Load slave address */
    outp(PCF8584_SX, (devaddr << 1) | 0x01);

    /* Wait till bus is free */
    while (!(inp(PCF8584_S1) & S1_BB));

    /* Send it */
    outp(PCF8584_S1, S1_PIN | S1_ESO | S1_DATASEL | S1_STA | S1_ACK);

    while (((s1reg = inp(PCF8584_S1)) & S1_PIN));

    if ((s1reg & S1_LRB) == S1_LRB)
    {
        ret = false;
        goto out;
    }

    outp(PCF8584_S1, S1_ESO);
    inp(PCF8584_SX); /* Dummy read */

    while (((s1reg = inp(PCF8584_S1)) & S1_PIN));

    /* Stop condition */
out:
    outp(PCF8584_S1, S1_PIN | S1_ESO | S1_DATASEL | S1_STO | S1_ACK);
    *data = inp(PCF8584_SX);
    return ret;
}

bool i2c_write_byte(uint8_t devaddr, uint8_t data)
{
    uint8_t s1reg;
    bool ret = true;

    /* Wait till bus is free */
    while (!(inp(PCF8584_S1) & S1_BB));

    /* Load slave address */
    outp(PCF8584_SX, devaddr << 1);

    /* Send it */
    outp(PCF8584_S1, S1_PIN | S1_ESO | S1_DATASEL | S1_STA | S1_ACK);
    
    while (((s1reg = inp(PCF8584_S1)) & S1_PIN));

    if ((s1reg & S1_LRB) == S1_LRB)
    {
        ret = false;
        goto out;
    }

    outp(PCF8584_SX, data);

    while (((s1reg = inp(PCF8584_S1)) & S1_PIN));

    if ((s1reg & S1_LRB) == S1_LRB)
    {
        ret = false;
        goto out;
    }

    /* Stop condition */
out:
    outp(PCF8584_S1, S1_PIN | S1_ESO | S1_DATASEL | S1_STO | S1_ACK);
    return ret;
}

bool i2c_write(uint8_t devaddr, uint8_t reg, uint8_t data)
{
    uint8_t s1reg;
    bool ret = true;

    /* Wait till bus is free */
    while (!(inp(PCF8584_S1) & S1_BB));

    /* Load slave address */
    outp(PCF8584_SX, devaddr << 1);
    
    /* Send it */
    outp(PCF8584_S1, S1_PIN | S1_ESO | S1_DATASEL | S1_STA | S1_ACK);

    while (((s1reg = inp(PCF8584_S1)) & S1_PIN));

    if ((s1reg & S1_LRB) == S1_LRB)
    {
        ret = false;
        goto out;
    }

    outp(PCF8584_SX, reg);

    while (((s1reg = inp(PCF8584_S1)) & S1_PIN));

    if ((s1reg & S1_LRB) == S1_LRB)
    {
        ret = false;
        goto out;
    }

    outp(PCF8584_SX, data);

    while (((s1reg = inp(PCF8584_S1)) & S1_PIN));

    if ((s1reg & S1_LRB) == S1_LRB)
    {
        ret = false;
        goto out;
    }

    /* Stop condition */
out:
    outp(PCF8584_S1, S1_PIN | S1_ESO | S1_DATASEL | S1_STO | S1_ACK);
    return ret;
}


bool i2c_write_buf(uint8_t devaddr, uint8_t reg, uint8_t *data, int len)
{
    return false;
}

bool i2c_read(uint8_t devaddr, uint8_t reg, uint8_t *data)
{
    uint8_t s1reg;
    bool ret = true;

    if (!i2c_write_byte(devaddr, reg))
        return false;

    /* Wait till bus is free */
    while (!(inp(PCF8584_S1) & S1_BB));

    /* Load slave address */
    outp(PCF8584_SX, (devaddr << 1) | 0x01);

    /* Send it */
    outp(PCF8584_S1, S1_PIN | S1_ESO | S1_DATASEL | S1_STA | S1_ACK);

    while (((s1reg = inp(PCF8584_S1)) & S1_PIN));

    if ((s1reg & S1_LRB) == S1_LRB)
    {
        ret = false;
        goto out;
    }

    outp(PCF8584_S1, S1_ESO);
    inp(PCF8584_SX); /* Dummy read */

    while (((s1reg = inp(PCF8584_S1)) & S1_PIN));

    if ((s1reg & S1_LRB) == S1_LRB)
    {
        ret = false;
        goto out;
    }

    /* Stop condition */
out:
    outp(PCF8584_S1, S1_PIN | S1_ESO | S1_DATASEL | S1_STO | S1_ACK);
    *data = inp(PCF8584_SX);
    return ret;
}

bool i2c_read_buf(uint8_t devaddr, uint8_t reg, uint8_t *data, int len)
{
    uint8_t s1reg;
    int ret = 1;
    int i;

    if (!i2c_write_byte(devaddr, reg))
        return false;

    /* Load slave address */
    outp(PCF8584_SX, (devaddr << 1) | 0x01);

    /* Wait till bus is free */
    while (!(inp(PCF8584_S1) & S1_BB));

    /* Send it */
    outp(PCF8584_S1, S1_PIN | S1_ESO | S1_DATASEL | S1_STA | S1_ACK);

    for (i = 0; i <= len; i++)
    {
        while (((s1reg = inp(PCF8584_S1)) & S1_PIN));

        if (((s1reg & S1_LRB) == S1_LRB) && (i != len))
        {
            outp(PCF8584_S1, S1_PIN | S1_ESO | S1_DATASEL | S1_STO | S1_ACK);
            return false;
        }

        if (i == (len - 1))
            outp(PCF8584_S1, S1_ESO);
        else if (i == len)
            outp(PCF8584_S1, S1_PIN | S1_ESO | S1_DATASEL | S1_STO | S1_ACK);

        if (i)
            data[i - 1] = inp(PCF8584_SX);
        else
            inp(PCF8584_SX);

    }

    return true;
}


bool i2c_await_flag(uint8_t addr, uint8_t mask, uint8_t *status, uint8_t attempts)
{
    uint8_t s1reg;
    uint8_t s0reg;
    bool ret = true;
    int i;

    /* Load slave address */
    outp(PCF8584_SX, (addr << 1) | 0x01);

    /* Wait till bus is free */
    while (!(inp(PCF8584_S1) & S1_BB));
    
    /* Send it */
    outp(PCF8584_S1, S1_PIN | S1_ESO | S1_DATASEL | S1_STA | S1_ACK);

    for (i = 0; i <= attempts; i++)
    {
        while (((s1reg = inp(PCF8584_S1)) & S1_PIN));

        if (((s1reg & S1_LRB) == S1_LRB) && (i != attempts))
        {
            ret = false;
            goto out;
        }

        if (i)
        {
            s0reg = inp(PCF8584_SX);
            if (!(s0reg & mask))
                break;
        }
        else
        {
            inp(PCF8584_SX); /* Dummy read */
        }
    }

    outp(PCF8584_S1, S1_ESO);
    s0reg = inp(PCF8584_SX);
    while ((inp(PCF8584_S1)) & S1_PIN);

out:
    outp(PCF8584_S1, S1_PIN | S1_ESO | S1_DATASEL | S1_STO | S1_ACK);
    s0reg = inp(PCF8584_SX);
    *status = s0reg;
    return !(s0reg & mask);
}
