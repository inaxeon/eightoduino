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
#include "pgm_mcs48.h"

#ifdef _M8OD

#ifdef _80D_5MHZ_
#define DELAY_PRE_READ      1
#define DELAY_4TCY          2
#define DELAY_WRITE         13925
#define DELAY_PRE_POST_VDD  260
#define DELAY_POWER_WAIT    0x7FFF
#else
#define DELAY_PRE_READ      2
#define DELAY_4TCY          4
#define DELAY_WRITE         27850
#define DELAY_PRE_POST_VDD  535
#define DELAY_POWER_WAIT    0xFFFF
#endif

#define pgm_mcs48_delay_4tcy() delay_ncycles(DELAY_4TCY)
#define pgm_mcs48_delay_write() delay_ncycles(DELAY_WRITE)
#define pgm_mcs48_delay_pre_read() delay_ncycles(DELAY_PRE_READ)
#define pgm_mcs48_delay_pre_post_vdd() delay_ncycles(DELAY_PRE_POST_VDD)

#define pgm_mcs48_pwr_up1_enable() cpld_write(CTRL_TRIS, MCS48_PWR_UP1, 0)
#define pgm_mcs48_pwr_up1_disable() cpld_write(CTRL_TRIS, MCS48_PWR_UP1, MCS48_PWR_UP1)

#define pgm_mcs48_pwr_up2_enable() cpld_write(CTRL_TRIS, MCS48_PWR_UP2, 0)
#define pgm_mcs48_pwr_up2_disable() cpld_write(CTRL_TRIS, MCS48_PWR_UP2, MCS48_PWR_UP2)

#define pgm_mcs48_ea_enable() cpld_write(CTRL_PORT, MCS48_EA, MCS48_EA)
#define pgm_mcs48_ea_disable() cpld_write(CTRL_PORT, MCS48_EA, 0)

#define pgm_mcs48_vdd_enable() cpld_write(CTRL_PORT, MCS48_VDDEN, MCS48_VDDEN)
#define pgm_mcs48_vdd_disable() cpld_write(CTRL_PORT, MCS48_VDDEN, 0)

#define pgm_mcs48_8755_test0_or_prog_enable() cpld_write(CTRL_PORT, MCS48_TEST0, MCS48_TEST0)
#define pgm_mcs48_8755_test0_or_prog_disable() cpld_write(CTRL_PORT, MCS48_TEST0, 0)

#define pgm_mcs48_prog_enable() cpld_write(CTRL_PORT, MCS48_PROGEN, MCS48_PROGEN)
#define pgm_mcs48_prog_disable() cpld_write(CTRL_PORT, MCS48_PROGEN, 0)

#define pgm_mcs48_8755_reset_or_ale_enable() do {               \
    if (_g_devType == DEV_8755)                                 \
        cpld_write(CTRL_PORT, MCS48_RESET, MCS48_RESET);        \
    else                                                        \
        cpld_write(CTRL_PORT, MCS48_RESET, 0);                  \
    } while (0)

#define pgm_mcs48_8755_reset_or_ale_disable() do {              \
    if (_g_devType == DEV_8755)                                 \
        cpld_write(CTRL_PORT, MCS48_RESET, 0);                  \
    else                                                        \
        cpld_write(CTRL_PORT, MCS48_RESET, MCS48_RESET);        \
    } while (0)

#define pgm_8755_rd_enable() cpld_write(PORTD, 0x800, 0)
#define pgm_8755_rd_disable() cpld_write(PORTD, 0x800, 0x800)

#endif /* _M8OD */

#ifdef _MDUINO

#define pgm_mcs48_delay_4tcy() _delay_us(20)
#define pgm_mcs48_delay_write() _delay_ms(50)
#define pgm_mcs48_delay_pre_read() _delay_us(20)
#define pgm_mcs48_delay_pre_post_vdd() _delay_ms(1)

#define pgm_mcs48_pwr_up1_enable() MCS48_PWR_UP1_DDR |= _BV(MCS48_PWR_UP1)
#define pgm_mcs48_pwr_up1_disable() MCS48_PWR_UP1_DDR &= ~_BV(MCS48_PWR_UP1)

#define pgm_mcs48_pwr_up2_enable() MCS48_PWR_UP2_DDR |= _BV(MCS48_PWR_UP2)
#define pgm_mcs48_pwr_up2_disable() MCS48_PWR_UP2_DDR &= ~_BV(MCS48_PWR_UP2)

#define pgm_mcs48_ea_enable() MCS48_EA_PORT |= _BV(MCS48_EA)
#define pgm_mcs48_ea_disable() MCS48_EA_PORT &= ~_BV(MCS48_EA)

