/*
 *   8OD - Arduino form factor i8086 based SBC
 *   Matthew Millman (tech.mattmillman.com/8od)
 *
 *   1702A/2704/2708/MCM68764/MCM68766 EPROM Programmer
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

#include "project.h"

#include <stdint.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <stdbool.h>

#include "util.h"

#ifdef _MDUINO
#include <avr/io.h>
#include <util/delay.h>
#endif /* _MDUINO */

#ifdef _MDUINO
#include "usart_buffered.h"
#endif /* _MDUINO */

#ifdef _MDUINO

char host_blocking_getc(void)
{
    while (!host_usart_data_ready());
    return host_usart_get();
}

bool host_getc(char *c)
{
    if (!host_usart_data_ready())
        return false;

    *c = host_usart_get();

    return true;
}

int print_char(char byte, FILE *stream)
{
    while (debug_usart_busy());
    debug_usart_put(byte);
    return 0;
}

#endif /* _MDUINO */
