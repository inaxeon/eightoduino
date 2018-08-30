/*
 *   8OD - Arduino form factor i8086 based SBC
 *   Matthew Millman (tech.mattmillman.com)
 *
 *   C based initialisation for "boot from flash" applications
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
#include "mid.h"
#include "spiflash.h"
#include "util.h"
#include "pgm.h"

#pragma aux     _CMain  "_*";

/* Memory map (0x20000-0x2FFFF in RAM):
 *
 * 0x0000 - 0x1FFF 8K  : _DATA (DGROUP)
 * 0x1FFF - 0x7FFF 24K : STACK
 * 0x8000 - 0xFFFF 32K : HEAP
 */

extern void main(void);

/* Internal */
extern uint16_t far _heap_start;
extern uint16_t far _heap_size;

void _CMain(void)
{
    io_init();
    mid_init(M_CLK_DIV4);
    spiflash_init();

    switch (pgm_main())
    {
    case PGM_RESET:
        hard_reset();
        break;
    case PGM_BOOT:
        /* Jump back into the bootrom to perform the load, then boot */
        appentry_load_and_boot(1);
        break;
    case PGM_LOAD_AND_READ:
        /* Jump back into the bootrom, load, then read RAM to serial */
        appentry_load_and_boot(0);
        break;
    }

    hard_reset();
}

void interrupt_handler(void)
{
    /* Unused */
}