#define pgm_mcs48_vdd_enable() MCS48_VDDEN_PORT |= _BV(MCS48_VDDEN)
#define pgm_mcs48_vdd_disable() MCS48_VDDEN_PORT &= ~_BV(MCS48_VDDEN)

#define pgm_mcs48_8755_test0_or_prog_enable() MCS48_TEST0_PORT |= _BV(MCS48_TEST0)
#define pgm_mcs48_8755_test0_or_prog_disable() MCS48_TEST0_PORT &= ~_BV(MCS48_TEST0)

#define pgm_mcs48_prog_enable() MCS48_PROGEN_PORT |= _BV(MCS48_PROGEN)
#define pgm_mcs48_prog_disable() MCS48_PROGEN_PORT &= ~_BV(MCS48_PROGEN)

#define pgm_mcs48_8755_reset_or_ale_enable() do {           \
    if (_g_devType == DEV_8755)                             \
        MCS48_RESET_PORT |= _BV(MCS48_RESET);               \
    else                                                    \
        MCS48_RESET_PORT &= ~_BV(MCS48_RESET);              \
    } while (0)

#define pgm_mcs48_8755_reset_or_ale_disable() do {          \
    if (_g_devType == DEV_8755)                             \
        MCS48_RESET_PORT &= ~_BV(MCS48_RESET);              \
    else                                                    \
        MCS48_RESET_PORT |= _BV(MCS48_RESET);               \
    } while (0)

#define pgm_8755_rd_enable() MCS48_ALE_PORT &= ~_BV(MCS48_ALE)
#define pgm_8755_rd_disable() MCS48_ALE_PORT |= _BV(MCS48_ALE)

#endif /* _MDUINO */

#define TEST_MCS48_PON          1
#define TEST_MCS48_EA_12V       2
#define TEST_MCS48_EA_18V       3
#define TEST_MCS48_EA_22V       4
#define TEST_MCS48_PROG         5
#define TEST_MCS48_VDD_21V      6
#define TEST_MCS48_VDD_25V      7
#define TEST_MCS48_AA           8
#define TEST_MCS48_55           9
#define TEST_MCS48_DATA         10

static uint8_t _g_maxPerByteWrites;
static uint8_t _g_useHts;
static uint8_t _g_maxRetries;
static uint32_t _g_totalWrites;
static uint16_t _g_devSize;
static uint16_t _g_offset;
static uint8_t _g_blankByte;
static int8_t _g_devType;

void pgm_mcs48_init(void)
{
    _g_maxPerByteWrites = 0;
    _g_totalWrites = 0;
    _g_devSize = 0;
    _g_devType = -1;

#ifdef _M8OD
    cpld_write(CTRL_PORT,
        (MCS48_PWR_UP1 | MCS48_PWR_UP2 | MCS48_PON | MCS48_PROGEN | MCS48_EA | MCS48_TEST0 | MCS48_VDDEN | MCS48_RESET), 0);
    
    cpld_write(CTRL_TRIS,
        (MCS48_PWR_UP1 | MCS48_PWR_UP2 | MCS48_PON | MCS48_PROGEN | MCS48_EA | MCS48_ALE | MCS48_TEST0 | MCS48_VDDEN | MCS48_RESET),
        (MCS48_ALE)
    );
#endif /* _M8OD */

#ifdef _MDUINO
    MCS48_PWR_UP1_PORT &= ~_BV(MCS48_PWR_UP1);
    MCS48_PWR_UP2_PORT &= ~_BV(MCS48_PWR_UP2);
    MCS48_PON_PORT &= ~_BV(MCS48_PON);
    MCS48_PROGEN_PORT &= ~_BV(MCS48_PROGEN);
    MCS48_EA_PORT &= ~_BV(MCS48_EA);
    MCS48_TEST0_PORT &= ~_BV(MCS48_TEST0);
    MCS48_VDDEN_PORT &= ~_BV(MCS48_VDDEN);
    MCS48_RESET_PORT &= ~_BV(MCS48_RESET);

    MCS48_PWR_UP1_DDR &= ~_BV(MCS48_PWR_UP1);
    MCS48_PWR_UP2_DDR &= ~_BV(MCS48_PWR_UP2);
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
    _g_blankByte = (dev_type == DEV_8755) ? 0xFF : 0x00;

#ifdef _DEBUG
    printf("pgm_mcs48_set_params(): completed\r\n");
#endif /* _DEBUG */
}

