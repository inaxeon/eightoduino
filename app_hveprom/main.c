/*
 *   8OD - Arduino form factor i8086 based SBC
 *   Matthew Millman (tech.mattmillman.com/8od)
 *
 *   2704/2708/MCM68764/MCM68766 EPROM Programmer
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
#include <stdio.h>
#include <stddef.h>
#include <string.h>

#ifdef _M8OD
#include "eod_io.h"
#include "uart.h"
#include "util.h"
#endif /* _M8OD */


#define CMD_START_WRITE          0x10
#define CMD_WRITE_CHUNK          0x11
#define CMD_START_READ           0x12
#define CMD_READ_CHUNK           0x13
#define CMD_BLANK_CHECK          0x14
#define CMD_DEV_RESET            0x15

#define DEV_C2704                0x01
#define DEV_C2708                0x02
#define DEV_MCM6876X             0x03

#define ERR_OK                   0x00
#define ERR_COMPLETE             0x01
#define ERR_INVALID_CMD          0x02
#define ERR_NOT_SUPPORTED        0x03
#define ERR_NO_DEV               0x04
#define ERR_INCORRECT_HW         0x05
#define ERR_NOT_BLANK            0x06
#define ERR_MAX_RETRIES          0x07

#define READ_CHUNK_SIZE          8
#define WRITE_CHUNK_SIZE         16
#define MCM6876X_MAX_RETRIES     25
#define C270X_MAX_RETRIES        100

static int8_t cmd_get_next(void);
static int8_t cmd_setup_dev_type(uint8_t cmd);
static void cmd_start_write(void);
static void cmd_write_chunk(void);
static void cmd_start_read(void);
static void cmd_read_chunk(void);
static void cmd_blank_check(void);

uint16_t _g_devSize;
uint16_t _g_offset;
uint8_t _g_maxPerByteWrites;
uint8_t _g_useHts;
uint8_t _g_extraWrites;
uint8_t _g_maxRetries;
uint32_t _g_totalWrites;
int8_t _g_devType;

//#define _DEBUG

#ifdef _M8OD

#define HOST_UART   UARTB
#define DEBUG_UART  UARTA

#define WR_EN     0x0004
#define RD_EN     0x0008
#define PE_EN     0x0010
#define PWR_EN    0x0020

#define CTRL_MASK (WR_EN | RD_EN | PE_EN | PWR_EN)

#define cmd_retry_delay() delay_ncycles(1 * 554)
#define cmd_respond(cmd, x) do { uart_putc(HOST_UART, cmd); uart_putc(HOST_UART, x); } while (0)
#define host_read8() uart_blocking_getc(HOST_UART)
#define host_try_read8(x) uart_getc(HOST_UART, x)
#define host_write8(x) uart_putc(HOST_UART, x)
#define host_write16(x) do { uart_putc(HOST_UART, ((uint8_t)(((uint16_t)x) >> 8)));    \
                             uart_putc(HOST_UART, ((uint8_t)(((uint16_t)x) & 0xFF)));  \
                           } while (0)
#define host_write32(x) do { uart_putc(HOST_UART, ((uint8_t)(((uint32_t)x) >> 24)));   \
                             uart_putc(HOST_UART, ((uint8_t)(((uint32_t)x) >> 16)));   \
                             uart_putc(HOST_UART, ((uint8_t)(((uint32_t)x) >> 8)));    \
                             uart_putc(HOST_UART, ((uint8_t)(((uint32_t)x) & 0xFF)));  \
                           } while (0)
#define dev_read_data() cpld_read(PORTC)
#define dev_write_data(x) cpld_direct_write(PORTC, x)
#define delay_read()
#define delay_ad_setup() delay_ncycles(1)
#define delay_ad_hold() delay_ncycles(1)
#define delay_write_mcm6876x() delay_ncycles(870)
#define delay_write_270x() delay_ncycles(530)
#define dev_wr_enable() cpld_write(PORTA, WR_EN, WR_EN)
#define dev_wr_disable() cpld_write(PORTA, WR_EN, 0)
#define dev_rd_enable() cpld_write(PORTA, RD_EN, RD_EN)
#define dev_rd_disable() cpld_write(PORTA, RD_EN, 0)
#define dev_pe_enable() cpld_write(PORTA, PE_EN, PE_EN)
#define dev_pe_disable() cpld_write(PORTA, PE_EN, 0)
#define dev_write_address(x) cpld_direct_write(PORTD, x)
#define dev_dir_out() cpld_direct_write(TRISC, 0)
#define dev_dir_in() cpld_direct_write(TRISC, 0xFFFF)

#endif /* _M8OD */

#ifdef _MDUINO

#endif /* _MDUINO */

void interrupt_handler(void)
{
    /* Unused */
}

