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

#ifndef _PGM_270X_MCM6876X_H
#define _PGM_270X_MCM6876X_H

void pgm_270x_mcm6876x_init(void);
void pgm_270x_mcm6876x_set_params(uint8_t dev_type, uint16_t dev_size, uint8_t max_retries);
void pgm_270x_mcm6876x_reset(void);
void pgm_270x_mcm6876x_write_chunk(void);
void pgm_270x_mcm6876x_read_chunk(void);
void pgm_270x_mcm6876x_blank_check(void);
void pgm_270x_mcm6876x_start_write(void);
void pgm_270x_mcm6876x_start_read(void);

#endif /* _PGM_270X_MCM6876X_H */
