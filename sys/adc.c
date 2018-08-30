/*
 *   8OD - Arduino form factor i8086 based SBC
 *   Matthew Millman (tech.mattmillman.com)
 *
 *   Analog Devices AD7490 driver
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
#include <stddef.h>
#include "eod_map.h"
#include "eod_io.h"
#include "mid.h"
#include "adc.h"

#define CTRL_WRITE      (1 << 7)
#define CTRL_SEQ        (1 << 6)
#define CTRL_PM1        (1 << 1)
#define CTRL_PM0        (1 << 0)

#define CTRL_SHADOW     (1 << 7)
#define CTRL_WEAKTRI    (1 << 6)
#define CTRL_RANGE      (1 << 5)
#define CTRL_CODING     (1 << 4)

#define CTRL_ADD_SHIFT  2

void adc_init(void)
{
    mid_cfg_dev(M_DEV_ADC, 1, M_CLK_DPOSEDGE, M_D_16BIT);
}

uint16_t adc_read_channel(int channel)
{
    uint16_t value;

    outp(MID_BASE + CSEL, ~(1 << M_DEV_ADC));

    outp(MID_BASE + SMB, CTRL_WEAKTRI | CTRL_RANGE | CTRL_CODING);
    outp(MID_BASE + FMB_CS0SEL + M_DEV_ADC, (CTRL_WRITE | CTRL_PM1 | CTRL_PM0) | channel << CTRL_ADD_SHIFT);
    
    while ((inp(MID_BASE + ST) & ST_UWDONE) == 0);

    outp(MID_BASE + CSEL, 0xFF);
    outp(MID_BASE + CSEL, ~(1 << M_DEV_ADC));

    outp(MID_BASE + SMB, CTRL_RANGE | CTRL_CODING);
    outp(MID_BASE + FMB_CS0SEL + M_DEV_ADC, (CTRL_WRITE | CTRL_PM1 | CTRL_PM0) | channel << CTRL_ADD_SHIFT);

    while ((inp(MID_BASE + ST) & ST_UWDONE) == 0);

    value = (inp(MID_BASE + FMB) << 8) | inp(MID_BASE + SMB);

    outp(MID_BASE + CSEL, 0xFF);

    value &= 0xFFF;
                     
    return value;
}
