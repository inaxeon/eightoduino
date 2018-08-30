/*
 *   8OD - Arduino form factor i8086 based SBC
 *   Matthew Millman (tech.mattmillman.com)
 *
 *   C based initialisation for the bootrom
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
#include <stdlib.h>
#include <i86.h>

#include "eod_io.h"
#include "eod_map.h"
#include "negotiate.h"
#include "mid.h"
#include "util.h"

/* Memory map (0x70000-0x7FFFF in RAM):
 *
 * 0x0000 - 0x1FFF 8K  : _DATA (DGROUP)
 * 0x1FFF - 0x7FFF 24K : STACK
 * 0x8000 - 0xFFFF 32K : HEAP
 */

extern int spi_load_and_boot(uint16_t);
extern int xip_load_and_boot(uint16_t, uint16_t);

extern void boot_fail(void);

#pragma aux     _CMain  "_*";

void _CMain(void)
{
    //_amblksiz = 8 * 1024;   /* set minimum memory block allocation */
    io_init();
    mid_init(M_CLK_DIV4);

    if (pgm_negotiate())
    {
        //Load the flash programmer app into RAM and start it.
        xip_load_and_boot(1, PGM_SEG); 
    }
    else
    {
        //Boot the user app
#ifdef _EPROM_
        //EPROM bootrom builds always boot from SPI flash
        spi_load_and_boot(1);   
#else
        //Flash bootrom builds always boot form NOR flash
        xip_load_and_boot(1, APP_SEG); 
#endif
    }

    hard_reset();
}
