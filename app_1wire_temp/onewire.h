/*
 *   8OD - Arduino form factor i8086 based SBC
 *   Matthew Millman (tech.mattmillman.com)
 *
 *   Dallas 1-Wire Bus Driver
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

#ifndef __ONEWIRE_H__
#define __ONEWIRE_H__

#include "project.h"

#include <stdint.h>
#include <stdbool.h>

#include "ds2482.h"

#define OW_READ_ROM     0x33
#define OW_MATCH_ROM    0x55
#define OW_SKIP_ROM     0xCC
#define OW_SEARCH_ROM   0xF0

#define OW_SEARCH_FIRST 0xFF        /* Start new search */
#define OW_PRESENCE_ERR 0xFF
#define OW_DATA_ERR     0xFE
#define OW_COMMS_ERR    0xFD
#define OW_LAST_DEVICE  0x00        /* Last device found */

#ifdef _OW_DS2482_

#define ow_init() ds2482_init()
#define ow_bus_reset(presense) ds2482_bus_reset(presense)
#define ow_command(cmd, id) ds2482_command(cmd, id)
#define ow_read_byte(ret) ds2482_read_byte(ret)
#define ow_write_byte(data) ds2482_write_byte(data)
#define ow_rom_search(diff, id) ds2482_rom_search(diff, id)
#define ow_bus_idle() true
#define ow_select_channel(channel) ds2482_select_channel(channel)

#endif /* _OW_DS2482_ */

#endif /* __ONEWIRE_H__ */
