/*
 *   8OD - Arduino form factor i8086 based SBC
 *   Matthew Millman (tech.mattmillman.com)
 *
 *   DS2482 Driver
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

#ifndef __DS2482_H__
#define	__DS2482_H__

#include <stdint.h>
#include <stdbool.h>

bool ds2482_init(void);
bool ds2482_bus_reset(bool *presense_detect);
bool ds2482_command(uint8_t command, uint8_t *id);
bool ds2482_read_byte(uint8_t *ret);
bool ds2482_write_byte(uint8_t data);
#ifdef _OW_DS2482_800_
bool ds2482_select_channel(uint8_t channel);
#endif /* _OW_DS2482_800_ */
uint8_t ds2482_rom_search(uint8_t diff, uint8_t *id);

#endif /* __DS2482_H__ */
