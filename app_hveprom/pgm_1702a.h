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

#ifndef _PGM_1702A_H
#define _PGM_1702A_H

void pgm_1702a_set_params(void);
void pgm_1702a_init(void);
void pgm_1702a_reset(void);
void pgm_1702a_write_chunk(void);
void pgm_1702a_read_chunk(void);
void pgm_1702a_blank_check(void);
void pgm_1702a_start_write(void);
void pgm_1702a_start_read(void);

#endif /* _PGM_1702A_H */
