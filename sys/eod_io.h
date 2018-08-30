/*
 *   8OD - Arduino form factor i8086 based SBC
 *   Matthew Millman (tech.mattmillman.com)
 *
 *   I/O Helpers
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
#include "eod_map.h"

/* Watcom auto generated */
extern unsigned _inline_inp(unsigned __port);
extern unsigned _inline_inpw(unsigned __port);
extern unsigned _inline_outp(unsigned __port, unsigned __value);
extern unsigned _inline_outpw(unsigned __port, unsigned __value);

/* Direct write. No shadow update */
#define cpld_direct_write(reg, value) _inline_outpw(reg, value)
#define outp(reg, value) _inline_outp(reg, value)
#define outpw(reg, value) _inline_outpw(reg, value)

/* For write-only registers, keeps a shadow of current value for partial modifications */
extern uint16_t _g_shadowRegisters[NUM_CPLD_SHADOWS];
#define cpld_write(reg, mask, value)                                                        \
    do {                                                                                    \
            *((uint16_t *)((uint8_t *)_g_shadowRegisters + reg)) &= ~mask;                  \
            *((uint16_t *)((uint8_t *)_g_shadowRegisters + reg)) |= value;                  \
            cpld_direct_write(reg, *((uint16_t *)((uint8_t *)_g_shadowRegisters + reg)));   \
    } while (0)


/* Direct read */
#define cpld_read(reg) _inline_inpw(reg)
#define inp(reg) _inline_inp(reg)
#define inpw(reg) _inline_inpw(reg)

#define cpld_shadow_read(reg) \
    *((uint16_t *)((uint8_t *)_g_shadowRegisters + reg))

void io_init(void);
