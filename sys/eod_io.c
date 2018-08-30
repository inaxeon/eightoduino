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
#include "eod_io.h"

uint16_t _g_shadowRegisters[NUM_CPLD_SHADOWS];

void io_init(void)
{
    /* Set shadows to their physical reset values */
    *((uint16_t *)((uint8_t *)_g_shadowRegisters + STATUS)) = 0x0000;
    *((uint16_t *)((uint8_t *)_g_shadowRegisters + CONFIG)) = 0x0000;
    *((uint16_t *)((uint8_t *)_g_shadowRegisters + PORTA)) = 0x0000;
    *((uint16_t *)((uint8_t *)_g_shadowRegisters + PORTB)) = 0x0000;
#ifndef LBUS_CPLD
    *((uint16_t *)((uint8_t *)_g_shadowRegisters + PORTC)) = 0x0000;
    *((uint16_t *)((uint8_t *)_g_shadowRegisters + PORTD)) = 0x0000;
#endif /* !LBUS_CPLD */
    *((uint16_t *)((uint8_t *)_g_shadowRegisters + TRISA)) = 0xFFFF;
    *((uint16_t *)((uint8_t *)_g_shadowRegisters + TRISB)) = 0x003F;
#ifndef LBUS_CPLD
    *((uint16_t *)((uint8_t *)_g_shadowRegisters + TRISC)) = 0xFFFF;
#endif /* !LBUS_CPLD */
    *((uint16_t *)((uint8_t *)_g_shadowRegisters + TIMER)) = 0x0000;
}
