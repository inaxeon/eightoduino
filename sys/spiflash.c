/*
 *   8OD - Arduino form factor i8086 based SBC
 *   Matthew Millman (tech.mattmillman.com)
 *
 *   SPI flash driver
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
#include <stddef.h>
#include "eod_map.h"
#include "eod_io.h"
#include "mid.h"
#include "spiflash.h"

#define M25P80_MFG                  0x20
#define M25P80_TYPE                 0x20
#define M25P80_CAPACITY             0x14

#define CMD_READ                    0x03
#define CMD_READ_IDENTIFICATION     0x9F
#define CMD_READ_STATUS_REGISTER    0x05
#define CMD_WRITE_STATUS_REGISTER   0x01
#define CMD_WRITE_ENABLE            0x06
#define CMD_WRITE_DISABLE           0x04
#define CMD_ERASE_SECTOR            0xD8
#define CMD_ERASE_CHIP              0xC7
#define CMD_PROGRAM_PAGE            0x02

#define STATUS_LOCK_BITS            0x10
#define STATUS_LOCK_MASK            0x1C

#define STATUS_WIP                  0x01

#define ADDRCMD_LEN                 4

#define WRITE_ADDR(cmd, offset) \
    cmd[1] = offset >> 16; \
    cmd[2] = offset >> 8; \
    cmd[3] = offset;

const flash_ops_t spi_ops = {
    &spiflash_init,
    &spiflash_wait_write,
    &spiflash_read,
    &spiflash_read_to_uart,
    &spiflash_write,
    &spiflash_erase,
    &spiflash_is_present,
    &spiflash_lock_bootarea,
    &spiflash_get_bootarea_lock_state,
    &spiflash_get_geometry
};

uint32_t spiflash_get_geometry(uint16_t *block_data_len, flash_erase_block_t **block_data, uint32_t *erase_size, uint32_t *boot_offset)
{
    *block_data = NULL;
    *block_data_len = 0;
    *erase_size = SPI_FLASH_ERASE_SIZE;
    *boot_offset = SPI_FLASH_BOOT_OFFSET;
    return SPI_FLASH_SIZE;
}

static uint8_t spiflash_read_status(void)
{
    uint8_t cmd = CMD_READ_STATUS_REGISTER;
    uint8_t result;

    mid_xfer_x8(M_DEV_EEPROM, 1, &cmd, 1, &result);

    return result;
}

static void spiflash_write_enable(int enable)
{
    uint8_t cmd = enable ?
    CMD_WRITE_ENABLE : CMD_WRITE_DISABLE;

    mid_xfer_x8(M_DEV_EEPROM, 1, &cmd, 0, NULL);
}

static void spiflash_erase_chip(void)
{
    uint8_t cmd;

    cmd = CMD_ERASE_CHIP;

    /* Wait for previous operation to complete */
    while ((spiflash_read_status() & STATUS_WIP) == STATUS_WIP);

    mid_xfer_x8(M_DEV_EEPROM, 1, &cmd, 0, NULL);
}

static void spiflash_erase_sector(uint32_t offset)
{
    uint8_t cmd[ADDRCMD_LEN];

    cmd[0] = CMD_ERASE_SECTOR;
    WRITE_ADDR(cmd, offset);

    /* Wait for previous operation to complete */
    while ((spiflash_read_status() & STATUS_WIP) == STATUS_WIP);

    mid_xfer_x8(M_DEV_EEPROM, sizeof(cmd), &cmd, 0, NULL);
}

void spiflash_init(void)
{
    mid_cfg_dev(M_DEV_EEPROM, 1, M_CLK_DNEGEDGE, M_D_8BIT);
}

void spiflash_wait_write(void)
{
    while ((spiflash_read_status() & STATUS_WIP) == STATUS_WIP);
}

int spiflash_is_present(void)
{
    uint8_t cmd = CMD_READ_IDENTIFICATION;
    uint8_t result[3];

    mid_xfer_x8(M_DEV_EEPROM, 1, &cmd, 3, result);

    if (result[0] != M25P80_MFG ||
        result[1] != M25P80_TYPE ||
        result[2] != M25P80_CAPACITY)
        return 0;

    return 1;
}

