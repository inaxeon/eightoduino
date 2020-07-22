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

#ifdef _M8OD

#define pgm_mcs48_cs_enable() cpld_write(CTRL_PORT, MCS48_CS, 0)
#define pgm_mcs48_cs_disable() cpld_write(CTRL_PORT, MCS48_CS, MCS48_CS)

#define pgm_mcs48_a0_enable() cpld_write(CTRL_PORT, MCS48_A0, MCS48_A0)
#define pgm_mcs48_a0_disable() cpld_write(CTRL_PORT, MCS48_A0, 0)

#define pgm_mcs48_ea_enable() cpld_write(CTRL_PORT, MCS48_EA, MCS48_EA)
#define pgm_mcs48_ea_disable() cpld_write(CTRL_PORT, MCS48_EA, 0)

#define pgm_mcs48_vdd_enable() cpld_write(CTRL_PORT, MCS48_VDDEN, MCS48_VDDEN)
#define pgm_mcs48_vdd_disable() cpld_write(CTRL_PORT, MCS48_VDDEN, 0)

#define pgm_mcs48_test0_enable() cpld_write(CTRL_PORT, MCS48_TEST0, MCS48_TEST0)
#define pgm_mcs48_test0_disable() cpld_write(CTRL_PORT, MCS48_TEST0, 0)

#define pgm_mcs48_prog_enable() cpld_write(CTRL_PORT, MCS48_PROGEN, MCS48_PROGEN)
#define pgm_mcs48_prog_disable() cpld_write(CTRL_PORT, MCS48_PROGEN, 0)

#define pgm_mcs48_reset_enable() cpld_write(CTRL_PORT, MCS48_RESET, 0)
#define pgm_mcs48_reset_disable() cpld_write(CTRL_PORT, MCS48_RESET, MCS48_RESET)

#endif /* _M8OD */

#ifdef _MDUINO

#define pgm_mcs48_cs_enable() MCS48_CS_PORT &= ~_BV(MCS48_CS)
#define pgm_mcs48_cs_disable() MCS48_CS_PORT |= _BV(MCS48_CS)

#define pgm_mcs48_a0_enable() MCS48_A0_PORT |= _BV(MCS48_A0)
#define pgm_mcs48_a0_disable() MCS48_A0_PORT &= ~_BV(MCS48_A0)

#define pgm_mcs48_ea_enable() MCS48_EA_PORT |= _BV(MCS48_EA)
#define pgm_mcs48_ea_disable() MCS48_EA_PORT &= ~_BV(MCS48_EA)

#define pgm_mcs48_vdd_enable() MCS48_VDDEN_PORT |= _BV(MCS48_VDDEN)
#define pgm_mcs48_vdd_disable() MCS48_VDDEN_PORT &= ~_BV(MCS48_VDDEN)

#define pgm_mcs48_test0_enable() MCS48_TEST0_PORT |= _BV(MCS48_TEST0)
#define pgm_mcs48_test0_disable() MCS48_TEST0_PORT &= ~_BV(MCS48_TEST0)

#define pgm_mcs48_prog_enable() MCS48_PROGEN_PORT |= _BV(MCS48_PROGEN)
#define pgm_mcs48_prog_disable() MCS48_PROGEN_PORT &= ~_BV(MCS48_PROGEN)

#define pgm_mcs48_reset_enable() MCS48_RESET_PORT &= ~_BV(MCS48_RESET)
#define pgm_mcs48_reset_disable() MCS48_RESET_PORT |= _BV(MCS48_RESET)

#endif /* _MDUINO */

#define TEST_MCS48_PON    1
#define TEST_MCS48_VDD    2
#define TEST_MCS48_EA     3
#define TEST_MCS48_PROG   4
#define TEST_MCS48_AA     5
#define TEST_MCS48_55     6
#define TEST_MCS48_DATA   7

static uint8_t _g_maxPerByteWrites;
static uint8_t _g_useHts;
static uint8_t _g_extraWrites;
static uint8_t _g_maxRetries;
static uint32_t _g_totalWrites;
static uint16_t _g_devSize;
static uint16_t _g_offset;
static int8_t _g_devType;

