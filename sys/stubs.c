/*
 *   8OD - Arduino form factor i8086 based SBC
 *   Matthew Millman (tech.mattmillman.com)
 *
 *   Stubs for functions within the clib, that have no purpose on
 *   this platform
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

#include <stdio.h>
#include <stdlib.h>

/* Could be hooked up to printf, but probably not needed
 */
void __fatal_runtime_error(char *msg, unsigned retcode)
{

}

typedef int (*constraint_handler_t)(const char * __restrict msg,
                                void * __restrict ptr, int error);

int runtime_constraint_handler( const char * __restrict msg,
                                void * __restrict ptr, int error)
{
    return 0;
}

constraint_handler_t __runtime_constraint_handler = &runtime_constraint_handler;

/* Called to close all file handles.
 * Since we don't ever trully exit, this won't be needed
 */
void __full_io_exit(void)
{

}

/* Everything is a TTY
 */
void __chktty(FILE *fp)
{
    fp->_flag |= _ISTTY;
}

/* No need to flush anything, because serial output is always written
 * immediately
 */
_WCRTLINK extern int __flush(FILE *fp)
{
    return 0;
}

/* Appears to be used by malloc() to request more memory from the BIOS.
 * There is no BIOS, and malloc() is given everything it's ever going
 * to get up front.
 */
void _WCNEAR *__brk(unsigned brk_value)
{
    return ((void _WCNEAR *) -1);
}
