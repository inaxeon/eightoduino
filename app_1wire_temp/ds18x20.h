/*
 *   8OD - Arduino form factor i8086 based SBC
 *   Matthew Millman (tech.mattmillman.com)
 *
 *   DS18X20 Driver
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

#ifndef __DS18X20_H__
#define __DS18X20_H__

#include "project.h"

#include <stdint.h>
#include <stdbool.h>

#include "onewire.h"

#define DS18B20_TCONV_12BIT       750

bool ds18x20_find_sensor(uint8_t *diff, uint8_t *id);
bool ds18x20_start_meas(uint8_t *id);
bool ds18x20_read_decicelsius(uint8_t *id, int16_t *decicelsius);
bool ds18x20_search_sensors(uint8_t *count, uint8_t(*sensor_ids)[DS18X20_ROMCODE_SIZE]);

#endif /* __DS18X20_H__ */
