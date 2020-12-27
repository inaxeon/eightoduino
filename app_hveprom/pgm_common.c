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
#include "sys/adc.h"
#include "sys/util.h"
#endif /* _M8OD */

#ifdef _MDUINO
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
#include "adc.h"
#endif /* _MDUINO */

#include "iopins.h"
#include "usart_buffered.h"
#include "util.h"
#include "pgm_common.h"
#include "pgm_1702a.h"
#include "pgm_270x_mcm6876x.h"
#include "pgm_mcs48.h"

static int8_t pgm_setup_dev_type(uint8_t cmd);
static void pgm_start_write(void);
static void pgm_start_read(void);
static void pgm_write_chunk(void);
static void pgm_read_chunk(void);
static void pgm_start_blank_check(void);
static void pgm_blank_check(void);
static void pgm_reset(void);
static void pgm_measure_12v(void);
static void pgm_test(void);
static void pgm_test_read(void);

uint8_t _g_shieldType;

void pgm_process_command(uint8_t cmd)
{
    switch (cmd)
    {
    case CMD_START_WRITE:
        pgm_start_write();
        break;
    case CMD_WRITE_CHUNK:
        pgm_write_chunk();
        break;
    case CMD_START_READ:
        pgm_start_read();
        break;
    case CMD_READ_CHUNK:
        pgm_read_chunk();
        break;
    case CMD_START_BLANK_CHECK:
        pgm_start_blank_check();
        break;
    case CMD_BLANK_CHECK:
        pgm_blank_check();
        break;
    case CMD_MEASURE_12V:
        pgm_measure_12v();
        break;
    case CMD_DEV_RESET:
        pgm_reset();
        break;
    case CMD_TEST:
        pgm_test();
        break;
    case CMD_TEST_READ:
        pgm_test_read();
        break;
    default:
        break;
    }
}

void pgm_init(uint8_t shieldType)
{
    _g_shieldType = shieldType;

    pgm_write_address(0x0);

    // PORTD is output only on 8OD
    
#ifdef _MDUINO
    ADDRESS_0_DDR |= _BV(ADDRESS_0);
    ADDRESS_1_DDR |= _BV(ADDRESS_1);
    ADDRESS_2_DDR |= _BV(ADDRESS_2);
    ADDRESS_3_DDR |= _BV(ADDRESS_3);
    ADDRESS_4_DDR |= _BV(ADDRESS_4);
    ADDRESS_5_DDR |= _BV(ADDRESS_5);
    ADDRESS_6_DDR |= _BV(ADDRESS_6);
    ADDRESS_7_DDR |= _BV(ADDRESS_7);
    ADDRESS_8_DDR |= _BV(ADDRESS_8);
    ADDRESS_9_DDR |= _BV(ADDRESS_9);
    ADDRESS_10_DDR |= _BV(ADDRESS_10);
    ADDRESS_11_DDR |= _BV(ADDRESS_11);
    ADDRESS_12_DDR |= _BV(ADDRESS_12);
#endif /* _MDUINO */

    pgm_dir_in();

    if (shieldType == SHIELD_TYPE_1702A)
        pgm_1702a_init();

    if (shieldType == SHIELD_TYPE_270X_MCM6876X)
        pgm_270x_mcm6876x_init();

    if (shieldType == SHIELD_TYPE_MCS48)
        pgm_mcs48_init();
}

static void pgm_start_write(void)
{
    if (pgm_setup_dev_type(CMD_START_WRITE) < 0)
        return;

    if (_g_shieldType == SHIELD_TYPE_1702A)
        pgm_1702a_start_write();
    if (_g_shieldType == SHIELD_TYPE_270X_MCM6876X)
        pgm_270x_mcm6876x_start_write();
    if (_g_shieldType == SHIELD_TYPE_MCS48)
        pgm_mcs48_start_write();
}

static void pgm_start_read(void)
{
    if (pgm_setup_dev_type(CMD_START_READ) < 0)
        return;

    if (_g_shieldType == SHIELD_TYPE_1702A)
        pgm_1702a_start_read();
    if (_g_shieldType == SHIELD_TYPE_270X_MCM6876X)
        pgm_270x_mcm6876x_start_read();
    if (_g_shieldType == SHIELD_TYPE_MCS48)
        pgm_mcs48_start_read();
}

static void pgm_write_chunk(void)
{
    if (_g_shieldType == SHIELD_TYPE_1702A)
        pgm_1702a_write_chunk();
    if (_g_shieldType == SHIELD_TYPE_270X_MCM6876X)
        pgm_270x_mcm6876x_write_chunk();
    if (_g_shieldType == SHIELD_TYPE_MCS48)
        pgm_mcs48_write_chunk();
}

static void pgm_read_chunk(void)
{
    if (_g_shieldType == SHIELD_TYPE_1702A)
        pgm_1702a_read_chunk();
    if (_g_shieldType == SHIELD_TYPE_270X_MCM6876X)
        pgm_270x_mcm6876x_read_chunk();
    if (_g_shieldType == SHIELD_TYPE_MCS48)
        pgm_mcs48_read_chunk();
}

