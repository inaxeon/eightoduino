/*
 *   8OD - Arduino form factor i8086 based SBC
 *   Matthew Millman (tech.mattmillman.com)
 *
 *   Misc routines
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

#ifndef __UTIL_H__
#define __UTIL_H__

void delay_ncycles(uint16_t count);

#pragma aux delay_ncycles = \
    "again:" \
    "loop again" \
    parm [cx];

/*   How to calculate the parameter to pass to delay_ncycles:
 *
 *   Becasue the 8086 spends quite a lot of clock cycles
 *   fetching instructions, the overhead of fetching the
 *   delay instructions and others surrounding adds significantly
 *   to the operation, meaning that actual times become less
 *   relative as the number of wait cycles decreases.
 *
 *   Some figures have been calculated by asserting and de-asserting
 *   a GPIO pin and measuring the active high time with the
 *   following test code:
 *
 *   cpld_write(PORTD, 0x0001, 0x0001); //PORTD(0) high
 *   delay_ncycles(<number of cycles>);
 *   cpld_write(PORTD, 0x0001, 0x0000); //PORTD(0) low
 *
 *   called with '1' delay_ncycles(1):
 *    5MHz: 11.6uS
 *    8MHz: 7.28uS
 *   10MHz: 5.84uS
 *
 *   100us delay:
 *    5MHz: 26 cycles
 *    8MHz: 42 cycles
 *   10MHz: 54 cycles
 *
 *   1ms delay:
 *    5MHz: 275 cycles
 *    8MHz: 445 cycles
 *   10MHz: 554 cycles
 *
 *   10ms delay:
 *    5MHz: 2780 cycles
 *    8MHz: 4450 cycles
 *   10MHz: 5570 cycles
 */

void hard_reset(void);

#endif /* __UTIL_H__ */
