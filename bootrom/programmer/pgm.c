/*
 *   8OD - Arduino form factor i8086 based SBC
 *   Matthew Millman (tech.mattmillman.com)
 *
 *   Serial flash programming interface
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

#include "eod_io.h"
#include "uart.h"
#include "flash.h"
#include "norflash.h"
#include "spiflash.h"
#include "pgm.h"
#include "util.h"
#include "crc8.h"

#define NUM_NEG_WAITS               20000

#define CMD_RESET                   0x01
#define CMD_BOOT                    0x02
#define CMD_READ_PARAMS             0x03
#define CMD_READ                    0x04
#define CMD_ERASE                   0x05
#define CMD_WRITE_PAGE              0x06
#define CMD_LOCK_BOOT               0x07
#define CMD_UNLOCK_BOOT             0x08
#define CMD_LOAD_AND_READ           0x09

#define PGM_UART                    UARTD

static int await_token(uint8_t token, uint8_t reply, uint16_t waitfor);
static int cmd_loop(void);
static void send_data(uint32_t len, void *data);
static void receive_data(uint16_t len, void *data);
static void do_read_params(void);
static void do_read(void);
static void do_write(void);
static void do_erase(void);
static void do_boot_lock(int lock);
static void do_load_and_read(void);
static uint8_t read8(void);
static uint16_t read16(void);
static uint32_t read32(void);

extern int spi_load_and_boot(int);

flash_ops_t const *_g_ops[2];

typedef struct
{
    uint32_t flags;
    uint32_t flash_total_size;
    uint32_t flash_page_size;
    uint32_t flash_boot_offset;
    uint16_t flash_num_blocks;
} device_params_t;

int pgm_main(void)
{
    int ret;

    /* If the flash programmer card is connected, setting EEWP to '1'
     * will also swap over the chip select from EPROM to the flash module.
     *
     * So the EPROM is no longer addressable from this point, which is why
     * this code has to run from RAM.
     */
    cpld_write(CONFIG, CONFIG_EEWP, CONFIG_EEWP);

    uart_pgm_open();

    uart_putc(PGM_UART, 'P');
    uart_putc(PGM_UART, 'G');
    uart_putc(PGM_UART, 'M');

    ret = cmd_loop();

    uart_close(PGM_UART);

    cpld_write(CONFIG, CONFIG_EEWP, 0);

    return ret;
}

static int cmd_loop(void)
{
    while (1)
    {
        char next_cmd;
        next_cmd = uart_blocking_getc(PGM_UART);
        switch (next_cmd)
        {
        case CMD_READ_PARAMS:
            do_read_params();
            break;
        case CMD_RESET:
            uart_putc(PGM_UART, CMD_RESET);
            uart_putc(PGM_UART, 0x01);
            /* Make sure it's all sent before everything gets put into reset */
            uart_wait_tx(PGM_UART);
            return PGM_RESET;
            break;
        case CMD_BOOT:
            uart_putc(PGM_UART, CMD_BOOT);
            uart_putc(PGM_UART, 0x01);
            return PGM_BOOT;
            break;
        case CMD_READ:
            do_read();
            break;
        case CMD_ERASE:
            do_erase();
            break;
        case CMD_WRITE_PAGE:
            do_write();
            break;
        case CMD_LOCK_BOOT:
            do_boot_lock(1);
            break;
        case CMD_UNLOCK_BOOT:
            do_boot_lock(0);
            break;
        case CMD_LOAD_AND_READ:
            return PGM_LOAD_AND_READ;
            break;
        }
    }

    return PGM_BOOT;
}

static void send_device_params(const flash_ops_t *ops, uint32_t dev_flags)
{
    device_params_t info;
    flash_erase_block_t *flash_block_info;
    uint8_t *ptr = (uint8_t *)&info;
    uint32_t flash_erase_size;

    info.flash_total_size = ops->get_geometry(&info.flash_num_blocks, &flash_block_info, &flash_erase_size, &info.flash_boot_offset);
    info.flash_page_size = FLASH_WRITE_SIZE;
    info.flags = 0;

    if (ops->get_bootarea_lock_state())
        info.flags |= FLG_BOOT_LOCKED;

    info.flags |= dev_flags;

    send_data(sizeof(device_params_t), ptr);

    if (info.flash_num_blocks > 0)
    {
        /* block_data_len > 0 is only used to send geometry of non uniform chips.
         * For SPI flashes (uniform), just the size of the erase blocks is sent
         */
        int i;
        for (i = 0; i < info.flash_num_blocks; i++)
            send_data(sizeof(flash_erase_block_t), (void *)&flash_block_info[i]);
    }
    else
    {
        send_data(sizeof(uint32_t), &flash_erase_size);
    }

}