static void pgm_start_blank_check(void)
{
    if (pgm_setup_dev_type(CMD_START_BLANK_CHECK) < 0)
        return;

    if (_g_shieldType == SHIELD_TYPE_1702A)
        pgm_1702a_start_blank_check();
    if (_g_shieldType == SHIELD_TYPE_270X_MCM6876X)
        pgm_270x_mcm6876x_start_blank_check();
    if (_g_shieldType == SHIELD_TYPE_MCS48)
        pgm_mcs48_start_blank_check();
}

static void pgm_blank_check(void)
{
    if (_g_shieldType == SHIELD_TYPE_1702A)
        pgm_1702a_blank_check();
    if (_g_shieldType == SHIELD_TYPE_270X_MCM6876X)
        pgm_270x_mcm6876x_blank_check();
    if (_g_shieldType == SHIELD_TYPE_MCS48)
        pgm_mcs48_blank_check();
}

static void pgm_reset(void)
{
    if (_g_shieldType == SHIELD_TYPE_1702A)
        pgm_1702a_reset();
    if (_g_shieldType == SHIELD_TYPE_270X_MCM6876X)
        pgm_270x_mcm6876x_reset();
    if (_g_shieldType == SHIELD_TYPE_MCS48)
        pgm_mcs48_reset();
}

static void pgm_test(void)
{
    if (pgm_setup_dev_type(CMD_TEST) < 0)
        return;

    if (_g_shieldType == SHIELD_TYPE_1702A)
        pgm_1702a_test();
    if (_g_shieldType == SHIELD_TYPE_270X_MCM6876X)
        pgm_270x_mcm6876x_test();
    if (_g_shieldType == SHIELD_TYPE_MCS48)
        pgm_mcs48_test();
}

static void pgm_test_read(void)
{
    if (pgm_setup_dev_type(CMD_TEST) < 0)
        return;

    if (_g_shieldType == SHIELD_TYPE_1702A)
        pgm_1702a_test_read();
    if (_g_shieldType == SHIELD_TYPE_270X_MCM6876X)
        pgm_270x_mcm6876x_test_read();
    if (_g_shieldType == SHIELD_TYPE_MCS48)
        pgm_mcs48_test_read();
}

static void pgm_measure_12v(void)
{
    uint32_t reading;

#ifdef _DEBUG
    printf("pgm_measure_12v()\r\n");
#endif /* _DEBUG */

    cmd_respond(CMD_MEASURE_12V, ERR_OK);

#ifdef _M8OD
    /*
     * 4096 (0xFFF) = Vref = 3.3v
     * 3.3 / 4096 = 0.0008056640625
     * 
     * R1 = 10K
     * R2 = 2.2K
     * R2 / (R1+R2) = 0.180327868852459
     * 
     * 0.0008056640625 * 1000000 = 805.6640625
     * 0.180327868852459 * 10000 = 1803.27868852459
     * 1000000 / 10000 = 100
     * Therefore: Result = Vin * 100
     */
    reading = adc_read_channel(0);
    reading *= 806;
    reading /= 1803;
#endif /* _M8OD */

#ifdef _MDUINO
    reading = adc_read_12v();
#endif /* _MDUINO */

    host_write16((uint16_t)reading);
}

static int8_t pgm_setup_dev_type(uint8_t cmd)
{
    uint8_t devtype = host_read8();

    switch (devtype)
    {
    case DEV_1702A:
        if (_g_shieldType != SHIELD_TYPE_1702A)
            goto err_wrongshield;
        pgm_1702a_set_params();
        break;
    case DEV_C2704:
        if (_g_shieldType != SHIELD_TYPE_270X_MCM6876X)
            goto err_wrongshield;
        if (!pgm_270x_mcm6876x_check_switch(DEV_C2704))
            goto err_wrongswitch;
        pgm_270x_mcm6876x_set_params(DEV_C2704, 0x200, C270X_MAX_RETRIES);
        break;
    case DEV_C2708:
        if (_g_shieldType != SHIELD_TYPE_270X_MCM6876X)
            goto err_wrongshield;
        if (!pgm_270x_mcm6876x_check_switch(DEV_C2708))
            goto err_wrongswitch;
        pgm_270x_mcm6876x_set_params(DEV_C2708, 0x400, C270X_MAX_RETRIES);
        break;
    case DEV_MCM6876X:
        if (_g_shieldType != SHIELD_TYPE_270X_MCM6876X)
            goto err_wrongshield;
        if (!pgm_270x_mcm6876x_check_switch(DEV_MCM6876X))
            goto err_wrongswitch;
        pgm_270x_mcm6876x_set_params(DEV_MCM6876X, 0x2000, MCM6876X_MAX_RETRIES);
        break;
    case DEV_8741:
    case DEV_8748:
    case DEV_8048:
        if (_g_shieldType != SHIELD_TYPE_MCS48)
            goto err_wrongshield;
        pgm_mcs48_set_params(devtype, 0x400, MCS48_MAX_RETRIES);
        break;
    case DEV_8742:
    case DEV_8749:
    case DEV_8049:
        if (_g_shieldType != SHIELD_TYPE_MCS48)
            goto err_wrongshield;
        pgm_mcs48_set_params(devtype, 0x800, MCS48_MAX_RETRIES);
        break;
    case DEV_8050:
        if (_g_shieldType != SHIELD_TYPE_MCS48)
            goto err_wrongshield;
        pgm_mcs48_set_params(devtype, 0x1000, MCS48_MAX_RETRIES);
        break;
    default:
#ifdef _DEBUG
        printf("Invalid device type: %d\r\n", devtype);
#endif /* _DEBUG */
        cmd_respond(cmd, ERR_NOT_SUPPORTED);
        return -1;
    }

#ifdef _DEBUG
    printf("Setting device type: %d\r\n", devtype);
#endif /* _DEBUG */

    return 0;

err_wrongshield:
#ifdef _DEBUG
        printf("Invalid shield type: %d dev: %d\r\n", _g_shieldType, devtype);
#endif /* _DEBUG */
    cmd_respond(cmd, ERR_INCORRECT_HW);
    return -1;
err_wrongswitch:
#ifdef _DEBUG
        printf("Switch in wrong position: %d\r\n", devtype);
#endif /* _DEBUG */
    cmd_respond(cmd, ERR_INCORRECT_SWITCH_POS);
    return -1;
}