void pgm_mcs48_init(void)
{
    _g_maxPerByteWrites = 0;
    _g_totalWrites = 0;
    _g_maxRetries = 0;
    _g_devSize = 0;
    _g_devType = -1;

#ifdef _M8OD
    cpld_write(CTRL_PORT,
        (MCS48_CS | MCS48_A0 | MCS48_PON | MCS48_PROGEN | MCS48_EA | MCS48_TEST0 | MCS48_VDDEN | MCS48_RESET),
        (MCS48_CS)
    );
    
    cpld_write(CTRL_TRIS,
        (MCS48_CS | MCS48_A0 | MCS48_PON | MCS48_PROGEN | MCS48_EA | MCS48_ALE | MCS48_TEST0 | MCS48_VDDEN | MCS48_RESET),
        (MCS48_ALE)
    );
#endif /* _M8OD */

#ifdef _MDUINO
    MCS48_CS_PORT |= _BV(MCS48_CS);
    MCS48_A0_PORT &= ~_BV(MCS48_A0);
    MCS48_PON_PORT &= ~_BV(MCS48_PON);
    MCS48_PROGEN_PORT &= ~_BV(MCS48_PROGEN);
    MCS48_EA_PORT &= ~_BV(MCS48_EA);
    MCS48_TEST0_PORT &= ~_BV(MCS48_TEST0);
    MCS48_VDDEN_PORT &= ~_BV(MCS48_VDDEN);
    MCS48_RESET_PORT &= ~_BV(MCS48_RESET);

    MCS48_CS_DDR |= _BV(MCS48_CS);
    MCS48_A0_DDR |= _BV(MCS48_A0);
    MCS48_PON_DDR |= _BV(MCS48_PON);
    MCS48_PROGEN_DDR |= _BV(MCS48_PROGEN);
    MCS48_EA_DDR |= _BV(MCS48_EA);
    MCS48_TEST0_DDR |= _BV(MCS48_TEST0);
    MCS48_VDDEN_DDR |= _BV(MCS48_VDDEN);
    MCS48_RESET_DDR |= _BV(MCS48_RESET);
    MCS48_ALE_DDR &= ~_BV(MCS48_ALE);
#endif /* _MDUINO */

#ifdef _DEBUG
    printf("pgm_mcs48_io_init(): completed\r\n");
#endif /* _DEBUG */
}

void pgm_mcs48_set_params(uint8_t dev_type, uint16_t dev_size, uint8_t max_retries)
{
    _g_maxRetries = max_retries;
    _g_devSize = dev_size;
    _g_devType = dev_type;

    _g_offset = 0;
    _g_maxPerByteWrites = 0;
    _g_totalWrites = 0;

#ifdef _DEBUG
    printf("pgm_mcs48_set_params(): completed\r\n");
#endif /* _DEBUG */
}

void pgm_mcs48_power_on()
{
#ifdef _M8OD
    cpld_write(CTRL_PORT, MCS48_PON, MCS48_PON);
    delay_ncycles(DELAY_POWER_WAIT);
#endif /* _M8OD */

#ifdef _MDUINO
    MCS48_PON_PORT |= _BV(MCS48_PON);
    _delay_ms(100);
#endif /* _MDUINO */
}

void pgm_mcs48_reset(void)
{
    pgm_mcs48_cs_disable();
    pgm_mcs48_a0_disable();
    pgm_mcs48_ea_disable();
    pgm_mcs48_vdd_disable();
    pgm_mcs48_test0_disable();
    pgm_mcs48_prog_disable();
    pgm_mcs48_reset_disable();

#ifdef _M8OD
    delay_ncycles(DELAY_POWER_WAIT);
    cpld_write(CTRL_PORT, MCS48_PON, 0); /* Power off */
#endif /* _M8OD */

#ifdef _MDUINO
    _delay_ms(100);
    MCS48_PON_PORT &= ~_BV(MCS48_PON);
#endif /* _MDUINO */

    pgm_dir_in();
    cmd_respond(CMD_DEV_RESET, ERR_OK);
}

