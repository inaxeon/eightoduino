/*
 *   8OD - Arduino form factor i8086 based SBC
 *   Matthew Millman (tech.mattmillman.com)
 *
 *   Serial flash programming interface
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
#include <i86.h>

#include "eod_io.h"
#include "uart.h"
#include "negotiate.h"
#include "util.h"

#define NUM_NEG_WAITS               20000
#define PGM_UART                    UARTD

/* Establishes connectivity with programmer software */
int pgm_negotiate(void)
{
    int ret;
    char c;

#if PGM_UART == UARTD
    uart_pgm_open();
#else
    uart_open(PGM_UART, 115200, 8, PARITY_NONE, 1, 0);
#endif

    delay_ncycles(100);

    uart_putc(PGM_UART, '8');
    uart_putc(PGM_UART, 'O');
    uart_putc(PGM_UART, 'D');

    delay_ncycles(NUM_NEG_WAITS);

    if (uart_getc(PGM_UART, &c))
    {           
        if (c == 0x01)
        {
            uart_putc(PGM_UART, 0x01);
            uart_wait_tx(PGM_UART);
            ret = 1;
            goto done;
        }
    }

    ret = 0;
    uart_close(PGM_UART);

done:
    return ret;
}
