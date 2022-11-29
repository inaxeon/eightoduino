/*
 *   8OD - Arduino form factor i8086 based SBC
 *   Matthew Millman (tech.mattmillman.com/8od)
 *
 *   1702A/2704/2708/TMS2716/MCM6876x/MCS48 EPROM Programmer
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
#include "pgm_1702a.h"

#define C1702A_SIZE     0x100

#ifdef _M8OD

#ifdef _80D_5MHZ_
#define DELAY_READ 2
#define DELAY_AD_HOLD 2
#define DELAY_AD_HOLD_POST_VDD 38
#define DELAY_WRITE 745
#define DELAY_POST_WRITE 3340
#define DELAY_POWER_WAIT 0x7FFF
#else
#define DELAY_READ 5
#define DELAY_AD_HOLD 5
#define DELAY_AD_HOLD_POST_VDD 81
#define DELAY_WRITE 1495
#define DELAY_POST_WRITE 6684
#define DELAY_POWER_WAIT 0xFFFF
#endif

#define pgm_1702a_delay_read() delay_ncycles(DELAY_READ)
#define pgm_1702a_delay_ad_setup() delay_ncycles(1)
#define pgm_1702a_delay_ad_hold() delay_ncycles(DELAY_AD_HOLD)
#define pgm_1702a_delay_ad_hold_post_vdd() delay_ncycles(DELAY_AD_HOLD_POST_VDD)
#define pgm_1702a_delay_write() delay_ncycles(DELAY_WRITE)
#define pgm_1702a_delay_post_write() delay_ncycles(DELAY_POST_WRITE)

#define pgm_1702a_pen_enable()  cpld_write(CTRL_PORT, C1702A_PEN, C1702A_PEN)
#define pgm_1702a_pen_disable() cpld_write(CTRL_PORT, C1702A_PEN, 0)
#define pgm_1702a_ren_enable()  cpld_write(CTRL_PORT, C1702A_REN, C1702A_REN)
#define pgm_1702a_ren_disable() cpld_write(CTRL_PORT, C1702A_REN, 0)
#define pgm_1702a_vdd_enable()  cpld_write(CTRL_PORT, C1702A_PGMVDD, C1702A_PGMVDD)
#define pgm_1702a_vdd_disable() cpld_write(CTRL_PORT, C1702A_PGMVDD, 0)
#define pgm_1702a_cs_enable()   cpld_write(CTRL_PORT, C1702A_CSEN, C1702A_CSEN)
#define pgm_1702a_cs_disable()  cpld_write(CTRL_PORT, C1702A_CSEN, 0)
#define pgm_1702a_pgm_enable()  cpld_write(CTRL_PORT, C1702A_PGMEN, C1702A_PGMEN)
#define pgm_1702a_pgm_disable() cpld_write(CTRL_PORT, C1702A_PGMEN, 0)

#endif /* _M8OD */

#ifdef _MDUINO

#define pgm_1702a_delay_read() _delay_us(100)
#define pgm_1702a_delay_ad_setup() _delay_us(5)
#define pgm_1702a_delay_ad_hold() _delay_us(40)
#define pgm_1702a_delay_ad_hold_post_vdd() _delay_us(150)
#define pgm_1702a_delay_write() _delay_us(2700)
#define pgm_1702a_delay_post_write() _delay_ms(12)

#define pgm_1702a_pen_enable()  C1702A_PEN_PORT |= _BV(C1702A_PEN)
#define pgm_1702a_pen_disable() C1702A_PEN_PORT &= ~_BV(C1702A_PEN)
#define pgm_1702a_ren_enable()  C1702A_REN_PORT |= _BV(C1702A_REN)
#define pgm_1702a_ren_disable() C1702A_REN_PORT &= ~_BV(C1702A_REN)
#define pgm_1702a_vdd_enable()  C1702A_PGMVDD_PORT |= _BV(C1702A_PGMVDD)
#define pgm_1702a_vdd_disable() C1702A_PGMVDD_PORT &= ~_BV(C1702A_PGMVDD)
#define pgm_1702a_cs_enable()   C1702A_CSEN_PORT |= _BV(C1702A_CSEN)
#define pgm_1702a_cs_disable()  C1702A_CSEN_PORT &= ~_BV(C1702A_CSEN)
#define pgm_1702a_pgm_enable()  C1702A_PGMEN_PORT |= _BV(C1702A_PGMEN)
#define pgm_1702a_pgm_disable() C1702A_PGMEN_PORT &= ~_BV(C1702A_PGMEN)

#endif /* _MDUINO */

#define TEST_1702A_READ_PON    1
#define TEST_1702A_READ_CS     2
#define TEST_1702A_READ_AA     3
#define TEST_1702A_READ_55     4
#define TEST_1702A_READ_DATA   5
#define TEST_1702A_WRITE_PON   6
#define TEST_1702A_WRITE_PGM   7
#define TEST_1702A_WRITE_VDD   8
#define TEST_1702A_WRITE_AA    9
#define TEST_1702A_WRITE_55    10

