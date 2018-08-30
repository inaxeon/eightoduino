/*
 *   8OD - Arduino form factor i8086 based SBC
 *   Matthew Millman (tech.mattmillman.com)
 *
 *   GPIO port demo program
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
#include "util.h"

void interrupt_handler(void)
{
    /* Unused */
}


//#define READTEST 1
#define READTEST_GFP14_15 1

void main(void)
{
    int i = 0;

#ifdef READTEST_GFP14_15
    /* Special test to cover GFP14 and 15 only
     * Can't be covered by the one below because
     * those pins are needed for the console
     */
    uart_open(UARTA, 115200, 8, PARITY_NONE, 1, 0);
    setup_printf(UARTA);

    /* Set GFP14-15 to input */
    cpld_write(TRISA, 0xC000, 0xC000);

#elif defined(READTEST)
    uart_open(UARTD, 115200, 8, PARITY_NONE, 1, 0);
    setup_printf(UARTD);

    /* Set GFP0-13 to input */
    cpld_write(TRISA, 0x3FFF, 0x3FFF);

    /* Set GFP16-21 to input */
    cpld_write(TRISB, 0x003F, 0x003F);

    /* Set GFP23-37 to input */
    cpld_write(TRISC, 0xFFFF, 0xFFFF);

    /* No TRISD register. PORTD (GFP38-53 cannot be inputs) */

#else
    /* Set GFP0-15 to output */
    cpld_write(TRISA, 0xFFFF, 0x0000);

    /* Set GFP16-21 to output */
    cpld_write(TRISB, 0x003F, 0x0000);

    /* Set GFP23-37 to output */
    cpld_write(TRISC, 0xFFFF, 0x0000);

    /* No TRISD register. PORTD (GFP38-53 are output only) */
#endif

    while (1)
    {
#ifdef READTEST_GFP14_15
        uint16_t porta;

        porta = cpld_read(PORTA);
        porta &= 0xC000;

        printf("Current PORTA(14,15) reading: 0x%04X\r\n", porta);
        
        delay_ncycles(5000);

#elif defined(READTEST)
        uint16_t portb;

        printf("Current PORTA reading: 0x%04X\r\n", cpld_read(PORTA));

        portb = cpld_read(PORTB);
        /* PORTB is guaranteed to have junk on the unimplemented bits. If it matters - AND it off. */
        portb &= 0x003F;

        printf("Current PORTB reading: 0x%04X\r\n", portb);
        printf("Current PORTC reading: 0x%04X\r\n\r\n", cpld_read(PORTC));

        delay_ncycles(5000);
#else
        /* Set all odd pins to 'high' */
        /* Set all even pins to 'low' */
        cpld_direct_write(PORTA, 0xAAAA);
        cpld_direct_write(PORTB, 0x002A);
        cpld_direct_write(PORTC, 0xAAAA);
        cpld_direct_write(PORTD, 0xAAAA);

        delay_ncycles(5000);

        /* Set all even pins to 'high' */
        /* Set all odd pins to 'low' */
        cpld_direct_write(PORTA, 0x5555);
        cpld_direct_write(PORTB, 0x0015);
        cpld_direct_write(PORTC, 0x5555);
        cpld_direct_write(PORTD, 0x5555);
#endif
    }
}

