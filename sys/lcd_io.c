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
#include <stdio.h>
#include <stddef.h>
#include <string.h>

#include "eod_io.h"
#include "lcd_io.h"
#include "util.h"

#define LCD1_CMD_ADDR       (EXT_LOWIO_BASE + 0x00)
#define LCD1_DATA_ADDR      (EXT_LOWIO_BASE + 0x01)
#define LCD2_CMD_ADDR       (EXT_LOWIO_BASE + 0x02)
#define LCD2_DATA_ADDR      (EXT_LOWIO_BASE + 0x03)
#define LCD_BACKLIGHT_ADDR  (EXT_LOWIO_BASE + 0x04)

#define CMD_CLEAR           0x01
#define CMD_HOME            0x02
#define CMD_ONOFF           0x08
#define CMD_FUNCTIONSET     0x20

#define DISP_ON             0x04
#define MODE_8BIT           0x10
#define MODE_2LINE          0x08

#define CMD_DDADDR          0x80
#define CMD_CGADDR          0x40

#define STATUS_BUSY         0x80

static char lcd_address_from_idx(uint8_t idx);

#define LCD1_CMD(cmd) do { \
        outp(LCD1_CMD_ADDR, cmd); \
        while (inp(LCD1_CMD_ADDR) & STATUS_BUSY); \
} while (0)

#define LCD2_CMD(cmd) do { \
        outp(LCD2_CMD_ADDR, cmd); \
        while (inp(LCD2_CMD_ADDR) & STATUS_BUSY); \
} while (0)

#define LCD1_DATA(cmd) do { \
        outp(LCD1_DATA_ADDR, cmd); \
        while (inp(LCD1_CMD_ADDR) & STATUS_BUSY); \
} while (0)

#define LCD2_DATA(cmd) do { \
        outp(LCD2_DATA_ADDR, cmd); \
        while (inp(LCD2_CMD_ADDR) & STATUS_BUSY); \
} while (0)

uint8_t lcd_ddram;

void lcd_init(void)
{
    lcd_ddram = 0x0;

    LCD1_CMD(CMD_FUNCTIONSET | MODE_8BIT | MODE_2LINE);
    LCD1_CMD(CMD_FUNCTIONSET | MODE_8BIT | MODE_2LINE);
    LCD1_CMD(CMD_ONOFF | DISP_ON);
    LCD1_CMD(CMD_CLEAR);
    LCD1_CMD(CMD_HOME);

    LCD2_CMD(CMD_FUNCTIONSET | MODE_8BIT | MODE_2LINE);
    LCD2_CMD(CMD_FUNCTIONSET | MODE_8BIT | MODE_2LINE);
    LCD2_CMD(CMD_ONOFF | DISP_ON);
    LCD2_CMD(CMD_CLEAR);
    LCD2_CMD(CMD_HOME);

    outp(LCD_BACKLIGHT_ADDR, 1);
}

void lcd_string(const char *data)
{
    while (*data)
    {
        lcd_data((uint8_t)*(data));
        data++;
    }
}

void lcd_clear01(void)
{
    LCD1_CMD(CMD_CLEAR);
}

void lcd_clear23(void)
{
    LCD2_CMD(CMD_CLEAR);
}

void lcd_cgpopulate(uint8_t idx, const char *data)
{
    uint8_t i;

    LCD1_CMD((CMD_CGADDR | (idx * 8)) & ~CMD_DDADDR);
    LCD2_CMD((CMD_CGADDR | (idx * 8)) & ~CMD_DDADDR);
    
    for (i = 0; i < 8; i++)
    {
        LCD1_DATA((uint8_t)*(data));
        LCD2_DATA((uint8_t)*(data));
        data++;
    }

    lcd_address_from_idx(lcd_ddram);
}

static char lcd_address_from_idx(uint8_t idx)
{
    if (idx < 0x50)
    {
        if (idx < 0x28)
        {
            LCD1_CMD(CMD_DDADDR | idx);
            return 0;
        }
        else
        {
            LCD1_CMD(CMD_DDADDR | (idx + 24));
            return 1;
        }
    }
    else
    {
        if (idx < 0x78)
        {
            LCD2_CMD(CMD_DDADDR | (idx - 80));
            return 2;
        }
        else
        {
            LCD2_CMD(CMD_DDADDR | (idx - 56));
            return 3;
        }
    }
}

void lcd_pos(uint8_t row, uint8_t col)
{
    switch (row)
    {
        case 0:
            LCD1_CMD(CMD_DDADDR | (0x00 + col));
            lcd_ddram = col; //Start of line 0
            break;
        case 1:
            LCD1_CMD(CMD_DDADDR | (0x40 + col));
            lcd_ddram = 0x28 + col; //Start of line 1
            break;
        case 2:
            LCD2_CMD(CMD_DDADDR | (0x00 + col));
            lcd_ddram = 0x50 + col; //Start of line 2
            break;
        case 3:
            LCD2_CMD(CMD_DDADDR | (0x40 + col));
            lcd_ddram = 0x78 + col; //Start of line 3
            break;
    }    
}

void lcd_data(const uint8_t data)
{
    if (lcd_ddram == 0xA0) //went off the end of the display
        return;
    
    if (lcd_ddram >= 80)
        LCD2_DATA(data);
    else
        LCD1_DATA(data);
        
    lcd_ddram++;
    
    if (lcd_ddram == 0x50) //get disp 1 back to address 0x0 read for input
        LCD1_CMD(CMD_DDADDR | 0x00);
}
