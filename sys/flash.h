/*
 *   8OD - Arduino form factor i8086 based SBC
 *   Matthew Millman (tech.mattmillman.com)
 *
 *   Flash driver
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

#ifndef __FLASH_H__
#define __FLASH_H__

#include <stdint.h>

typedef struct
{
    uint32_t start;
    uint32_t length;
} flash_erase_block_t;

typedef struct
{
    void (*init)(void);
    void (*wait_write)(void);
    void (*read)(uint32_t offset, uint16_t len, uint8_t *buf);
    void (*read_to_uart)(uint32_t offset, uint32_t len, int uart_index);
    int (*write)(uint32_t start, uint16_t len, uint8_t *buf);
    int (*erase)(uint32_t start, uint32_t len);
    int (*is_present)(void);
    void (*lock_bootarea)(int);
    int (*get_bootarea_lock_state)(void);
    uint32_t (*get_geometry)(uint16_t *block_data_len, flash_erase_block_t **block_data, uint32_t *erase_size, uint32_t *boot_offset);
} flash_ops_t;

#define FLASH_WRITE_SIZE          0x100

#endif /* __FLASH_H__ */
