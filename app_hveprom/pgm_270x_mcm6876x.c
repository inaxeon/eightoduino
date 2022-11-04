
/*
 *   8OD - Arduino form factor i8086 based SBC
 *   Matthew Millman (tech.mattmillman.com/8od)
 *
 *   1702A/2704/2708/MCM68764/MCM68766/MCS48 EPROM Programmer
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

#include "project.h"

#include <stdint.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <stdbool.h>

#ifdef _M8OD
#include "sys/eod_io.h"
#include "sys/uart.h"
#include "sys/util.h"
#endif /* _M8OD */

#ifdef _MDUINO
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
#endif /* _MDUINO */

#include "iopins.h"
#include "usart_buffered.h"
#include "util.h"
#include "pgm_common.h"
#include "pgm_270x_mcm6876x.h"

#ifdef _M8OD

#ifdef _80D_5MHZ_
#define DELAY_WRITE_MCM6876X 430
#define DELAY_WRITE_270X 260
#define DELAY_POWER_WAIT 0x7FFF
#else
#define DELAY_WRITE_MCM6876X 870
#define DELAY_WRITE_270X 535
#define DELAY_POWER_WAIT 0xFFFF
#endif

#define pgm_270x_mcm6876x_delay_read() delay_ncycles(1)
#define pgm_270x_mcm6876x_delay_ad_setup() delay_ncycles(1)
#define pgm_270x_mcm6876x_delay_ad_hold() delay_ncycles(1)
#define pgm_270x_mcm6876x_delay_write_mcm6876x() delay_ncycles(DELAY_WRITE_MCM6876X)
#define pgm_270x_mcm6876x_delay_write_270x() delay_ncycles(DELAY_WRITE_270X)
#define pgm_270x_mcm6876x_wr_enable() cpld_write(CTRL_PORT, MCMX_270X_WR, MCMX_270X_WR)
#define pgm_270x_mcm6876x_wr_disable() cpld_write(CTRL_PORT, MCMX_270X_WR, 0)
#define pgm_270x_mcm6876x_rd_enable() cpld_write(CTRL_PORT, MCMX_270X_RD, MCMX_270X_RD)
#define pgm_270x_mcm6876x_rd_disable() cpld_write(CTRL_PORT, MCMX_270X_RD, 0)
#define pgm_270x_mcm6876x_pe_enable() cpld_write(CTRL_PORT, MCMX_270X_PE, MCMX_270X_PE)
#define pgm_270x_mcm6876x_pe_disable() cpld_write(CTRL_PORT, MCMX_270X_PE, 0)

#endif /* _M8OD */

#ifdef _MDUINO

#define pgm_270x_mcm6876x_delay_read() _delay_us(1)
#define pgm_270x_mcm6876x_delay_ad_setup() _delay_us(5)
#define pgm_270x_mcm6876x_delay_ad_hold() _delay_us(5)
#define pgm_270x_mcm6876x_delay_write_mcm6876x() _delay_ms(2)
#define pgm_270x_mcm6876x_delay_write_270x() _delay_ms(1)
#define pgm_270x_mcm6876x_wr_enable()  MCMX_270X_WR_PORT |= _BV(MCMX_270X_WR)
#define pgm_270x_mcm6876x_wr_disable() MCMX_270X_WR_PORT &= ~_BV(MCMX_270X_WR)
#define pgm_270x_mcm6876x_rd_enable()  MCMX_270X_RD_PORT |= _BV(MCMX_270X_RD)
#define pgm_270x_mcm6876x_rd_disable() MCMX_270X_RD_PORT &= ~_BV(MCMX_270X_RD)
#define pgm_270x_mcm6876x_pe_enable()  MCMX_270X_PE_PORT |= _BV(MCMX_270X_PE)
#define pgm_270x_mcm6876x_pe_disable() MCMX_270X_PE_PORT &= ~_BV(MCMX_270X_PE)

#endif /* _MDUINO */

