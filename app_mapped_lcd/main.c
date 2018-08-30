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

#include "lcd_io.h"
#include "eod_io.h"
#include "uart.h"
#include "util.h"

void marquee_line(const char *text, int line);

const char *line0 = "abcdefghijklmnopqrstuvwxyz";
const char *line1 = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const char *line2 = "123456789012345678901234567890";
const char *line3 = "098765432109876543210987654321";


void interrupt_handler(void)
{
    /* Unused */
}

void marquee_line(const char *text, int line)
{
    uint16_t remaining;
    char buf[41];

    remaining = 40;
    buf[40] = 0;

    while(1)
    {
        uint16_t linelen = strlen(text);
        remaining--;
        
        memset(buf, ' ', 40);
        memcpy(buf + remaining, text, linelen > (40 - remaining) ?
            (40 - remaining) : linelen);

        lcd_pos(line, 0);
        lcd_string(buf);

        delay_ncycles(20000);

        if (remaining == 0)
            break;
    }
}

void main(void)
{
    int i = 0;
    
    uart_open(UARTA, 115200, 8, PARITY_NONE, 1, 0);
    setup_printf(UARTA);

    lcd_init();

    while (1)
    {
        lcd_init();
        printf("Hello world %u\r\n", i++);
        delay_ncycles(65535);
    
        marquee_line(line0, 0);
        marquee_line(line1, 1);
        marquee_line(line2, 2);
        marquee_line(line3, 3);
    }
}
