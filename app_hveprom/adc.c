/*
 *   File:   adc.c
 *   Author: Matt
 *
 *   Created on 19 December 2019, 14:49
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


#include "project.h"

#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>

#include "adc.h"

/*
 * 1024 (0x3FF) = Vref = 3.3V
 * 3.3 / 1024 = 0.00322265625
 * 
 * R1 = 10K
 * R2 = 2.2K
 * R2 / (R1+R2) = 0.180327868852459
 * 
 * 0.00322265625 * 1000000 = 3222.65625
 * 0.180327868852459 * 10000 = 1803.27868852459
 * 1000000 / 10000 = 100
 * Therefore: Result = Vin * 100
 */

#define SCALE_FACTOR 3223
#define VIN_SCALE_AMOUNT 1803
#define VIN_CHANNEL 0

void adc_init(void)
{
    // AREF = Internal
    ADMUX = 0;//_BV(REFS0) | _BV(REFS1);
 
    // ADC Enable and prescaler of 128
    // 16000000/128 = 125000
    ADCSRA = _BV(ADEN) | _BV(ADPS2) | _BV(ADPS1) | _BV(ADPS0);
}

uint16_t adc_read(uint8_t samples, uint16_t scale_amount)
{
    uint32_t average;
    uint8_t i;

    average = 0;
        
    for (i = 0; i < samples; i++)
    {
        _delay_ms(1);
        ADCSRA |= _BV(ADSC);
        while (ADCSRA & _BV(ADSC));

        average += ADC;
    }

    average /= samples;
    average *= SCALE_FACTOR;
    average /= scale_amount;

    return (uint16_t)average;
}

uint16_t adc_read_12v(void)
{
    ADMUX = (ADMUX & 0xE0) | VIN_CHANNEL;
    return adc_read(10, VIN_SCALE_AMOUNT);
}