#define TEST_270X_MCM6876X_PON    1
#define TEST_270X_MCM6876X_RD     2
#define TEST_270X_MCM6876X_WR     3
#define TEST_270X_MCM6876X_PE     4
#define TEST_270X_MCM6876X_AA     5
#define TEST_270X_MCM6876X_55     6
#define TEST_270X_MCM6876X_DATA   7

static uint8_t _g_maxPerByteWrites;
static uint8_t _g_useHts;
static uint8_t _g_extraWrites;
static uint8_t _g_maxRetries;
static uint32_t _g_totalWrites;
static uint16_t _g_devSize;
static uint16_t _g_offset;
static uint8_t _g_shieldType;
static int8_t _g_devType;

void pgm_270x_mcm6876x_tms2716_addr_fudge(uint16_t addr);

void pgm_270x_mcm6876x_init(uint8_t shield_type)
{
    _g_maxPerByteWrites = 0;
    _g_totalWrites = 0;
    _g_maxRetries = 0;
    _g_devSize = 0;
    _g_devType = -1;
    _g_shieldType = shield_type;

#ifdef _M8OD
    cpld_write(CTRL_PORT,
        (MCMX_270X_DEVSEL | MCMX_270X_NC_0 | MCMX_270X_NC_1 | MCMX_270X_NC_2 | MCMX_270X_WR | MCMX_270X_RD | MCMX_270X_PE | MCMX_270X_PON),
        0
    );
    // DEVSEL + NC's as inputs
    cpld_write(CTRL_TRIS,
        (MCMX_270X_DEVSEL | MCMX_270X_NC_0 | MCMX_270X_NC_1 | MCMX_270X_NC_2 | MCMX_270X_WR | MCMX_270X_RD | MCMX_270X_PE | MCMX_270X_PON),
        (MCMX_270X_DEVSEL | MCMX_270X_NC_0 | MCMX_270X_NC_1 | MCMX_270X_NC_2)
    );
#endif /* _M8OD */

#ifdef _MDUINO
    MCMX_270X_WR_PORT &= ~_BV(MCMX_270X_WR);
    MCMX_270X_RD_PORT &= ~_BV(MCMX_270X_RD);
    MCMX_270X_PE_PORT &= ~_BV(MCMX_270X_PE);
    MCMX_270X_PON_PORT &= ~_BV(MCMX_270X_PON);

    MCMX_270X_DEVSEL_DDR &= ~_BV(MCMX_270X_DEVSEL); // input
    MCMX_270X_NC_0_DDR &= ~_BV(MCMX_270X_NC_0); // input
    MCMX_270X_NC_1_DDR &= ~_BV(MCMX_270X_NC_1); // input
    MCMX_270X_NC_2_DDR &= ~_BV(MCMX_270X_NC_2); // input
    MCMX_270X_WR_DDR |= _BV(MCMX_270X_WR); // output
    MCMX_270X_RD_DDR |= _BV(MCMX_270X_RD); // output
    MCMX_270X_PE_DDR |= _BV(MCMX_270X_PE); // output
    MCMX_270X_PON_DDR |= _BV(MCMX_270X_PON); // output
    MCMX_270X_NC_3_DDR &= ~_BV(MCMX_270X_NC_3); // input
#endif /* _MDUINO */

#ifdef _DEBUG
    printf("pgm_270x_mcm6876x_io_init(): completed\r\n");
#endif /* _DEBUG */
}

void pgm_270x_mcm6876x_set_params(uint8_t dev_type, uint16_t dev_size, uint8_t max_retries)
{
    _g_maxRetries = max_retries;
    _g_devSize = dev_size;
    _g_devType = dev_type;

    _g_offset = 0;
    _g_maxPerByteWrites = 0;
    _g_totalWrites = 0;

#ifdef _DEBUG
    //printf("pgm_270x_mcm6876x_set_params(): completed\r\n");
#endif /* _DEBUG */
}