uint16_t _g_1702a_offset;

void pgm_1702a_set_params(void)
{
    _g_1702a_offset = 0;
}

static void pgm_1702a_read_power_on()
{
#ifdef _M8OD 
    if ((cpld_read(CTRL_PORT) & C1702A_READPWREN) == 0)
#endif /* _M8OD */
#ifdef _MDUINO
    if ((C1702A_PGMPWREN_PIN & _BV(C1702A_READPWREN)) == 0)
#endif /* _MDUINO */
    {
#ifdef _M8OD
        cpld_write(CTRL_PORT, C1702A_READPWREN, C1702A_READPWREN);
        delay_ncycles(0xFFFF);
#endif /* _M8OD */

#ifdef _MDUINO
        C1702A_READPWREN_PORT |= _BV(C1702A_READPWREN);
        _delay_ms(100);
#endif /* _MDUINO */
    }
}

static void pgm_1702a_write_power_on()
{
#ifdef _M8OD 
    if ((cpld_read(CTRL_PORT) & C1702A_PGMPWREN) == 0)
#endif /* _M8OD */
#ifdef _MDUINO
    if ((C1702A_PGMPWREN_PIN & _BV(C1702A_PGMPWREN)) == 0)
#endif /* _MDUINO */
    {
#ifdef _M8OD
        cpld_write(CTRL_PORT, C1702A_PGMPWREN, C1702A_PGMPWREN);
        delay_ncycles(DELAY_POWER_WAIT);
#endif /* _M8OD */

#ifdef _MDUINO
        C1702A_PGMPWREN_PORT |= _BV(C1702A_PGMPWREN);
        _delay_ms(100);
#endif /* _MDUINO */
    }
}

void pgm_1702a_init(void)
{
    pgm_1702a_ren_disable();
    pgm_1702a_pen_disable();

#ifdef _M8OD
    cpld_write(CTRL_PORT, 
        (C1702A_NC_0 | C1702A_IMAX | C1702A_PGMEN | C1702A_CSEN | C1702A_PGMVDD | C1702A_PGMPWREN | C1702A_READPWREN),
        0
    );
    // Imax + NC's as inputs
    cpld_write(CTRL_TRIS,
        (C1702A_NC_0 | C1702A_IMAX | C1702A_REN | C1702A_PGMEN | C1702A_CSEN | C1702A_PEN | C1702A_PGMVDD | C1702A_PGMPWREN | C1702A_READPWREN),
        (C1702A_NC_0 | C1702A_IMAX)
    );
#endif /* _M8OD */

#ifdef _MDUINO
    C1702A_PGMEN_PORT &= ~_BV(C1702A_PGMEN);
    C1702A_CSEN_PORT &= ~_BV(C1702A_CSEN);
    C1702A_PGMVDD_PORT &= ~_BV(C1702A_PGMVDD);
    C1702A_PGMPWREN_PORT &= ~_BV(C1702A_PGMPWREN);
    C1702A_READPWREN_PORT &= ~_BV(C1702A_READPWREN);

    C1702A_NC_0_DDR &= ~_BV(C1702A_NC_0); // input
    C1702A_IMAX_DDR &= ~_BV(C1702A_IMAX); // input
    C1702A_REN_DDR |= _BV(C1702A_REN); // input
    C1702A_PGMEN_DDR |= _BV(C1702A_PGMEN); // output
    C1702A_CSEN_DDR |= _BV(C1702A_CSEN); // output
    C1702A_PEN_DDR |= _BV(C1702A_PEN); // output
    C1702A_PGMVDD_DDR |= _BV(C1702A_PGMVDD); // output
    C1702A_PGMPWREN_DDR |= _BV(C1702A_PGMPWREN); // output
    C1702A_READPWREN_DDR |= _BV(C1702A_READPWREN); // output
#endif /* _MDUINO */

#ifdef _DEBUG
    printf("pgm_1702a_init(): completed\r\n");
#endif /* _DEBUG */
}

