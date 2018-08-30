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

#include "project.h"

#include <stdint.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>

#include "eod_io.h"
#include "i2c.h"
#include "uart.h"
#include "util.h"
#include "onewire.h"
#include "ds18x20.h"

uint8_t _g_sensor_ids[MAX_SENSORS][DS18X20_ROMCODE_SIZE];

static void print_temp(uint8_t temp, int16_t dec, const char *desc, uint8_t nl);
static char *dots_for(const char *str);

#define MAX_DESC 16

char _g_dotBuf[MAX_DESC];

void interrupt_handler(void)
{
    /* Unused */
}

void main(void)
{
    uint8_t num_sensors;
    
    uart_open(UARTA, 9600, 8, PARITY_NONE, 1, 0);
    setup_printf(UARTA);

    ow_init();

    if (ds18x20_search_sensors(&num_sensors, _g_sensor_ids))
        printf("\r\nFound %u of %u maximum sensors\r\n", num_sensors, MAX_SENSORS);
    else
        printf("\r\nHardware error searching for sensors\r\n");

    while (1)
    {
        for (int i = 0; i < num_sensors; i++)
            ds18x20_start_meas(_g_sensor_ids[i]);

        // Nearly 1 second
        delay_ncycles(65535);
        delay_ncycles(65535);
        delay_ncycles(65535);
        delay_ncycles(65535);
        delay_ncycles(65535);
        delay_ncycles(65535);
        delay_ncycles(65535);

        for (int i = 0; i < num_sensors; i++)
        {
            int16_t reading_temp;

            if (ds18x20_read_decicelsius(_g_sensor_ids[i], &reading_temp))
            {
                print_temp(i, reading_temp, "Test", i == 0);
            }
            else
            {
                printf("Error reading sensor\r\n");
            }
        }
        
    }
}

static void print_temp(uint8_t temp, int16_t dec, const char *desc, uint8_t nl)
{
    fixedpoint_sign(dec, dec);

    printf("%sTemp %c (C) [%s] %s..: %s%u.%u\r\n",
         nl ? "\r\n" : "",
        '1' + temp,
        desc, dots_for(desc), fixedpoint_arg(dec, dec));
}

static char *dots_for(const char *str)
{
    uint8_t len = (MAX_DESC - 1) - strlen(str);
    uint8_t di = 0;
    for (di = 0; di < len; di++)
        _g_dotBuf[di] = '.';
    _g_dotBuf[di] = 0;
    return _g_dotBuf;
}