bool pgm_270x_mcm6876x_check_switch(uint8_t dev_type)
{
    if (_g_shieldType == SHIELD_TYPE_270X_MCM6876X_V1)
    {
#ifdef _M8OD
        if ((cpld_read(CTRL_PORT) & MCMX_270X_DEVSEL) == 0)
        {
            if (dev_type == DEV_C2704 || dev_type == DEV_C2708 || dev_type == DEV_TMS2716)
                return true;
        }
        if ((cpld_read(CTRL_PORT) & MCMX_270X_DEVSEL) == MCMX_270X_DEVSEL)
        {
            if (dev_type == DEV_MCM6876X)
                return true;
        }
#endif /* _M8OD */

#ifdef _MDUINO
        if ((MCMX_270X_DEVSEL_PIN & _BV(MCMX_270X_DEVSEL)) == 0)
        {
            if (dev_type == DEV_C2704 || dev_type == DEV_C2708 || dev_type == DEV_TMS2716)
                return true;
        }
        if ((MCMX_270X_DEVSEL_PIN & _BV(MCMX_270X_DEVSEL)) == _BV(MCMX_270X_DEVSEL))
        {
            if (dev_type == DEV_MCM6876X)
                return true;
        }
#endif /* _MDUINO */
    }

#ifdef _MDUINO
    if (_g_shieldType == SHIELD_TYPE_270X_MCM6876X_V2)
    {
        // The V2 shield has a completely different mechanism of detecting the switch position.
        // Instead it is possible observe the state of A11 when tri-stated to detect it.
        // It's not as clean as the previous solution but it saves money on the BOM.
        ADDRESS_11_DDR &= ~_BV(ADDRESS_11);

        _delay_us(1);

        if ((ADDRESS_11_PIN & _BV(ADDRESS_11)) == _BV(ADDRESS_11))
        {
            if (dev_type == DEV_C2704 || dev_type == DEV_C2708 || dev_type == DEV_TMS2716)
                return true;
        }
        if ((ADDRESS_11_PIN & _BV(ADDRESS_11)) == 0)
        {
            if (dev_type == DEV_MCM6876X)
                return true;
        }

        ADDRESS_11_DDR |= _BV(ADDRESS_11);
    }
#endif /* _MDUINO */

    return false;
}

void pgm_270x_mcm6876x_power_on()
{
#ifdef _M8OD
    cpld_write(CTRL_PORT, MCMX_270X_PON, MCMX_270X_PON);
    delay_ncycles(DELAY_POWER_WAIT);
#endif /* _M8OD */

#ifdef _MDUINO
    MCMX_270X_PON_PORT |= _BV(MCMX_270X_PON);
    _delay_ms(100);
#endif /* _MDUINO */
}

void pgm_270x_mcm6876x_reset(void)
{
    pgm_270x_mcm6876x_pe_disable();
    pgm_270x_mcm6876x_rd_disable();
    pgm_270x_mcm6876x_wr_disable();

#ifdef _M8OD
    delay_ncycles(DELAY_POWER_WAIT);
    cpld_write(CTRL_PORT, MCMX_270X_PON, 0); /* Power off */
#endif /* _M8OD */

#ifdef _MDUINO
    _delay_ms(100);
    MCMX_270X_PON_PORT &= ~_BV(MCMX_270X_PON);
#endif /* _MDUINO */

    pgm_dir_in();
    cmd_respond(CMD_DEV_RESET, ERR_OK);
}

