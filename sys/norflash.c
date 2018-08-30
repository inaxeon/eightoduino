/*
 *   8OD - Arduino form factor i8086 based SBC
 *   Matthew Millman (tech.mattmillman.com)
 *
 *   E28F400 NOR flash driver
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
#include <i86.h>
#include "eod_map.h"
#include "eod_io.h"
#include "mid.h"
#include "norflash.h"
#include "uart.h"

#define E28F400T_MFG                0x89
#define E28F400T_TYPE               0x4470

#define CMD_READ_ARRAY              0xFF
#define CMD_READ_STATUS             0x70
#define CMD_READ_ID                 0x90
#define CMD_CLEAR_STATUS            0x50
#define CMD_WRITE                   0x40
#define CMD_ERASE                   0x20
#define CMD_ERASE_CONFIRM           0xD0
#define CMD_ERASE_SUSPEND           0xB0

#define STATUS_READY                0x80
#define STATUS_ESS                  0x40
#define STATUS_ERASE_ERR            0x20
#define STATUS_WRITE_ERR            0x10
#define STATUS_VPP_LOW              0x08

const flash_ops_t nor_ops = {
    &norflash_init,
    &norflash_wait_write,
    &norflash_read,
    &norflash_read_to_uart,
    &norflash_write,
    &norflash_erase,
    &norflash_is_present,
    &norflash_lock_bootarea,
    &norflash_get_bootarea_lock_state,
    &norflash_get_geometry
};

flash_erase_block_t blocks[] = {
    { 0x0,     0x20000 },
    { 0x20000, 0x20000 },
    { 0x40000, 0x20000 },
    { 0x60000, 0x18000 },
    { 0x78000, 0x2000 },
    { 0x7A000, 0x2000 },
    { 0x7C000, NOR_BOOTBLOCK_SIZE }
};

#define E28F400T_NUM_BLOCKS (sizeof(blocks) / sizeof(flash_erase_block_t))

#define norflash_ptr(addr) (MK_FP((ROM_SEG + (uint16_t)(addr >> 4)), (uint16_t)(addr & 0xF)))
#define norflash_cmd(x, addr) (*((volatile uint16_t far *)norflash_ptr(addr)) = x)
#define norflash_readreg(x) *((uint16_t far *)MK_FP(ROM_SEG, x))

uint32_t norflash_get_geometry(uint16_t *block_data_len, flash_erase_block_t **block_data, uint32_t *erase_size, uint32_t *boot_offset)
{
    *block_data = &blocks;
    *block_data_len = E28F400T_NUM_BLOCKS;
    *erase_size = 0;
    *boot_offset = 0x0;

    return NOR_FLASH_SIZE;
}

static uint16_t norflash_read_status(void)
{
    norflash_cmd(CMD_READ_STATUS, 0);
    return (uint8_t)norflash_readreg(0);
}

static int norflash_erase_sector(uint32_t offset)
{
    uint16_t status;

    norflash_cmd(CMD_ERASE, offset);
    norflash_cmd(CMD_ERASE_CONFIRM, offset);

    while (!((status = norflash_read_status()) & STATUS_READY));

    if (status & STATUS_ERASE_ERR || status & STATUS_VPP_LOW)
        return 0;

    return 1;
}

void norflash_init(void)
{

}

void norflash_wait_write(void)
{

}

int norflash_is_present(void)
{
    int ret;
    uint16_t mfg;
    uint16_t type;

    norflash_cmd(CMD_READ_ID, 0);
    mfg = norflash_readreg(0);
    norflash_cmd(CMD_READ_ID, 2);
    type = norflash_readreg(2);

    if (mfg != E28F400T_MFG || type != E28F400T_TYPE)
    {
        ret = 0;
        goto out;
    }

    norflash_cmd(CMD_READ_ARRAY, 0);
    ret = 1;
out:
    return ret;
}

void norflash_read(uint32_t offset, uint16_t len, uint8_t *buf)
{
    uint8_t far *flashptr = norflash_ptr(offset);
    while (len--)
        *buf++ = *flashptr++;
}

void norflash_read_to_uart(uint32_t offset, uint32_t len, int uart_index)
{
    while (len > 0)
    {
        uint32_t thisRead = len > 0x8000 ? 0x8000 : len;
        uint8_t far *flashptr = norflash_ptr(offset);
        offset += thisRead;
        len -= thisRead;
        while (thisRead--)
            uart_putc(uart_index, *flashptr++);
    }
}

void norflash_lock_bootarea(int lock)
{

}

int norflash_get_bootarea_lock_state(void)
{
    return 0;
}

int norflash_erase(uint32_t start, uint32_t len)
{
    int startblk;
    int endblk;
    int blk;
    int ret;

    if ((start + len) > NOR_FLASH_SIZE)
        return 0;

    for (startblk = 0; startblk < E28F400T_NUM_BLOCKS; startblk++)
    {
        if (start >= blocks[startblk].start && start < (blocks[startblk].start + blocks[startblk].length))
            break;
    }

    for (endblk = 0; endblk < E28F400T_NUM_BLOCKS; endblk++)
    {
        if ((start + len) > blocks[endblk].start && (start + len) <= (blocks[endblk].start + blocks[endblk].length))
            break;
    }

    for (blk = startblk; blk <= endblk; blk++)
    {
        if (!norflash_erase_sector(blocks[blk].start))
        {
            ret = 0;
            goto out;
        }
    }

    ret = 1;
out:
    norflash_cmd(CMD_READ_ARRAY, 0);
    return ret;
}

int norflash_write(uint32_t start, uint16_t len, uint8_t *buf)
{
    int i;
    int ret;
    int evenlen = (len & ~1) >> 1;
    uint16_t status;
    uint16_t far *flashptr = norflash_ptr(start);

    for (i = 0; i < evenlen; i++)
    {
        *flashptr = CMD_WRITE;
        *flashptr = *(uint16_t *)buf;

        while (!((status = norflash_read_status()) & STATUS_READY));

        if (status & STATUS_WRITE_ERR || status & STATUS_VPP_LOW)
        {
            ret = 0;
            goto out;
        }

        flashptr++;
        buf += 2;
    }

    /* Odd byte */
    if (len & 1)
    {
        *flashptr = CMD_WRITE;
        *flashptr = (*(uint8_t *)buf | 0xFF00);

        while (!((status = norflash_read_status()) & STATUS_READY));

        if (status & STATUS_WRITE_ERR || status & STATUS_VPP_LOW)
        {
            ret = 0;
            goto out;
        }
    }

    ret = 1;
out:
    norflash_cmd(CMD_READ_ARRAY, 0);
    return ret;
}