void pgm_write_address(uint16_t address)
{
#ifdef _M8OD
    cpld_direct_write(PORTD, address);
#endif /* _M8OD */

#ifdef _MDUINO
    if (address & _BV(0))
        ADDRESS_0_PORT |= _BV(ADDRESS_0);
    else
        ADDRESS_0_PORT &= ~_BV(ADDRESS_0);

    if (address & _BV(1))
        ADDRESS_1_PORT |= _BV(ADDRESS_1);
    else
        ADDRESS_1_PORT &= ~_BV(ADDRESS_1);

    if (address & _BV(2))
        ADDRESS_2_PORT |= _BV(ADDRESS_2);
    else
        ADDRESS_2_PORT &= ~_BV(ADDRESS_2);

    if (address & _BV(3))
        ADDRESS_3_PORT |= _BV(ADDRESS_3);
    else
        ADDRESS_3_PORT &= ~_BV(ADDRESS_3);

    if (address & _BV(4))
        ADDRESS_4_PORT |= _BV(ADDRESS_4);
    else
        ADDRESS_4_PORT &= ~_BV(ADDRESS_4);

    if (address & _BV(5))
        ADDRESS_5_PORT |= _BV(ADDRESS_5);
    else
        ADDRESS_5_PORT &= ~_BV(ADDRESS_5);

    if (address & _BV(6))
        ADDRESS_6_PORT |= _BV(ADDRESS_6);
    else
        ADDRESS_6_PORT &= ~_BV(ADDRESS_6);

    if (address & _BV(7))
        ADDRESS_7_PORT |= _BV(ADDRESS_7);
    else
        ADDRESS_7_PORT &= ~_BV(ADDRESS_7);

    if (address & _BV(8))
        ADDRESS_8_PORT |= _BV(ADDRESS_8);
    else
        ADDRESS_8_PORT &= ~_BV(ADDRESS_8);

    if (address & _BV(9))
        ADDRESS_9_PORT |= _BV(ADDRESS_9);
    else
        ADDRESS_9_PORT &= ~_BV(ADDRESS_9);

    if (address & _BV(10))
        ADDRESS_10_PORT |= _BV(ADDRESS_10);
    else
        ADDRESS_10_PORT &= ~_BV(ADDRESS_10);

    if (address & _BV(11))
        ADDRESS_11_PORT |= _BV(ADDRESS_11);
    else
        ADDRESS_11_PORT &= ~_BV(ADDRESS_11);

    if (address & _BV(12))
        ADDRESS_12_PORT |= _BV(ADDRESS_12);
    else
        ADDRESS_12_PORT &= ~_BV(ADDRESS_12);
#endif /* _MDUINO */
}

void pgm_write_data(uint8_t data)
{
#ifdef _M8OD
    cpld_direct_write(PORTC, data);
#endif /* _M8OD */

#ifdef _MDUINO
    DATA_PORT = data;
#endif /* _MDUINO */
}

uint8_t pgm_read_data(void)
{
#ifdef _M8OD
    return (uint8_t)cpld_read(PORTC);
#endif /* _M8OD */

#ifdef _MDUINO
    return DATA_PIN;
#endif /* _MDUINO */
}

void pgm_dir_out(void)
{
#ifdef _M8OD
    cpld_direct_write(TRISC, 0);
#endif /* _M8OD */

#ifdef _MDUINO
    DATA_DDR = 0xFF;
#endif /* _MDUINO */
}

void pgm_dir_in(void)
{
#ifdef _M8OD
    cpld_direct_write(TRISC, 0xFFFF);
#endif /* _M8OD */

#ifdef _MDUINO
    DATA_DDR = 0x00;
#endif /* _MDUINO */
}