void pgm_270x_mcm6876x_write_chunk(void)
{
    uint8_t chunk[WRITE_CHUNK_SIZE];
    uint8_t attempt;
    int16_t remaining = (_g_devSize - _g_offset);
    uint8_t i;
    uint16_t thisChunk = remaining > WRITE_CHUNK_SIZE ? WRITE_CHUNK_SIZE : remaining;

#ifdef _DEBUG
    printf("pgm_270x_mcm6876x_write_chunk() thisChunk=%d remaining=%d _g_offset=%d\r\n", thisChunk, remaining, _g_offset);
#endif /* _DEBUG */

    /* The host is going to shove all of the data in at once, so we have to buffer it */
    for (i = 0; i < thisChunk; i++)
        chunk[i] = host_read8();

    /* Now get writing it */
    for (i = 0; i < thisChunk; i++)
    {
        uint8_t verified = 0;
        uint8_t stopat = _g_useHts ? _g_maxRetries : 1;
        pgm_270x_mcm6876x_tms2716_addr_fudge(_g_offset + i);
            
        for (attempt = 1; attempt <= stopat; attempt++)
        {
            uint8_t data;
            uint8_t temp = chunk[i];

            /* Present data */
            pgm_270x_mcm6876x_pe_enable();
            pgm_270x_mcm6876x_delay_read();
            pgm_dir_out();
            pgm_write_data(temp);

            pgm_270x_mcm6876x_delay_ad_setup();

            /* Pulse Vpp */
            pgm_270x_mcm6876x_wr_enable();
            
            if (_g_devType == DEV_MCM6876X)
                pgm_270x_mcm6876x_delay_write_mcm6876x(); /* 2ms */
            else
                pgm_270x_mcm6876x_delay_write_270x(); /* 1ms */

            pgm_270x_mcm6876x_wr_disable();
            pgm_270x_mcm6876x_delay_ad_hold();

            pgm_dir_in();
            pgm_270x_mcm6876x_pe_disable();

            if (_g_useHts)
            {
                /* Read back data */
                pgm_270x_mcm6876x_delay_read();
                pgm_270x_mcm6876x_rd_enable();
                pgm_270x_mcm6876x_delay_read();
                data = pgm_read_data();
                pgm_270x_mcm6876x_rd_disable();

#ifdef _DEBUG
                printf("pgm_270x_mcm6876x_write_chunk() data=0x%02X chunk[i]=0x%02X attempt=%d\r\n", data, chunk[i], attempt);
#endif /* _DEBUG */

                if (data == chunk[i] && verified == 0)
                {
                    verified = 1;
                    stopat = attempt + _g_extraWrites;
#ifdef _DEBUG
                    printf("pgm_270x_mcm6876x_write_chunk() data verified. Setting stopat to %d\r\n", stopat);
#endif /* _DEBUG */
                }
            }
            else
            {
                verified = 1; /* 270x write strategy does not use inline verify, so just set this to '1' */
            }
        }

        if (!verified)
        {
            cmd_respond(CMD_WRITE_CHUNK, ERR_MAX_RETRIES);
            return;
        }

        _g_maxPerByteWrites = attempt > _g_maxPerByteWrites ? attempt : _g_maxPerByteWrites;
        _g_totalWrites += attempt;
    }

    _g_offset += thisChunk;

    if (_g_offset == _g_devSize)
    {
        cmd_respond(CMD_WRITE_CHUNK, ERR_COMPLETE);
        host_write8(_g_maxPerByteWrites);
        host_write32(_g_devType == DEV_MCM6876X ? _g_totalWrites : 0);
    }
    else
    {
        cmd_respond(CMD_WRITE_CHUNK, ERR_OK);
    }
}

void pgm_270x_mcm6876x_read_chunk(void)
{
    int16_t remaining = (_g_devSize - _g_offset);
    uint8_t i;
    int thisChunk = remaining > READ_CHUNK_SIZE ? READ_CHUNK_SIZE : remaining;

    cmd_respond(CMD_READ_CHUNK, (_g_offset + thisChunk) == _g_devSize ? ERR_COMPLETE : ERR_OK);

#ifdef _DEBUG
    printf("pgm_270x_mcm6876x_read_chunk() thisChunk=%d remaining=%d _g_offset=%d\r\n", thisChunk, remaining, _g_offset);
#endif /* _DEBUG */

    for (i = 0; i < thisChunk; i++)
    {
        pgm_270x_mcm6876x_tms2716_addr_fudge(_g_offset + i);

        /* Read data */
        pgm_270x_mcm6876x_delay_read();
        pgm_270x_mcm6876x_rd_enable();
        pgm_270x_mcm6876x_delay_read();
        host_write8(pgm_read_data());
        pgm_270x_mcm6876x_rd_disable();
        pgm_270x_mcm6876x_delay_read();
    }

    _g_offset += thisChunk;
}