void spiflash_read(uint32_t offset, uint16_t len, uint8_t *buf)
{
    uint8_t cmd[4];

    cmd[0] = CMD_READ;
    WRITE_ADDR(cmd, offset);

    /* Wait for previous operation to complete */
    while ((spiflash_read_status() & STATUS_WIP) == STATUS_WIP);

    mid_xfer_x8(M_DEV_EEPROM, sizeof(cmd), &cmd, len, buf);
}

void spiflash_read_to_uart(uint32_t offset, uint32_t len, int uart_index)
{
    uint8_t cmd[4];

    cmd[0] = CMD_READ;
    WRITE_ADDR(cmd, offset);

    /* Wait for previous operation to complete */
    while ((spiflash_read_status() & STATUS_WIP) == STATUS_WIP);

    mid_xfer_to_uart(M_DEV_EEPROM, sizeof(cmd), &cmd, len, uart_index);
}

/* Protect/unprotect the top 512KB */
void spiflash_lock_bootarea(int lock)
{
    uint8_t status;
    uint8_t cmd[2];

    status = spiflash_read_status();
    status &= ~STATUS_LOCK_MASK;

    if (lock)
        status |= STATUS_LOCK_BITS;

    cmd[0] = CMD_WRITE_STATUS_REGISTER;
    cmd[1] = status;

    /* Wait for previous operation to complete */
    while ((spiflash_read_status() & STATUS_WIP) == STATUS_WIP);

    mid_xfer_x8(M_DEV_EEPROM, sizeof(cmd), &cmd, 0, NULL);
}

int spiflash_get_bootarea_lock_state(void)
{
    uint8_t status;
    status = spiflash_read_status();

    return (status & STATUS_LOCK_BITS) == STATUS_LOCK_BITS;
}

int spiflash_erase(uint32_t start, uint32_t len)
{
    if ((start + len) > SPI_FLASH_SIZE)
        return 0;

    spiflash_write_enable(1);

    if (len == SPI_FLASH_SIZE)
    {
        spiflash_erase_chip();
    }
    else
    {
        while (len)
        {
            spiflash_erase_sector(start);

            start += SPI_FLASH_ERASE_SIZE;

            if (len < SPI_FLASH_ERASE_SIZE)
                len = 0;
            else
                len -= SPI_FLASH_ERASE_SIZE;
        }
    }

    return 1;
}

int spiflash_write(uint32_t start, uint16_t len, uint8_t *buf)
{
    uint32_t page_offset;
    uint32_t page_size;
    uint8_t cmd[ADDRCMD_LEN];

    cmd[0] = CMD_PROGRAM_PAGE;
    WRITE_ADDR(cmd, start);

    if ((start + len) > SPI_FLASH_SIZE)
        return 0;

    /* Wait for previous operation to complete */
    while ((spiflash_read_status() & STATUS_WIP) == STATUS_WIP);

    spiflash_write_enable(1);

    page_offset = start % FLASH_WRITE_SIZE;

    /* do all the bytes fit onto one page? */
    if (page_offset + len <= FLASH_WRITE_SIZE)
    {
        mid_xfer_x8_two(M_DEV_EEPROM, sizeof(cmd), &cmd, len, buf, 0, NULL);
    }
    else
    {
        uint32_t i;

        /* the size of data remaining on the first page */
        page_size = FLASH_WRITE_SIZE - page_offset;

        mid_xfer_x8_two(M_DEV_EEPROM, sizeof(cmd), &cmd, page_size, buf, 0, NULL);

        /* write everything in M25P80_PAGE_SIZE chunks */
        for (i = page_size; i < len; i += page_size)
        {
            page_size = len - i;
            if (page_size > FLASH_WRITE_SIZE)
                page_size = FLASH_WRITE_SIZE;

            WRITE_ADDR(cmd, start + i);

            /* Wait for previous operation to complete */
            while ((spiflash_read_status() & STATUS_WIP) == STATUS_WIP);

            spiflash_write_enable(1);

            mid_xfer_x8_two(M_DEV_EEPROM, sizeof(cmd), &cmd, page_size, buf + i, 0, NULL);
        }
    }

    return 1;
}