void pgm_mcs48_power_on()
{
    switch (_g_devType)
    {
        case DEV_8748:
        case DEV_8749:
        case DEV_8742:
            // Vpp = 21V
            pgm_mcs48_pwr_up1_enable();
            pgm_mcs48_pwr_up2_disable();
            break;
        case DEV_8741:
        case DEV_8755:
            // Vpp = 25V
            pgm_mcs48_pwr_up1_enable();
            pgm_mcs48_pwr_up2_enable();
            break;
        case DEV_8048:
        case DEV_8049:
        case DEV_8050:
        case DEV_8041:
        case DEV_8042:
            // Vpp = 15V. Reduced down to 12V by 3V zener for EA pin only
            pgm_mcs48_pwr_up1_disable();
            pgm_mcs48_pwr_up2_disable();
            break;
    }

#ifdef _M8OD
    if (_g_devType == DEV_8755)
        cpld_write(CTRL_TRIS, MCS48_ALE, 0); // ALE is used to drive RD for 8755
    else
        cpld_write(CTRL_TRIS, MCS48_ALE, MCS48_ALE); // Not presently used for MCS-48

    cpld_write(CTRL_PORT, MCS48_PON, MCS48_PON);

    delay_ncycles(DELAY_POWER_WAIT);
#endif /* _M8OD */

#ifdef _MDUINO
    if (_g_devType == DEV_8755)
        MCS48_ALE_DDR |= _BV(MCS48_ALE); // ALE is used to drive RD for 8755
    else
        MCS48_ALE_DDR &= ~_BV(MCS48_ALE); // Not presently used for MCS-48

    MCS48_PON_PORT |= _BV(MCS48_PON);

    _delay_ms(100);
#endif /* _MDUINO */

    pgm_mcs48_8755_test0_or_prog_disable();

    if (_g_devType == DEV_8755)
        pgm_mcs48_8755_reset_or_ale_disable(); 
    else
        pgm_mcs48_8755_reset_or_ale_enable();
}