void pgm_mcs48_write_chunk(void)
{
    uint8_t chunk[WRITE_CHUNK_SIZE];
    uint8_t attempt;
    int16_t remaining = (_g_devSize - _g_offset);
    uint8_t i;
    uint16_t thisChunk = remaining > WRITE_CHUNK_SIZE ? WRITE_CHUNK_SIZE : remaining;

#ifdef _DEBUG
    printf("pgm_mcs48_write_chunk() thisChunk=%d remaining=%d _g_offset=%d\r\n", thisChunk, remaining, _g_offset);
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
            // uint8_t data;
            // uint8_t temp = chunk[i];

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

void pgm_mcs48_read_chunk(void)
{
    int16_t remaining = (_g_devSize - _g_offset);
    uint8_t i;
    int thisChunk = remaining > READ_CHUNK_SIZE ? READ_CHUNK_SIZE : remaining;

    cmd_respond(CMD_READ_CHUNK, (_g_offset + thisChunk) == _g_devSize ? ERR_COMPLETE : ERR_OK);

#ifdef _DEBUG
    printf("pgm_mcs48_read_chunk() thisChunk=%d remaining=%d _g_offset=%d\r\n", thisChunk, remaining, _g_offset);
#endif /* _DEBUG */

    for (i = 0; i < thisChunk; i++)
    {
        pgm_write_address(_g_offset + i); /* Output address */

        /* Read data */
        // pgm_mcs48_delay_read();
        // pgm_mcs48_rd_enable();
        // pgm_mcs48_delay_read();
        // host_write8(pgm_read_data());
        // pgm_mcs48_rd_disable();
        // pgm_mcs48_delay_read();
    }

    _g_offset += thisChunk;
}

void pgm_mcs48_blank_check(void)
{
    uint16_t offset = 0;
    uint8_t data;

    while (offset < _g_devSize)
    {
        // CLOSE, BUT NOT GOING TO WORK.
        pgm_write_address(offset); /* Output address */
        // pgm_mcs48_delay_read();
        // pgm_mcs48_rd_enable();
        // pgm_mcs48_delay_read();
        // data = pgm_read_data();
        // pgm_mcs48_rd_disable();
        // pgm_mcs48_delay_read();

        // if (data != 0xFF)
        //     break;

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

void pgm_mcs48_start_write(void)
{
    _g_useHts = host_read8();
    _g_extraWrites = host_read8();

#ifdef _DEBUG
    printf("pgm_mcs48_start_write() _g_useHts=%d _g_extraWrites=%d\r\n", _g_useHts, _g_extraWrites);
#endif /* _DEBUG */

    pgm_mcs48_power_on();

    cmd_respond(CMD_START_WRITE, ERR_OK);
}

void pgm_mcs48_start_read(void)
{
#ifdef _DEBUG
    printf("pgm_mcs48_start_read()\r\n");
#endif /* _DEBUG */

    pgm_mcs48_power_on();

    cmd_respond(CMD_START_READ, ERR_OK);
}

void pgm_mcs48_start_blank_check(void)
{
#ifdef _DEBUG
    printf("pgm_mcs48_start_blank_check()\r\n");
#endif /* _DEBUG */

    pgm_mcs48_power_on();

    cmd_respond(CMD_START_BLANK_CHECK, ERR_OK);
}

void pgm_mcs48_test(void)
{
    uint8_t test_num = host_read8();

    switch (test_num)
    {
        case TEST_MCS48_PON:
            pgm_mcs48_power_on();
            break;
        case TEST_MCS48_VDD:
            pgm_mcs48_power_on();
            pgm_mcs48_vdd_enable();
            break;
        case TEST_MCS48_EA:
            pgm_mcs48_power_on();
            pgm_mcs48_ea_enable();
            break;
        case TEST_MCS48_PROG:
            pgm_mcs48_power_on();
            pgm_mcs48_prog_enable();
            break;
        case TEST_MCS48_AA:
            pgm_mcs48_power_on();
            pgm_dir_out();
            pgm_write_data(0xAA);
            pgm_write_address(0xAAA);
            pgm_mcs48_a0_enable();
            pgm_mcs48_cs_enable();
            break;
        case TEST_MCS48_55:
            pgm_mcs48_power_on();
            pgm_dir_out();
            pgm_write_data(0x55);
            pgm_write_address(0x1555);
            pgm_mcs48_test0_enable();
            pgm_mcs48_reset_enable();
            break;
        case TEST_MCS48_DATA:
            pgm_mcs48_power_on();
            break;
        default:
            cmd_respond(ERR_INVALID_CMD, ERR_OK);
            return;
    }

    cmd_respond(CMD_TEST, ERR_OK);
}

void pgm_mcs48_test_read(void)
{
    cmd_respond(CMD_TEST_READ, ERR_OK);
    host_write8(pgm_read_data());
}
