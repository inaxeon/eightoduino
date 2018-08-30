/*
 *   8OD - Arduino form factor i8086 based SBC
 *   Matthew Millman (tech.mattmillman.com)
 *
 *   HD44780 40x4 LCD driver
 *
 *   This is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 2 of the License, or
 *   (at your option) any later version.

 *   This software is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.

 *   You should have received a copy of the GNU General Public License
 *   along with this software.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __LCD_H__
#define __LCD_H__

void lcd_init(void);
void lcd_string(const char *data);
void lcd_home(uint8_t disp);
void lcd_clear(uint8_t disp);
void lcd_pos(uint8_t row, uint8_t col);
void lcd_cgpopulate(uint8_t idx, const char *data);
void lcd_backspace(void);
void lcd_return(void);

#endif /* __LCD_H__ */
