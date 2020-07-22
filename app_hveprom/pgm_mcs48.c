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
#include "pgm_mcs48.h"

void pcm_mcs48_init(void)
{
    _g_maxPerByteWrites = 0;
    _g_totalWrites = 0;
    _g_maxRetries = 0;
    _g_devSize = 0;
    _g_devType = -1;

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
    printf("pcm_mcs48_io_init(): completed\r\n");
#endif /* _DEBUG */
}

void pcm_mcs48_set_params(uint8_t dev_type, uint16_t dev_size, uint8_t max_retries)
{
    _g_maxRetries = max_retries;
    _g_devSize = dev_size;
    _g_devType = dev_type;

    _g_offset = 0;
    _g_maxPerByteWrites = 0;
    _g_totalWrites = 0;

#ifdef _DEBUG
    //printf("pcm_mcs48_set_params(): completed\r\n");
#endif /* _DEBUG */
}

void pcm_mcs48_power_on()
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

void pcm_mcs48_reset(void)
{
    pcm_mcs48_pe_disable();
    //pcm_mcs48_rd_disable();
    //pcm_mcs48_wr_disable();

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

void pcm_mcs48_write_chunk(void)
{
    uint8_t chunk[WRITE_CHUNK_SIZE];
    uint8_t attempt;
    int16_t remaining = (_g_devSize - _g_offset);
    uint8_t i;
    uint16_t thisChunk = remaining > WRITE_CHUNK_SIZE ? WRITE_CHUNK_SIZE : remaining;

#ifdef _DEBUG
    printf("pcm_mcs48_write_chunk() thisChunk=%d remaining=%d _g_offset=%d\r\n", thisChunk, remaining, _g_offset);
#endif /* _DEBUG */

    /* The host is going to shove all of the data in at once, so we have to buffer it */
    for (i = 0; i < thisChunk; i++)
        chunk[i] = host_read8();

    /* Now get writing it */
    for (i = 0; i < thisChunk; i++)
    {
        uint8_t verified = 0;
        uint8_t stopat = _g_useHts ? _g_maxRetries : 1;
        pgm_write_address(_g_offset + i); /* Output address */
            
        for (attempt = 0; attempt < stopat; attempt++)
        {
            uint8_t data;
            uint8_t temp = chunk[i];

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

void pcm_mcs48_read_chunk(void)
{
    int16_t remaining = (_g_devSize - _g_offset);
    uint8_t i;
    int thisChunk = remaining > READ_CHUNK_SIZE ? READ_CHUNK_SIZE : remaining;

    cmd_respond(CMD_READ_CHUNK, (_g_offset + thisChunk) == _g_devSize ? ERR_COMPLETE : ERR_OK);

#ifdef _DEBUG
    printf("pcm_mcs48_read_chunk() thisChunk=%d remaining=%d _g_offset=%d\r\n", thisChunk, remaining, _g_offset);
#endif /* _DEBUG */

    for (i = 0; i < thisChunk; i++)
    {
        pgm_write_address(_g_offset + i); /* Output address */

        /* Read data */
        pcm_mcs48_delay_read();
        pcm_mcs48_rd_enable();
        pcm_mcs48_delay_read();
        host_write8(pgm_read_data());
        pcm_mcs48_rd_disable();
        pcm_mcs48_delay_read();
    }

    _g_offset += thisChunk;
}

void pcm_mcs48_blank_check(void)
{
    uint16_t offset = 0;
    uint8_t data;

    while (offset < _g_devSize)
    {
        // CLOSE, BUT NOT GOING TO WORK.
        pgm_write_address(offset); /* Output address */
        pcm_mcs48_delay_read();
        pcm_mcs48_rd_enable();
        pcm_mcs48_delay_read();
        data = pgm_read_data();
        pcm_mcs48_rd_disable();
        pcm_mcs48_delay_read();

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

void pcm_mcs48_start_write(void)
{
    _g_useHts = host_read8();
    _g_extraWrites = host_read8();

#ifdef _DEBUG
    printf("pcm_mcs48_start_write() _g_useHts=%d _g_extraWrites=%d\r\n", _g_useHts, _g_extraWrites);
#endif /* _DEBUG */

    pcm_mcs48_power_on();

    cmd_respond(CMD_START_WRITE, ERR_OK);
}

void pcm_mcs48_start_read(void)
{
#ifdef _DEBUG
    printf("pcm_mcs48_start_read()\r\n");
#endif /* _DEBUG */

    pcm_mcs48_power_on();

    cmd_respond(CMD_START_READ, ERR_OK);
}

void pcm_mcs48_start_blank_check(void)
{
#ifdef _DEBUG
    printf("pcm_mcs48_start_blank_check()\r\n");
#endif /* _DEBUG */

    pcm_mcs48_power_on();

    cmd_respond(CMD_START_BLANK_CHECK, ERR_OK);
}

void pcm_mcs48_test(void)
{
    uint8_t test_num = host_read8();

    switch (test_num)
    {
        case TEST_270X_MCM6876X_PON:
            pcm_mcs48_power_on();
            break;
        case TEST_270X_MCM6876X_RD:
            pcm_mcs48_power_on();
            pcm_mcs48_rd_enable();
            break;
        case TEST_270X_MCM6876X_WR:
            pcm_mcs48_power_on();
            pcm_mcs48_wr_enable();
            break;
        case TEST_270X_MCM6876X_PE:
            pcm_mcs48_power_on();
            pcm_mcs48_pe_enable();
            break;
        case TEST_270X_MCM6876X_AA:
            pcm_mcs48_power_on();
            pgm_dir_out();
            pgm_write_data(0xAA);
            pgm_write_address(0xAAA);
            break;
        case TEST_270X_MCM6876X_55:
            pcm_mcs48_power_on();
            pgm_dir_out();
            pgm_write_data(0x55);
            pgm_write_address(0x1555);
            break;
        case TEST_270X_MCM6876X_DATA:
            pcm_mcs48_power_on();
            break;
        default:
            cmd_respond(ERR_INVALID_CMD, ERR_OK);
            return;
    }

    cmd_respond(CMD_TEST, ERR_OK);
}

void pcm_mcs48_test_read(void)
{
    cmd_respond(CMD_TEST_READ, ERR_OK);
    host_write8(pgm_read_data());
}
