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

#include <stdint.h>
#include <stdio.h>
#include <stddef.h>

#include "eod_io.h"
#include "util.h"
#include "lcd.h"

uint8_t lcd_ddram;

void lcd_byte(uint8_t byte);
void lcd_setrs(int on);
void lcd_strobe1(uint8_t delay);
void lcd_strobe2(uint8_t delay);
void lcd_cmd(uint8_t disp, uint8_t cmd, uint8_t delay);
void lcd_data(uint8_t data);
void lcd_address(uint8_t disp, uint8_t address);
void lcd_pos(uint8_t row, uint8_t col);
void lcd_cgaddress(uint8_t disp, uint8_t addr);
char lcd_address_from_idx(uint8_t idx);
void lcd_special_data(uint8_t disp, uint8_t data);

#define D_39uS              0
#define D_1_53mS            1
#define D_43uS              2

/********************************************
* Init both displays
* 
*/
void lcd_init(void)
{
    lcd_ddram = 0x0;
    lcd_cmd(0, 0x38, D_39uS);
    lcd_cmd(0, 0x38, D_39uS);
    lcd_cmd(0, 0xC, D_39uS);
    lcd_clear(0);
    lcd_home(0);
    lcd_cmd(1, 0x38, D_39uS);
    lcd_cmd(1, 0x38, D_39uS);
    lcd_cmd(1, 0xC, D_39uS);
    lcd_clear(1);
    lcd_home(1);
}

/********************************************
* Clear a display
* 
*/
void lcd_clear(uint8_t disp)
{
    lcd_cmd(disp, 0x1, D_1_53mS);
}

/********************************************
* Reset cursor pos to start of display
* 
*/
void lcd_home(uint8_t disp)
{
    lcd_cmd(disp, 0x2, D_1_53mS);
}

/********************************************
* Output a string
*
* Automatically chooses the correct display
* based on lcd_ddram
* 
*/
void lcd_string(const char *data)
{
    while (*data)
    {
        lcd_data((uint8_t)*(data));
        data++;
    }
}

/********************************************
* Handle 0x8 (backspace)
*
* Automatically chooses the correct display
* based on lcd_ddram
*/
void lcd_backspace(void)
{
    if (lcd_ddram == 0)
        return;
        
    lcd_ddram--;
    lcd_address_from_idx(lcd_ddram);
    lcd_data(0x20);
    lcd_ddram--;
    lcd_address_from_idx(lcd_ddram);
}

/********************************************
* Handle 0xD (return)
*
* Automatically chooses the correct display
* based on lcd_ddram
*/
void lcd_return(void)
{
    uint8_t line;
    
    line = lcd_address_from_idx(lcd_ddram);
    
    if (line == 3)
        return;
        
    line++;
    
    lcd_pos(line, 0);
}

/********************************************
* Populate a CGRAM position with an array
* containing the charactor
* 
* Updates both displays
*/
void lcd_cgpopulate(uint8_t idx, const char *data)
{
    uint8_t i;
    lcd_cgaddress(0, idx * 8);
    lcd_cgaddress(1, idx * 8);
    
    for (i = 0; i < 8; i++)
    {
        lcd_special_data(0, (uint8_t)*(data));
        lcd_special_data(1, (uint8_t)*(data));
        data++;
    }

    lcd_address_from_idx(lcd_ddram);
}

/********************************************
* Set the address of the controller
* which owns the charactor index in idx
*
* also returns the line the charactor is on
*/
char lcd_address_from_idx(uint8_t idx)
{
    if (idx < 0x50)
    {
        if (idx < 0x28)
        {
            lcd_address(0, idx);
            return 0;
        }
        else
        {
            lcd_address(0, idx + 24);
            return 1;
        }
    }
    else
    {
        if ( idx < 0x78 )
        {
            lcd_address(1, idx - 80);
            return 2;
        }
        else
        {
            lcd_address(1, idx - 56);
            return 3;
        }
    }
}

