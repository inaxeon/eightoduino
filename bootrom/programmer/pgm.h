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

#ifndef __PGM_H__
#define __PGM_H__

#include <i86.h>

int pgm_main(void);
int pgm_negotiate(void);

#define PGM_BOOT            0
#define PGM_RESET           1
#define PGM_LOAD_AND_READ   2

#define FLG_BOOT_LOCKED     0x01
#define FLG_NOR             0x02
#define FLG_BOOT            0x04

#define appentry_load_and_boot(boot) ((void far (*const)(int))MK_FP(0xFFF8, 0x0000))(boot)

#endif /* __PGM_H__ */
