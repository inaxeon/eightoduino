/*
 *   8OD - Arduino form factor i8086 based SBC
 *   Matthew Millman (tech.mattmillman.com)
 *
 *   One wire bus demo app (DS2482 master)
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

#ifndef __PROJECT_H__
#define __PROJECT_H__

#define _OW_DS2482_
#define MAX_SENSORS 8

#ifdef _DS18X20_SINGLE_DEV_PER_CHANNEL_
#define DS18X20_ROMCODE_SIZE 1
#else
#define DS18X20_ROMCODE_SIZE 8
#endif

#define _1DP_BASE 10

#define abs(x) (((x) < 0) ? -(x) : (x))

#define fixedpoint_sign(value, tag) \
    char tag##_sign[2]; \
    tag##_sign[1] = 0; \
    if (value < 0 ) \
        tag##_sign[0] = '-'; \
    else \
        tag##_sign[0] = 0; \

#define fixedpoint_arg(value, tag) tag##_sign, (abs(value) / _1DP_BASE), (abs(value) % _1DP_BASE)

#endif /* __PROJECT_H__ */
