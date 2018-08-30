/*
 *   8OD - Arduino form factor i8086 based SBC
 *   Matthew Millman (tech.mattmillman.com)
 *
 *   NOR flash driver
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

#ifndef __NORFLASH_H__
#define __NORFLASH_H__

#include <stdint.h>
#include "flash.h"

void norflash_init(void);
void norflash_wait_write(void);
void norflash_read(uint32_t offset, uint16_t len, uint8_t *buf);
void norflash_read_to_uart(uint32_t offset, uint32_t len, int uart_index);
int norflash_write(uint32_t start, uint16_t len, uint8_t *buf);
int norflash_erase(uint32_t start, uint32_t len);
int norflash_is_present(void);
void norflash_lock_bootarea(int lock);
int norflash_get_bootarea_lock_state(void);
uint32_t norflash_get_geometry(uint16_t *block_data_len, flash_erase_block_t **block_data, uint32_t *erase_size, uint32_t *boot_offset);

#define NOR_FLASH_BOOT_OFFSET       0x0
#define NOR_FLASH_SIZE              0x80000
#define NOR_BOOTBLOCK_SIZE          0x4000

extern const flash_ops_t nor_ops;

#endif /* __FLASH_H__ */