static void do_read_params(void)
{
    uint8_t protocol_version = 3;
    uint8_t numdevices = 0;

    int spipresent = spiflash_is_present();
    int norpresent = norflash_is_present();

    if (spipresent)
    {
        _g_ops[numdevices] = &spi_ops;
        numdevices++;
    }

    if (norpresent)
    {
        _g_ops[numdevices] = &nor_ops;
        numdevices++;
    }

    send_data(1, &protocol_version);
    send_data(1, &numdevices);

    if (spipresent)
    {
        uint32_t dev_flags = 0;
#ifdef _EPROM_
        dev_flags |= FLG_BOOT;
#endif /* _EPROM_ */
        send_device_params(&spi_ops, dev_flags);
    }

    if (norpresent)
    {
        uint32_t dev_flags = 0;
        dev_flags |= FLG_NOR;
#ifndef _EPROM_
        dev_flags |= FLG_BOOT;
#endif /* !_EPROM_ */
        send_device_params(&nor_ops, dev_flags);
    }

    uart_putc(PGM_UART, CMD_READ_PARAMS);
    uart_putc(PGM_UART, 0x01);
}

static void send_data(uint32_t len, void *data)
{
    uint8_t *ptr = (uint8_t *)data;
   
    while (len--)
    {
        uart_putc(PGM_UART, *ptr);
        ptr++;
    }
}

static uint8_t read8(void)
{
    return uart_blocking_getc(PGM_UART);
}

static uint16_t read16(void)
{
    uint16_t ret;

    ret = (uint16_t)uart_blocking_getc(PGM_UART);
    ret |= (uint16_t)uart_blocking_getc(PGM_UART) << 8;

    return ret;
}

static uint32_t read32(void)
{
    uint32_t ret;

    ret = (uint32_t)uart_blocking_getc(PGM_UART);
    ret |= (uint32_t)uart_blocking_getc(PGM_UART) << 8;
    ret |= (uint32_t)uart_blocking_getc(PGM_UART) << 16;
    ret |= (uint32_t)uart_blocking_getc(PGM_UART) << 24;

    return ret;
}

static void do_read(void)
{
    uint8_t opsidx = read8();
    uint32_t offset = read32();
    uint32_t len = read32();

    _g_ops[opsidx]->read_to_uart(offset, len, PGM_UART);

    uart_putc(PGM_UART, CMD_READ);
    uart_putc(PGM_UART, 0x01);
}

static void do_write(void)
{
    uint8_t crc;
    uint8_t opsidx = read8();
    uint32_t offset = read32();
    uint16_t writeLen = read16();
    uint8_t crc_enabled = read8();
    /* The writer tool will not send more than this */
    uint8_t page[FLASH_WRITE_SIZE];
    uint8_t readback[FLASH_WRITE_SIZE];

    if (writeLen > FLASH_WRITE_SIZE)
    {
        uart_putc(PGM_UART, CMD_WRITE_PAGE);
        uart_putc(PGM_UART, 0x00);
    }

    uart_read(PGM_UART, writeLen, page);

    if (crc_enabled)
        crc = (uint8_t)uart_blocking_getc(PGM_UART);

    if (crc_enabled && crc != crc8(0x00, page, writeLen))
    {
        uart_putc(PGM_UART, CMD_WRITE_PAGE);
        uart_putc(PGM_UART, 0x02); /* Comms error - recoverable */
        return;
    }

    _g_ops[opsidx]->write(offset, writeLen, page);
    _g_ops[opsidx]->wait_write();
    
    if (crc_enabled)
    {
        _g_ops[opsidx]->read(offset, writeLen, readback);
        if (crc != crc8(0x00, readback, writeLen))
        {
            uart_putc(PGM_UART, CMD_WRITE_PAGE);
            uart_putc(PGM_UART, 0x03); /* Write error - unrecoverable */
            return;
        }
    }

    uart_putc(PGM_UART, CMD_WRITE_PAGE);
    uart_putc(PGM_UART, 0x01);
}

static void do_erase(void)
{
    uint8_t opsidx = read8();
    uint32_t offset = read32();
    uint32_t len = read32();

    _g_ops[opsidx]->erase(offset, len);
    _g_ops[opsidx]->wait_write();

    uart_putc(PGM_UART, CMD_ERASE);
    uart_putc(PGM_UART, 0x01);
}

static void do_boot_lock(int lock)
{
    uint8_t opsidx = read8();
    if (lock)
        _g_ops[opsidx]->lock_bootarea(1);
    else
        _g_ops[opsidx]->lock_bootarea(0);

    _g_ops[opsidx]->wait_write();

    uart_putc(PGM_UART, lock ? CMD_LOCK_BOOT : CMD_UNLOCK_BOOT);
    uart_putc(PGM_UART, 0x01);
}