static void pgm_1702a_do_reset(void)
{
#ifdef _DEBUG
    printf("pgm_1702a_do_reset()\r\n");
#endif /* _DEBUG */

#ifdef _M8OD 
    if ((cpld_read(CTRL_PORT) & C1702A_PGMPWREN) == C1702A_PGMPWREN)
#endif /* _M8OD */
#ifdef _MDUINO
    if ((C1702A_PGMPWREN_PIN & _BV(C1702A_PGMPWREN)) == _BV(C1702A_PGMPWREN))
#endif /* _MDUINO */
    {
#ifdef _M8OD
        pgm_1702a_pen_disable();
        cpld_write(CTRL_PORT, (C1702A_PGMPWREN), 0);
        // Wait for high voltage supplies to discharge
        delay_ncycles(DELAY_POWER_WAIT);
        delay_ncycles(DELAY_POWER_WAIT);
        delay_ncycles(DELAY_POWER_WAIT);
#endif /* _M8OD */

#ifdef _MDUINO
        pgm_1702a_pen_disable();
        C1702A_PGMPWREN_PORT &= ~_BV(C1702A_PGMPWREN);
        // Wait for high voltage supplies to discharge
        _delay_ms(100);
        _delay_ms(100);
        _delay_ms(100);
#endif /* _MDUINO */

        pgm_1702a_pgm_disable();
        pgm_1702a_cs_disable();
        pgm_1702a_vdd_disable();
    }

#ifdef _M8OD
    if ((cpld_read(CTRL_PORT) & C1702A_READPWREN) == C1702A_READPWREN)
#endif /* _M8OD */
#ifdef _MDUINO
    if ((C1702A_READPWREN_PIN & _BV(C1702A_READPWREN)) == _BV(C1702A_READPWREN))
#endif /* _MDUINO */
    {
        
#ifdef _M8OD
        pgm_1702a_ren_disable();
        cpld_write(CTRL_PORT, (C1702A_READPWREN), 0);
        delay_ncycles(DELAY_POWER_WAIT);
        delay_ncycles(DELAY_POWER_WAIT);
#endif /* _M8OD */

#ifdef _MDUINO
        pgm_1702a_ren_disable();
        C1702A_READPWREN_PORT &= ~_BV(C1702A_READPWREN);
        _delay_ms(100);
        _delay_ms(100);
#endif /* _MDUINO */

        pgm_1702a_pgm_disable();
        pgm_1702a_cs_disable();
        pgm_1702a_vdd_disable();
    }

    pgm_dir_in();
}

void pgm_1702a_write_chunk(void)
{
    uint8_t chunk[WRITE_CHUNK_SIZE];
    uint16_t remaining = (C1702A_SIZE - _g_1702a_offset);
    uint8_t i;
    uint8_t thisChunk = remaining > WRITE_CHUNK_SIZE ? WRITE_CHUNK_SIZE : remaining;

#ifdef _DEBUG
    printf("pgm_1702a_write_chunk() thisChunk=%d remaining=%d _g_1702a_offset=%d\r\n", thisChunk, remaining, _g_1702a_offset);
#endif /* _DEBUG */

    pgm_1702a_write_power_on();
    pgm_1702a_pen_enable();
    pgm_1702a_delay_read();

    /* Read data from host */
    for (i = 0; i < thisChunk; i++)
        chunk[i] = host_read8();

    /* Now get writing it */
    for (i = 0; i < thisChunk; i++)
    {
        uint8_t data = chunk[i];
        uint8_t addr = _g_1702a_offset + i;

        pgm_dir_out();
        pgm_write_data(data);

        pgm_write_address(~addr); /* Output inverted address */
        pgm_1702a_delay_ad_hold();
        pgm_1702a_vdd_enable();
        pgm_1702a_delay_ad_hold_post_vdd();
        pgm_write_address(addr); /* Output address */
        pgm_1702a_delay_ad_hold();
        pgm_1702a_pgm_enable(); /* Main pulse: 2.7ms */
        pgm_1702a_delay_write();
        pgm_1702a_pgm_disable();
        pgm_1702a_delay_ad_hold();
        pgm_1702a_vdd_disable();

        pgm_1702a_delay_post_write(); /* 12ms */
    }

    _g_1702a_offset += thisChunk;

    pgm_1702a_pen_disable();
    pgm_1702a_delay_read();

    if (_g_1702a_offset == C1702A_SIZE)
    {
        cmd_respond(CMD_WRITE_CHUNK, ERR_COMPLETE);
        host_write8(0); // max per byte writes
        host_write32(0); // total writes
    }
    else
    {
        cmd_respond(CMD_WRITE_CHUNK, ERR_OK);
    }
}

void pgm_1702a_read_chunk(void)
{
    int16_t remaining = (C1702A_SIZE - _g_1702a_offset);
    uint8_t i;
    int thisChunk = remaining > READ_CHUNK_SIZE ? READ_CHUNK_SIZE : remaining;

    cmd_respond(CMD_READ_CHUNK, (_g_1702a_offset + thisChunk) == C1702A_SIZE ? ERR_COMPLETE : ERR_OK);

#ifdef _DEBUG
    printf("pgm_1702a_read_chunk() thisChunk=%d remaining=%d _g_1702a_offset=%d\r\n", thisChunk, remaining, _g_1702a_offset);
#endif /* _DEBUG */

    pgm_1702a_read_power_on();
    pgm_1702a_ren_enable();
    pgm_1702a_delay_read();

    for (i = 0; i < thisChunk; i++)
    {
        pgm_write_address(_g_1702a_offset + i); /* Output address */
        /* Read data */
        pgm_1702a_delay_read();
        pgm_1702a_cs_enable();
        pgm_1702a_delay_read();
        host_write8(pgm_read_data());
        pgm_1702a_cs_disable();
        pgm_1702a_delay_read();
    }

    pgm_1702a_ren_disable();
    pgm_1702a_delay_read();

    _g_1702a_offset += thisChunk;
}