/********************************************
* Set column/row of next inserted char
* 
*/
void lcd_pos(uint8_t row, uint8_t col)
{
    switch (row)
    {
        case 0:
            lcd_address(0, 0x00 + col);
            lcd_ddram = col; //Start of line 0
            break;
        case 1:
            lcd_address(0, 0x40 + col);
            lcd_ddram = 0x28 + col; //Start of line 1
            break;
        case 2:
            lcd_address(1, 0x00 + col);
            lcd_ddram = 0x50 + col; //Start of line 2
            break;
        case 3:
            lcd_address(1, 0x40 + col);
            lcd_ddram = 0x78 + col; //Start of line 3
            break;
    }    
}

/********************************************
* DD-RAM address
* 
*/
void lcd_address(uint8_t disp, uint8_t addr)
{
    addr |= 0x80;
    lcd_cmd(disp, addr, D_39uS);
}

/********************************************
* CG-RAM address
* 
*/
void lcd_cgaddress(uint8_t disp, uint8_t addr)
{
    addr |= 0x40;
    addr &= ~0x80;
    lcd_cmd(disp, addr, D_39uS);
}

/********************************************
* Output data/characters
*
* Automatically chooses the correct display
* based on lcd_ddram
*/
void lcd_data(uint8_t data)
{
    if (lcd_ddram == 0xA0) //went off the end of the display
    {
        return;
    }
    
    lcd_setrs(1);
    lcd_byte(data);
    if (lcd_ddram >= 80)
        lcd_strobe2(D_43uS);
    else
        lcd_strobe1(D_43uS);
        
    lcd_ddram++;
    
    if (lcd_ddram == 0x50) //get disp 1 back to address 0x0 read for input
        lcd_address(1, 0);
}

/********************************************
* output data on a paticular display
* 
*/
void lcd_special_data(uint8_t disp, uint8_t data)
{
    lcd_setrs(1);
    lcd_byte(data);
    if (disp)
        lcd_strobe2(D_43uS);
    else
        lcd_strobe1(D_43uS);
}

/********************************************
* Send a command to a paticular display
* 
*/
void lcd_cmd(uint8_t disp, uint8_t cmd, uint8_t delay)
{
    lcd_setrs(0);
    lcd_byte(cmd);
    
    if (disp)
        lcd_strobe2(delay);
    else
        lcd_strobe1(delay);
    
}

/********************************************
*
* Output a byte.
*
*/
void lcd_byte(uint8_t byte)
{    
    cpld_write(PORTD, 0x00FF, byte);
}

/********************************************
* Toggle RS pin
* 
*/
void lcd_setrs(int on)
{
    if (on)
        cpld_write(PORTD, 0x400, 0x400);
    else
        cpld_write(PORTD, 0x400, 0x0);

    delay_ncycles(1);
}

/********************************************
* Assert chip select on display 1
* for 1uS and wait for the specified time
* 
*/
void lcd_strobe1(uint8_t delay)
{
    cpld_write(PORTD, 0x100, 0x100);
    delay_ncycles(1);
    cpld_write(PORTD, 0x100, 0x0);

    switch (delay)
    {
        case D_1_53mS: 
            delay_ncycles(833);
            break;
        case D_39uS:
            delay_ncycles(20);
            break;
        case D_43uS:
            delay_ncycles(23);
            break;
    }    
}

/********************************************
* Assert chip select on display 2
* for 1uS and wait for the specified time
* 
*/
void lcd_strobe2(uint8_t delay)
{
    cpld_write(PORTD, 0x200, 0x200);
    delay_ncycles(1);
    cpld_write(PORTD, 0x200, 0x0);

    switch ( delay )
    {
        case D_1_53mS: 
            delay_ncycles(833);
            break;
        case D_39uS:
            delay_ncycles(20);
            break;
        case D_43uS:
            delay_ncycles(23);
            break;
    }    
}
