/*
 *   8OD - Arduino form factor i8086 based SBC
 *   Matthew Millman (tech.mattmillman.com)
 *
 *   Gravitech 7 segment sheild demo
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

#include "lcd_io.h"
#include "eod_io.h"
#include "i2c.h"
#include "uart.h"
#include "util.h"
 
#define _7SEG       0x38     /* I2C address for 7-Segment */
#define THERM       0x49     /* I2C address for digital thermometer */
#define EEP         0x50     /* I2C address for EEPROM */

#define RED         3        /* Red color pin of RGB LED */
#define GREEN       5        /* Green color pin of RGB LED */
#define BLUE        6        /* Blue color pin of RGB LED */

#define COLD        23       /* Cold temperature, drive blue LED (23c) */
#define HOT         26       /* Hot temperature, drive red LED (27c) */

const uint8_t numberlookup[16] =
{
    0x3F,
    0x06,
    0x5B,
    0x4F,
    0x66,
    0x6D,
    0x7D,
    0x07,
    0x7F,
    0x6F,
    0x77,
    0x7C,
    0x39,
    0x5E,
    0x79,
    0x71
};

void setup();
void update_rgb(uint8_t temp_h);
void cal_temp(int *decimal, uint8_t *high, uint8_t *low, uint8_t *sign);
void dis_7seg(int decimal, uint8_t high, uint8_t low, uint8_t sign);

void interrupt_handler(void)
{
    /* Unused */
}

void main(void)
{ 
    int decimal;
    uint8_t temperature_h, temperature_l;
    uint8_t is_positive;

    uart_open(UARTA, 115200, 8, PARITY_NONE, 1, 0);
    printf("Starting...\r\n");

    cpld_write(TRISA, 0x68, 0); /* P3, 5, 6 output */

    /* I2C SCL 117KHz @ 10MHz */
    i2c_init(ICLK4, OCLK0);

    /* Configure 7-Segment to 12mA segment output current, Dynamic mode,  and Digits 1, 2, 3 AND 4 are NOT blanked */
    i2c_write(_7SEG, 0x00, 0x47);
    
    /* Setup configuration register 12-bit */
    i2c_write(THERM, 0x01, 0x60);

    printf("Init LCD...\r\n");
    lcd_init();

    while (1)
    {
        uint8_t readtemp[2];
        char buf[41];
        int written;
        i2c_read_buf(THERM, 0x0, readtemp, 2);
    
        /* Calculate temperature */
        cal_temp(&decimal, &readtemp[0], &readtemp[1], &is_positive);
    
        memset(buf, 0x20, 40);
        written = sprintf(buf, "The temperature is %s%u.%u degrees C", is_positive ? "" : "-", readtemp[0], decimal);
        buf[written] = 0x20;
        buf[40] = 0x00;
        lcd_clear01();
        lcd_pos(0, 0);
        lcd_string(buf);
        /* Update RGB LED.*/
        update_rgb(readtemp[0]);
    
        /* Display temperature on the 7-Segment */
        dis_7seg (decimal, readtemp[0], readtemp[1], is_positive);
    
        delay_ncycles(0xFFFF);
        delay_ncycles(0xFFFF);
        delay_ncycles(0xFFFF);
        delay_ncycles(0xFFFF);
        delay_ncycles(0xFFFF);
        delay_ncycles(0xFFFF);
        delay_ncycles(0xFFFF);
        delay_ncycles(0xFFFF);
    }
} 

void cal_temp(int *decimal, uint8_t *high, uint8_t *low, uint8_t *is_positive)
{
    if ((*high & 0x80) == 0x80)    /* Check for negative temperature. */
        *is_positive = 0;
    else
        *is_positive = 1;
    
    *high = *high & 0x7F;      /* Remove sign bit */
    *low = *low & 0xF0;        /* Remove last 4 bits */
    *low = *low >> 4; 
    *decimal = *low;
    *decimal = *decimal * 625;      /* Each bit = 0.0625 degree C */
  
    if (*is_positive == 0)          /* if temperature is negative */
    {
        *high = *high ^ 0x7F;    /* Complement all of the bits, except the MSB */
        *decimal = *decimal ^ 0xFF;   /* Complement all of the bits */
    }  
}

void dis_7seg(int decimal, uint8_t high, uint8_t low, uint8_t sign)
{
    uint8_t digit = 4;                 /* Number of 7-Segment digit */
    uint8_t number;                    /* Temporary variable hold the number to display */
  
    if (sign == 0)                  /* When the temperature is negative */
    {
        i2c_write(_7SEG, digit, 0x40); /* Display "-" sign */
        digit--;                      /* Decrement number of digit */
    }
  
    if (high > 99)                  /* When the temperature is three digits long */
    {
        number = high / 100;          /* Get the hundredth digit */
        i2c_write(_7SEG, digit, numberlookup[number]);
        high = high % 100;            /* Remove the hundredth digit from the TempHi */
        digit--;                      /* Subtract 1 digit */    
    }
  
    if (high > 9)
    {
        number = high / 10;           /* Get the tenth digit */
        i2c_write(_7SEG, digit, numberlookup[number]);
        high = high % 10;            /* Remove the tenth digit from the TempHi */
        digit--;                      /* Subtract 1 digit */
    }
  
    number = high;                  /* Display the last digit */
    number = numberlookup[number]; 

    if (digit > 1)                  /* Display "." if it is not the last digit on 7-SEG */
    {
        number = number | 0x80;
    }

    i2c_write(_7SEG, digit, number);
    digit--;                        /* Subtract 1 digit */
  
    if (digit > 0)                  /* Display decimal point if there is more space on 7-SEG */
    {
        number = decimal / 1000;
        i2c_write(_7SEG, digit, numberlookup[number]);
        digit--;
    }

    if (digit > 0)                 /* Display "c" if there is more space on 7-SEG */
    {
        i2c_write(_7SEG, digit, 0x58);
        digit--;
    }
  
    if (digit > 0)                 /* Clear the rest of the digit */
    {
        i2c_write(_7SEG, digit, 0x00);
    }
}

void update_rgb(uint8_t temp_h)
{
    if (temp_h <= COLD)
        cpld_write(PORTA, 0x68, (1 << BLUE));
    else if (temp_h >= HOT)
        cpld_write(PORTA, 0x68, (1 << RED));
    else 
        cpld_write(PORTA, 0x68, (1 << GREEN));
}