void pgm_1702a_blank_check(void)
{
    uint16_t offset = 0;
    uint8_t data;

    pgm_1702a_read_power_on();
    pgm_1702a_ren_enable();

    while (offset < C1702A_SIZE)
    {
        pgm_write_address(offset); /* Output address */
        pgm_1702a_delay_read();

        pgm_1702a_cs_enable();
        pgm_1702a_delay_read();
        data = pgm_read_data();
        pgm_1702a_cs_disable();
        pgm_1702a_delay_read();

        if (data != 0x00)
            break;

        offset++;
    }

    pgm_1702a_ren_disable();

    if (offset == C1702A_SIZE)
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

void pgm_1702a_start_write(void)
{
    host_read8(); // Unused - HTS byte
    host_read8(); // Unused - extra writes byte

    pgm_1702a_do_reset();
    
#ifdef _DEBUG
    printf("pgm_1702a_start_write()\r\n");
#endif /* _DEBUG */

    // Programmers with seperate read/write sockets should return ERR_PROCEED_DUALSOCKET.
    // The UI will prompt the user to move the device to the appropriate socket.
    cmd_respond(CMD_START_WRITE, ERR_OK);
}

void pgm_1702a_start_read(void)
{
    pgm_1702a_do_reset();

#ifdef _DEBUG
    printf("pgm_1702a_start_read()\r\n");
#endif /* _DEBUG */

    // Programmers with seperate read/write sockets should return ERR_PROCEED_DUALSOCKET.
    // The UI will prompt the user to move the device to the appropriate socket.
    cmd_respond(CMD_START_READ, ERR_OK);
}

void pgm_1702a_start_blank_check(void)
{
    pgm_1702a_do_reset();

#ifdef _DEBUG
    printf("pgm_1702a_start_blank_check()\r\n");
#endif /* _DEBUG */

    // Programmers with seperate read/write sockets should return ERR_PROCEED_DUALSOCKET.
    // The UI will prompt the user to move the device to the appropriate socket.
    cmd_respond(CMD_START_BLANK_CHECK, ERR_OK);
}

void pgm_1702a_reset(void)
{
#ifdef _DEBUG
    printf("pgm_1702a_reset()\r\n");
#endif /* _DEBUG */

    pgm_1702a_do_reset();
    cmd_respond(CMD_DEV_RESET, ERR_OK);
}

void pgm_1702a_test(void)
{
    uint8_t test_num = host_read8();

    switch (test_num)
    {
        case TEST_1702A_READ_PON:
            pgm_1702a_read_power_on();
            break;
        case TEST_1702A_READ_CS:
            pgm_1702a_read_power_on();
            pgm_1702a_cs_enable();
            break;
        case TEST_1702A_READ_AA:
            pgm_1702a_read_power_on();
            pgm_1702a_ren_enable();
            pgm_write_address(0xAA);
            break;
        case TEST_1702A_READ_55:
            pgm_1702a_read_power_on();
            pgm_1702a_ren_enable();
            pgm_write_address(0x55);
            break;
        case TEST_1702A_READ_DATA:
            pgm_1702a_read_power_on();
            pgm_1702a_ren_enable();
            break;
        case TEST_1702A_WRITE_PON:
            pgm_1702a_write_power_on();
            break;
        case TEST_1702A_WRITE_PGM:
            pgm_1702a_write_power_on();
            pgm_1702a_pgm_enable();
            break;
        case TEST_1702A_WRITE_VDD:
            pgm_1702a_write_power_on();
            pgm_1702a_vdd_enable();
            break;
        case TEST_1702A_WRITE_AA:
            pgm_1702a_write_power_on();
            pgm_1702a_pen_enable();
            pgm_write_address(0xAA);
            break;
        case TEST_1702A_WRITE_55:
            pgm_1702a_write_power_on();
            pgm_1702a_pen_enable();
            pgm_write_address(0x55);
            break;
        default:
            cmd_respond(ERR_INVALID_CMD, ERR_OK);
            return;
    }

    cmd_respond(CMD_TEST, ERR_OK);
}

void pgm_1702a_test_read(void)
{
    cmd_respond(CMD_TEST_READ, ERR_OK);
    host_write8(pgm_read_data());
}