void pgm_mcs48_reset(void)
{
    pgm_mcs48_ea_disable();
    pgm_mcs48_vdd_disable();
    pgm_mcs48_8755_test0_or_prog_disable();
    pgm_mcs48_prog_disable();

    if (_g_devType == DEV_8755)
        pgm_mcs48_8755_reset_or_ale_disable(); 
    else
        pgm_mcs48_8755_reset_or_ale_enable();

#ifdef _M8OD
    delay_ncycles(DELAY_POWER_WAIT);
    cpld_write(CTRL_PORT, MCS48_PON, 0); /* Power off */
#endif /* _M8OD */

#ifdef _MDUINO
    _delay_ms(100);
    MCS48_PON_PORT &= ~_BV(MCS48_PON);
#endif /* _MDUINO */

    pgm_dir_in();
    pgm_write_address(0x000);
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

    /* Read data from host */
    for (i = 0; i < thisChunk; i++)
        chunk[i] = host_read8();

    /* Now get writing it */
    for (i = 0; i < thisChunk; i++)
    {
        uint16_t thisOffset = (_g_offset + i);

        uint8_t verified = 0;
        uint8_t stopat = _g_useHts ? _g_maxRetries : 1;

        /* Setup address */
        pgm_mcs48_8755_reset_or_ale_enable(); // Prepare for address input

        if (_g_devType != DEV_8755)
            pgm_mcs48_8755_test0_or_prog_disable(); // Target data bus = input

        pgm_dir_out();
        pgm_write_data((uint8_t)(thisOffset & 0xFF));
        pgm_write_address(thisOffset & 0xF00); /* Output address */
        pgm_mcs48_delay_4tcy();
        pgm_mcs48_8755_reset_or_ale_disable();
        pgm_mcs48_delay_4tcy();
            
        for (attempt = 1; attempt <= stopat; attempt++)
        {
            uint8_t data;
            uint8_t temp = chunk[i];

            if (temp != _g_blankByte)
            {
                if (_g_devType != DEV_8755)
                    pgm_mcs48_8755_test0_or_prog_disable(); // Target data bus = input

                pgm_dir_out();

                pgm_write_data(temp); // Present data
                pgm_mcs48_delay_4tcy();

                if (_g_devType != DEV_8755)
                {
                    pgm_mcs48_vdd_enable(); // Programming power on
                    pgm_mcs48_delay_pre_post_vdd();
                    pgm_mcs48_prog_enable(); // Programming pulse on
                    pgm_mcs48_delay_write(); 
                    pgm_mcs48_prog_disable(); // Programming pulse off
                    pgm_mcs48_delay_pre_post_vdd();
                    pgm_mcs48_vdd_disable(); // Programming power off
                }
                else
                {
                    pgm_mcs48_8755_test0_or_prog_enable();
                    pgm_mcs48_delay_4tcy();
                    pgm_mcs48_vdd_enable(); // Programming pulse on
                    pgm_mcs48_delay_write(); 
                    pgm_mcs48_vdd_disable(); // Programming pulse off
                    pgm_mcs48_delay_4tcy();
                    pgm_mcs48_8755_test0_or_prog_disable();
                }

                pgm_mcs48_delay_4tcy();
            }

            if (_g_useHts)
            {
                /* Read back data */
                pgm_dir_in();

                if (_g_devType == DEV_8755)
                {
                    pgm_8755_rd_enable();
                    pgm_mcs48_delay_4tcy();
                }
                else
                {
                    pgm_mcs48_8755_test0_or_prog_enable(); // Target data bus = output
                }

                pgm_mcs48_delay_pre_read();
                data = pgm_read_data();

                if (_g_devType == DEV_8755)
                    pgm_8755_rd_disable();

                pgm_mcs48_delay_4tcy();
#ifdef _DEBUG
                printf("pgm_mcs48_write_chunk() data=0x%02X chunk[i]=0x%02X attempt=%d\r\n", data, chunk[i], attempt);
#endif /* _DEBUG */

                if (data == chunk[i] && verified == 0)
                {
                    verified = 1;
                    break;
                }
            }
            else
            {
                verified = 1;
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
        host_write32(_g_totalWrites);
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
        uint16_t thisOffset = (_g_offset + i);
        uint8_t data;
        pgm_dir_out();

        if (_g_devType == DEV_8755)
            pgm_mcs48_8755_reset_or_ale_enable();

        pgm_write_data((uint8_t)(thisOffset & 0xFF));
        pgm_write_address(thisOffset & 0xF00); /* Output address */
        pgm_mcs48_delay_4tcy();
        pgm_mcs48_8755_reset_or_ale_disable();

        pgm_dir_in();
        pgm_mcs48_delay_4tcy();

        if (_g_devType == DEV_8741 || _g_devType == DEV_8041)
        {
            // Unlike the rest of the MCS-48 family, the 8741 datasheet does not explicitly tell us what we have to
            // do with TEST0 when reading back the EPROM. Much experimentation finds that it cannot be left at 5V
            // as with other parts. Instead it must be asserted before reading a byte, then de-asserted thereafter.
            pgm_mcs48_8755_test0_or_prog_enable();
            pgm_mcs48_delay_4tcy();
        }

        if (_g_devType == DEV_8755)
        {
            pgm_8755_rd_enable();
            pgm_mcs48_delay_4tcy();
        }

        data = pgm_read_data();

        if (_g_devType == DEV_8741 || _g_devType == DEV_8041)
            pgm_mcs48_8755_test0_or_prog_disable();

        if (_g_devType == DEV_8755)
            pgm_8755_rd_disable();
        else
            pgm_mcs48_8755_reset_or_ale_enable();

        pgm_mcs48_delay_4tcy();
        host_write8(data);

#ifdef _DEBUG
        printf("pgm_mcs48_read_chunk() thisOffset=%d data=0x%02X\r\n", thisOffset, data);
#endif /* _DEBUG */

    }

    _g_offset += thisChunk;
}

void pgm_mcs48_blank_check(void)
{
    uint16_t offset = 0;
    uint8_t data = 0xAA;

    while (offset < _g_devSize)
    {
        pgm_dir_out();

        if (_g_devType == DEV_8755)
            pgm_mcs48_8755_reset_or_ale_enable();

        pgm_write_data((uint8_t)(offset & 0xFF));
        pgm_write_address(offset & 0xF00); /* Output address */
        pgm_mcs48_delay_4tcy();
        pgm_mcs48_8755_reset_or_ale_disable();
        pgm_mcs48_delay_4tcy();
        pgm_dir_in();
        pgm_mcs48_delay_4tcy();

        if (_g_devType == DEV_8741 || _g_devType == DEV_8041)
        {
            // Unlike the rest of the MCS-48 family, the 8741 datasheet does not explicitly tell us what we have to
            // do with TEST0 when reading back the EPROM. Much experimentation finds that it cannot be left at 5V
            // as with other parts. Instead it must be asserted before reading a byte, then de-asserted thereafter.
            pgm_mcs48_8755_test0_or_prog_enable();
            pgm_mcs48_delay_4tcy();
        }

        if (_g_devType == DEV_8755)
        {
            pgm_8755_rd_enable();
            pgm_mcs48_delay_4tcy();
        }

        data = pgm_read_data();

        if (_g_devType == DEV_8741 || _g_devType == DEV_8041)
            pgm_mcs48_8755_test0_or_prog_disable();

        if (_g_devType == DEV_8755)
            pgm_8755_rd_disable();
        else
            pgm_mcs48_8755_reset_or_ale_enable();

        pgm_mcs48_delay_4tcy();

        if (data != _g_blankByte)
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

void pgm_mcs48_start_write(void)
{
    _g_useHts = host_read8();
    host_read8();

#ifdef _DEBUG
    printf("pgm_mcs48_start_write() _g_useHts=%d\r\n", _g_useHts);
#endif /* _DEBUG */

    if (_g_devType == DEV_8048 || _g_devType == DEV_8049 || _g_devType == DEV_8050)
    {
        cmd_respond(CMD_START_WRITE, ERR_INVALID_CMD);
        return;
    }

    pgm_mcs48_power_on();

    pgm_mcs48_ea_enable();

    if (_g_devType == DEV_8755)
        pgm_mcs48_8755_test0_or_prog_disable();
    else
        pgm_mcs48_8755_test0_or_prog_enable();

    if (_g_devType == DEV_8755)
        pgm_mcs48_8755_reset_or_ale_disable(); 
    else
        pgm_mcs48_8755_reset_or_ale_enable(); 

    cmd_respond(CMD_START_WRITE, ERR_OK);
}

void pgm_mcs48_start_read(void)
{
#ifdef _DEBUG
    printf("pgm_mcs48_start_read()\r\n");
#endif /* _DEBUG */

    pgm_mcs48_power_on();

    pgm_mcs48_ea_enable();

    if (_g_devType == DEV_8741 || _g_devType == DEV_8041 || _g_devType == DEV_8755)
        pgm_mcs48_8755_test0_or_prog_disable();
    else
        pgm_mcs48_8755_test0_or_prog_enable();

    if (_g_devType == DEV_8755)
        pgm_mcs48_8755_reset_or_ale_disable(); 
    else
        pgm_mcs48_8755_reset_or_ale_enable(); 

    cmd_respond(CMD_START_READ, ERR_OK);
}

void pgm_mcs48_start_blank_check(void)
{
#ifdef _DEBUG
    printf("pgm_mcs48_start_blank_check()\r\n");
#endif /* _DEBUG */

    if (_g_devType == DEV_8048 || _g_devType == DEV_8049 || _g_devType == DEV_8050)
    {
        cmd_respond(CMD_START_BLANK_CHECK, ERR_INVALID_CMD);
        return;
    }

    pgm_mcs48_power_on();

    pgm_mcs48_ea_enable();

    if (_g_devType == DEV_8741 || _g_devType == DEV_8755)
        pgm_mcs48_8755_test0_or_prog_disable();
    else
        pgm_mcs48_8755_test0_or_prog_enable();

    if (_g_devType == DEV_8755)
        pgm_mcs48_8755_reset_or_ale_disable(); 
    else
        pgm_mcs48_8755_reset_or_ale_enable(); 

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
        case TEST_MCS48_VDD_21V:
            _g_devType = DEV_8748;
            pgm_mcs48_power_on();
            pgm_mcs48_vdd_enable();
            break;
        case TEST_MCS48_VDD_25V:
            _g_devType = DEV_8741;
            pgm_mcs48_power_on();
            pgm_mcs48_vdd_enable();
            break;
        case TEST_MCS48_EA_12V:
            _g_devType = DEV_8048;
            pgm_mcs48_power_on();
            pgm_mcs48_ea_enable();
            break;
        case TEST_MCS48_EA_18V:
            _g_devType = DEV_8748;
            pgm_mcs48_power_on();
            pgm_mcs48_ea_enable();
            break;
        case TEST_MCS48_EA_22V:
            _g_devType = DEV_8741;
            pgm_mcs48_power_on();
            pgm_mcs48_ea_enable();
            break;
        case TEST_MCS48_PROG:
            _g_devType = DEV_8748;
            pgm_mcs48_power_on();
            pgm_mcs48_prog_enable();
            break;
        case TEST_MCS48_AA:
            pgm_mcs48_power_on();
            pgm_dir_out();
            pgm_write_data(0xAA);
            pgm_write_address(0xA00);
            pgm_mcs48_8755_test0_or_prog_disable();
            pgm_mcs48_8755_reset_or_ale_disable();
            break;
        case TEST_MCS48_55:
            pgm_mcs48_power_on();
            pgm_dir_out();
            pgm_write_data(0x55);
            pgm_write_address(0x500);
            pgm_mcs48_8755_test0_or_prog_enable();
            pgm_mcs48_8755_reset_or_ale_enable();
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
