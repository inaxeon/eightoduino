/*
 *   8OD - Arduino form factor i8086 based SBC
 *   Matthew Millman (tech.mattmillman.com)
 *
 *   Analog to Digital demo program
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
#include "adc.h"

void interrupt_handler(void)
{
    /* Unused */
}

void main(void)
{
    int i = 0;
    uart_open(UARTA, 115200, 8, PARITY_NONE, 1, 0);
    setup_printf(UARTA);

    while (1)
    {
        int channel;
        for (channel = 0; channel < 16; channel++)
        {
            uint16_t result = adc_read_channel(channel);
            printf("ADC channel %02d: read level %u of %u\r\n", channel, result, ADC_MAX_LEVEL);
            
            for(i = 0; i < 0x4000; i++);
        }

        printf("\r\n");
    }
}