void main(void)
{
#ifdef _M8OD
    uart_open(HOST_UART, 115200, 8, PARITY_NONE, 1, 0);
#ifdef _DEBUG
    uart_open(DEBUG_UART, 115200, 8, PARITY_NONE, 1, 0);
    setup_printf(DEBUG_UART);
#endif /* _DEBUG */
    cpld_write(TRISA, CTRL_MASK, 0); /* 3, 4, 5 and 6 = output */
    cpld_direct_write(TRISC, 0xFFFF); /* All inputs */
    cpld_write(PORTA, CTRL_MASK, 0); /* 3, 4, 5 and 6 = off */
    cpld_direct_write(PORTD, 0x0000);
#endif  /* _M8OD */

#ifdef _MDUINO

#endif /* _MDUINO */

    _g_devSize = 0;
    _g_maxPerByteWrites = 0;
    _g_totalWrites = 0;
    _g_maxRetries = 0;
    _g_devType = -1;

#ifdef _DEBUG
    printf("Starting...\r\n");
#endif /* _DEBUG */

    for (;;)
    {
        int cmd = cmd_get_next();
        if (cmd < 0)
            continue;

#ifdef _DEBUG
        printf("Got command: %d\r\n", cmd);
#endif /* _DEBUG */

        switch (cmd)
        {
        case CMD_START_WRITE:
            cmd_start_write();
            break;
        case CMD_WRITE_CHUNK:
            cmd_write_chunk();
            break;
        case CMD_START_READ:
            cmd_start_read();
            break;
        case CMD_READ_CHUNK:
            cmd_read_chunk();
            break;
        case CMD_BLANK_CHECK:
            cmd_blank_check();
            break;
        case CMD_DEV_RESET:
            dev_reset();
            cmd_respond(CMD_DEV_RESET, ERR_OK);
            break;
        default:
            continue;
        }
    }
}

uint8_t fix_data8(uint8_t data)
{
    uint8_t ret;

    ret = 0;

    if (data & 0x01)
        ret |= 0x02;

    if (data & 0x02)
        ret |= 0x01;

    if (data & 0x04)
        ret |= 0x08;

    if (data & 0x08)
        ret |= 0x20;

    if (data & 0x10)
        ret |= 0x04;

    if (data & 0x20)
        ret |= 0x10;

    if (data & 0x40)
        ret |= 0x80;

    if (data & 0x80)
        ret |= 0x40;

    return ret;
}

uint8_t fix_data8r(uint8_t data)
{
    uint8_t ret;

    ret = 0;

    if (data & 0x02)
        ret |= 0x01;

    if (data & 0x01)
        ret |= 0x02;

    if (data & 0x08)
        ret |= 0x04;

    if (data & 0x20)
        ret |= 0x08;

    if (data & 0x04)
        ret |= 0x10;

    if (data & 0x10)
        ret |= 0x20;

    if (data & 0x80)
        ret |= 0x40;

    if (data & 0x40)
        ret |= 0x80;

    return ret;
}

uint16_t fix_data16(uint16_t data)
{
    uint16_t even_bits;
    uint16_t odd_bits;

    even_bits = (uint16_t)(data & 0xAAAA); 
    odd_bits  = (uint16_t)(data & 0x5555);
    even_bits >>= 1;
    odd_bits <<= 1;
    return (uint16_t)(even_bits | odd_bits);
}

static void dev_setup()
{
#ifdef _M8OD
    cpld_write(PORTA, PWR_EN, PWR_EN);
#endif  /* _M8OD */

    delay_ncycles(0xFFFF);
}

static void dev_reset()
{
    dev_pe_disable();
    dev_rd_disable();
    dev_wr_disable();

    delay_ncycles(0xFFFF);

#ifdef _M8OD
    cpld_write(PORTA, PWR_EN, 0); /* Power off */
    cpld_direct_write(TRISC, 0xFFFF); /* All inputs */
#endif  /* _M8OD */
}

static int8_t cmd_get_next(void)
{
    uint8_t c;
    if (host_try_read8(&c))
    {
        uint8_t i = 0;
        uint8_t d;

        for (i = 0; i < 100; i++)
        {
            if (host_try_read8(&d))
            {
                if ((uint8_t)~d == c)
                {
                    switch (c)
                    {
                    case CMD_START_WRITE:
                    case CMD_WRITE_CHUNK:
                    case CMD_START_READ:
                    case CMD_READ_CHUNK:
                    case CMD_BLANK_CHECK:
                    case CMD_DEV_RESET:
                        return c;
                    default:
                        return -1;
                    }
                }
                else
                {
#ifdef _DEBUG
                    printf("Command compliment byte wrong. Got: 0x%02X 0x%02X\r\n", c, d);
#endif /* _DEBUG */
                    return -1;
                }
            }
            cmd_retry_delay();
        }
    }

    return -1;
}

static int8_t cmd_setup_dev_type(uint8_t cmd)
{
    uint8_t devtype = host_read8();

    switch (devtype)
    {
    case DEV_C2704:
        _g_devSize = 0x200;
        _g_maxRetries = C270X_MAX_RETRIES;
        break;
    case DEV_C2708:
        _g_devSize = 0x400;
        _g_maxRetries = C270X_MAX_RETRIES;
        break;
    case DEV_MCM6876X:
        _g_devSize = 0x2000;
        _g_maxRetries = MCM6876X_MAX_RETRIES;
        break;
    default:
#ifdef _DEBUG
        printf("Invalid device type: %d\r\n", devtype);
#endif /* _DEBUG */
        cmd_respond(cmd, ERR_NOT_SUPPORTED);
        _g_devType = -1;
        return -1;
    }

#ifdef _DEBUG
    printf("Setting device type: %d\r\n", devtype);
#endif /* _DEBUG */

    _g_offset = 0;
    _g_maxPerByteWrites = 0;
    _g_totalWrites = 0;
    _g_devType = devtype;

    return 0;
}

