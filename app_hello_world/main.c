/*
 *   8OD - Arduino form factor i8086 based SBC
 *   Matthew Millman (tech.mattmillman.com)
 *
 *   Hello world demo program
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
#include "mid.h"

void interrupt_handler(void)
{
    /* Unused */
}

void main(void)
{
    int i = 0;

    uart_open(UARTA, 115200, 8, PARITY_NONE, 1, 0);
    setup_printf(UARTA);

    cpld_write(TRISA, (1 << 2), 0); //PIN 2 Output

    while (1)
    {
        printf("Hello world %u\r\n", i++);

        cpld_write(PORTA, (1 << 2), (1 << 2)); //PIN 2 On
        delay_ncycles(65535);
        cpld_write(PORTA, (1 << 2), 0); //PIN 2 Off
        delay_ncycles(65535);
    }
}

