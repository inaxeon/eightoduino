/*
 *   8OD - Arduino form factor i8086 based SBC
 *   Matthew Millman (tech.mattmillman.com)
 *
 *   Entry point for ram based app to ROM calls
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
#include <i86.h>
#include "eod_io.h"
#include "eod_map.h"
#include "uart.h"

extern int spi_load_and_boot(uint16_t);
extern int xip_load_and_boot(uint16_t, uint16_t);

static void do_load_and_read(void);

#pragma aux     _LoadAndBoot  "_*";

void _LoadAndBoot(int boot)
{
    if (boot)
    {
        //Boot the user app
#ifndef _EPROM_
        //Flash bootrom builds always boot form NOR flash
        xip_load_and_boot(1, APP_SEG); 
#else
        //EPROM bootrom builds always boot from SPI flash
        spi_load_and_boot(1);
#endif
    }
    else
    {
        do_load_and_read();
        /* Return to the programmer app */
        xip_load_and_boot(1, PGM_SEG);
    }
}

#define CMD_LOAD_AND_READ           0x09
#define PGM_UART                    UARTD

static void do_load_and_read(void)
{
    uint16_t i = 0;
    uint16_t segment;
    uint8_t far *fp = MK_FP(0x00, 0x0);

    uart_pgm_open();

    for (segment = 0; segment < 0x7000; segment += 0x1000)
    {
        i = 0;
        fp = MK_FP(segment, 0x0);

        for (;;)
        {
            fp[i] = 0xFF;
            if (i == 0xFFFF)
                break;
            i++;
        }
    }

    if (
    //Boot the user app
#ifdef _EPROM_
    //EPROM bootrom builds always boot from SPI flash
    spi_load_and_boot(0)
#else
    //Flash bootrom builds always boot form NOR flash
    xip_load_and_boot(0, APP_SEG)
#endif
    )
    {
        for (segment = 0; segment < 0x7000; segment += 0x1000)
        {
            i = 0;
            fp = MK_FP(segment, 0x0);

            for (;;)
            {
                uart_putc(PGM_UART, fp[i]);
                if (i == 0xFFFF)
                    break;
                i++;
            }
        }
        
        /* Success */
        uart_putc(PGM_UART, CMD_LOAD_AND_READ);
        uart_putc(PGM_UART, 0x01);
        return;
    }

    /* Fail */
    uart_putc(PGM_UART, CMD_LOAD_AND_READ);
    uart_putc(PGM_UART, 0x00);
}
