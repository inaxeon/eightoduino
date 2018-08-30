/*
 *   8OD - Arduino form factor i8086 based SBC
 *   Matthew Millman (tech.mattmillman.com)
 *
 *   PCF8584 I2C Master driver
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

/*   The PCF8584 is clocked by MIDCLK,
 *   which varies depending on the selected CPU clock speed.
 *
 *   Therefore, let's ignore all the stuff about clocks in the datasheet.
 *
 *   CPU 10MHz: MIDCLK = 15MHz
 *   CPU 8MHz : MIDCLK = 12MHz
 *   CPU 5MHz : MIDCLK = 7.5MHz
 *
 *   Assuming S21/S0 = 0 (OCLK0), the resulting I2C clocks are:
 *
 *   MIDCLK  @ 15MHz     @ 12MHz     @ 7.5MHz
 *
 *   ICLK0   = 441KHz    = 353KHz    = 220KHz
 *   ICLK2   = 220KHz    = 187KHz    = 117KHz
 *   ICLK4   = 117KHz    = 90KHz     = 58KHz
 */

#include <stdint.h>
#include <stdbool.h>

#define ICLK4        0x1C
#define ICLK3        0x18
#define ICLK2        0x14
#define ICLK1        0x10
#define ICLK0        0x00

#define OCLK3        0x03
#define OCLK2        0x02
#define OCLK1        0x01
#define OCLK0        0x00

void i2c_init(uint8_t iclkdiv, uint8_t oclkdiv);

bool i2c_read(uint8_t devaddr, uint8_t reg, uint8_t *data);
bool i2c_write(uint8_t devaddr, uint8_t reg, uint8_t data);

bool i2c_write_byte(uint8_t devaddr, uint8_t data);
bool i2c_read_byte(uint8_t addr, uint8_t *ret);

bool i2c_read_buf(uint8_t devaddr, uint8_t reg, uint8_t *data, int len);
bool i2c_write_buf(uint8_t devaddr, uint8_t reg, uint8_t *data, int len);

bool i2c_await_flag(uint8_t addr, uint8_t mask, uint8_t *ret, uint8_t attempts);
