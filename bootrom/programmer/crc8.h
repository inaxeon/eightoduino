/*
*   8OD - Arduino form factor i8086 based SBC
*   Matthew Millman (tech.mattmillman.com)
*
*   8-bit CRC with polynomial x^8+x^6+x^3+x^2+1, 0x14D.
*   Chosen based on Koopman, et al. (0xA6 in his notation = 0x14D >> 1):
*   http://www.ece.cmu.edu/~koopman/roses/dsn04/koopman04_crc_poly_embedded.pdf
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

#ifndef __CRC8_H__
#define __CRC8_H__

#include <stdint.h>

uint8_t crc8(uint8_t crc, uint8_t *data, uint16_t len);

#endif /* __CRC8_H__ */