void pgm_270x_mcm6876x_blank_check(void)
{
    uint16_t offset = 0;
    uint8_t data;

    while (offset < _g_devSize)
    {
        pgm_270x_mcm6876x_tms2716_addr_fudge(offset);
        pgm_270x_mcm6876x_delay_read();
        pgm_270x_mcm6876x_rd_enable();
        pgm_270x_mcm6876x_delay_read();
        data = pgm_read_data();
        pgm_270x_mcm6876x_rd_disable();
        pgm_270x_mcm6876x_delay_read();

        if (data != 0xFF)
            break;

        offset++;
    }

    if (offset == _g_devSize)
    {
        cmd_respond(CMD_BLANK_CHECK, ERR_COMPLETE);
    }
    else
    {
        cmd_respond(CMD_BLANK_CHECK, ERR_NOT_BLANK);
        host_write16(offset);
        host_write8(data);
    }
}

void pgm_270x_mcm6876x_start_write(void)
{
    _g_useHts = host_read8();
    _g_extraWrites = host_read8();

#ifdef _DEBUG
    printf("pgm_270x_mcm6876x_start_write() _g_useHts=%d _g_extraWrites=%d\r\n", _g_useHts, _g_extraWrites);
#endif /* _DEBUG */

    pgm_270x_mcm6876x_power_on();

    cmd_respond(CMD_START_WRITE, ERR_OK);
}

void pgm_270x_mcm6876x_start_read(void)
{
#ifdef _DEBUG
    printf("pgm_270x_mcm6876x_start_read()\r\n");
#endif /* _DEBUG */

    pgm_270x_mcm6876x_power_on();

    cmd_respond(CMD_START_READ, ERR_OK);
}

void pgm_270x_mcm6876x_start_blank_check(void)
{
#ifdef _DEBUG
    printf("pgm_270x_mcm6876x_start_blank_check()\r\n");
#endif /* _DEBUG */

    pgm_270x_mcm6876x_power_on();

    cmd_respond(CMD_START_BLANK_CHECK, ERR_OK);
}

void pgm_270x_mcm6876x_test(void)
{
    uint8_t test_num = host_read8();

    switch (test_num)
    {
        case TEST_270X_MCM6876X_PON:
            pgm_270x_mcm6876x_power_on();
            break;
        case TEST_270X_MCM6876X_RD:
            pgm_270x_mcm6876x_power_on();
            pgm_270x_mcm6876x_rd_enable();
            break;
        case TEST_270X_MCM6876X_WR:
            pgm_270x_mcm6876x_power_on();
            pgm_270x_mcm6876x_wr_enable();
            break;
        case TEST_270X_MCM6876X_PE:
            pgm_270x_mcm6876x_power_on();
            pgm_270x_mcm6876x_pe_enable();
            break;
        case TEST_270X_MCM6876X_AA:
            pgm_270x_mcm6876x_power_on();
            pgm_dir_out();
            pgm_write_data(0xAA);
            pgm_write_address(0xAAA);
            break;
        case TEST_270X_MCM6876X_55:
            pgm_270x_mcm6876x_power_on();
            pgm_dir_out();
            pgm_write_data(0x55);
            pgm_write_address(0x1555);
            break;
        case TEST_270X_MCM6876X_DATA:
            pgm_270x_mcm6876x_power_on();
            break;
        default:
            cmd_respond(ERR_INVALID_CMD, ERR_OK);
            return;
    }

    cmd_respond(CMD_TEST, ERR_OK);
}

void pgm_270x_mcm6876x_test_read(void)
{
    cmd_respond(CMD_TEST_READ, ERR_OK);
    host_write8(pgm_read_data());
}

void pgm_270x_mcm6876x_tms2716_addr_fudge(uint16_t addr)
{
    pgm_write_address(addr); /* Output address */
}

