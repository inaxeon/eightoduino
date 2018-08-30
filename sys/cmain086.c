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
#include "i2c.h"
#include "spiflash.h"
#include "adc.h"

#pragma aux     _CMain  "_*";

/* Memory map (0x20000-0x2FFFF in RAM):
 *
 * 0x0000 - 0x1FFF 8K  : _DATA (DGROUP)
 * 0x1FFF - 0x7FFF 24K : STACK
 * 0x8000 - 0xFFFF 32K : HEAP
 */

extern void main(void);

/* clib */
extern void _WCFAR __HeapInit(void _WCNEAR *start, unsigned int amount);
extern void __InitFiles(void);

/* Internal */
extern uint16_t far _heap_start;
extern uint16_t far _heap_size;

void _CMain(void)
{
    //_amblksiz = 8 * 1024;   /* set minimum memory block allocation */
    io_init();
#ifndef NO_MID
    mid_init(M_CLK_DIV4);
#endif /* NO_MID */
#ifndef NO_I2C
    i2c_init(ICLK4, OCLK0);
#endif /* NO_I2C */
#ifndef NO_SPIFLASH
    spiflash_init();
#endif /* NO_SPIFLASH */
#ifndef NO_ADC
    adc_init();
#endif /* NO_ADC */

    /* Setup malloc() */
    __HeapInit((void _WCNEAR *)_heap_start, _heap_size);
    /* Init stdin, stdout, stderr */
    __InitFiles();

    for (;;)
    {
        main();
    }
}
