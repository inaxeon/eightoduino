/*
 *   8OD - Arduino form factor i8086 based SBC
 *   Matthew Millman (tech.mattmillman.com)
 *
 *   I/O mapped HD44780 LCD driver, for the 8OD LCD half shield
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

void lcd_init(void);
void lcd_data(const uint8_t data);
void lcd_string(const char *data);
void lcd_pos(uint8_t row, uint8_t col);
void lcd_cgpopulate(uint8_t idx, const char *data);
void lcd_clear01(void);
void lcd_clear23(void);