static void cmd_start_write(void)
{
    if (cmd_setup_dev_type(CMD_START_WRITE) < 0)
        return;

    _g_useHts = host_read8();
    _g_extraWrites = host_read8();

#ifdef _DEBUG
    printf("cmd_start_write() _g_useHts=%d _g_extraWrites=%d\r\n", _g_useHts, _g_extraWrites);
#endif /* _DEBUG */

    dev_setup();

    cmd_respond(CMD_START_WRITE, ERR_OK);
}

static void cmd_write_chunk(void)
{
    uint8_t chunk[WRITE_CHUNK_SIZE];
    uint8_t attempt;
    int16_t remaining = (_g_devSize - _g_offset);
    uint8_t i;
    uint16_t thisChunk = remaining > WRITE_CHUNK_SIZE ? WRITE_CHUNK_SIZE : remaining;

#ifdef _DEBUG
    printf("cmd_write_chunk() thisChunk=%d remaining=%d _g_offset=%d\r\n", thisChunk, remaining, _g_offset);
#endif /* _DEBUG */

    /* The host is going to shove all of the data in at once, so we have to buffer it */
    for (i = 0; i < thisChunk; i++)
        chunk[i] = host_read8();

    /* Now get writing it */
    for (i = 0; i < thisChunk; i++)
    {
        uint8_t verified = 0;
        uint8_t stopat = _g_useHts ? _g_maxRetries : 1;
        dev_write_address(fix_data16(_g_offset + i)); /* Output address */

        for (attempt = 0; attempt < stopat; attempt++)
        {
            uint8_t data;
            uint8_t temp = fix_data8(chunk[i]);

            /* Present data */
            dev_pe_enable();
            delay_read();
            dev_dir_out();
            dev_write_data(temp);
            delay_ad_setup();

            /* Pulse Vpp */
            dev_wr_enable();
            
            if (_g_devType == DEV_MCM6876X)
                delay_write_mcm6876x(); /* 2ms */
            else
                delay_write_270x(); /* 1ms */

            dev_wr_disable();

            delay_ad_hold();

            dev_dir_in();
            dev_pe_disable();

            if (_g_useHts)
            {
                /* Read back data */
                delay_read();
                dev_rd_enable();
                delay_read();
                data = fix_data8r(dev_read_data());
                dev_rd_disable();

#ifdef _DEBUG
                printf("cmd_write_chunk() data=0x%02X chunk[i]=0x%02X attempt=%d\r\n", data, chunk[i], attempt);
#endif /* _DEBUG */

                if (data == chunk[i] && verified == 0)
                {
                    verified = 1;
                    stopat = attempt + _g_extraWrites;
#ifdef _DEBUG
                    printf("cmd_write_chunk() data verified. Setting stopat to %d\r\n", stopat);
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

static void cmd_start_read(void)
{
#ifdef _DEBUG
    printf("cmd_start_read()\r\n");
#endif /* _DEBUG */

    if (cmd_setup_dev_type(CMD_START_READ) < 0)
        return;

    dev_setup();

    cmd_respond(CMD_START_READ, ERR_OK);
}

static void cmd_read_chunk(void)
{
    int16_t remaining = (_g_devSize - _g_offset);
    uint8_t i;
    int thisChunk = remaining > READ_CHUNK_SIZE ? READ_CHUNK_SIZE : remaining;

    cmd_respond(CMD_READ_CHUNK, (_g_offset + thisChunk) == _g_devSize ? ERR_COMPLETE : ERR_OK);

#ifdef _DEBUG
    printf("cmd_read_chunk() thisChunk=%d remaining=%d _g_offset=%d\r\n", thisChunk, remaining, _g_offset);
#endif /* _DEBUG */

    for (i = 0; i < thisChunk; i++)
    {
        dev_write_address(fix_data16(_g_offset + i)); /* Output address */

        /* Read data */
        delay_read();
        dev_rd_enable();
        delay_read();
        host_write8(fix_data8r(dev_read_data()));
        dev_rd_disable();
        delay_read();
    }

    _g_offset += thisChunk;
}

static void cmd_blank_check(void)
{
    uint16_t offset = 0;
    uint8_t data;

    if (cmd_setup_dev_type(CMD_BLANK_CHECK) < 0)
        return;

    dev_setup();

    while (offset < _g_devSize)
    {
        dev_write_address(fix_data16(offset)); /* Output address */
        delay_read();

        dev_rd_enable();
        delay_read();
        data = dev_read_data();
        dev_rd_disable();
        delay_read();

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
        host_write8(fix_data8r(data));
    }
}
