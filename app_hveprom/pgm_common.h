/*
 *   8OD - Arduino form factor i8086 based SBC
 *   Matthew Millman (tech.mattmillman.com/8od)
 *
 *   1702A/2704/2708/MCM68764/MCM68766/MCS48 EPROM Programmer
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

#ifndef _PGM_COMMON_H
#define _PGM_COMMON_H

#define CMD_START_WRITE          0x10
#define CMD_WRITE_CHUNK          0x11
#define CMD_START_READ           0x12
#define CMD_READ_CHUNK           0x13
#define CMD_START_BLANK_CHECK    0x14
#define CMD_BLANK_CHECK          0x15
#define CMD_DEV_RESET            0x16
#define CMD_MEASURE_12V          0x17
#define CMD_TEST                 0x18
#define CMD_TEST_READ            0x19

#define DEV_1702A                0x00
#define DEV_C2704                0x01
#define DEV_C2708                0x02
#define DEV_MCM6876X             0x03
#define DEV_8748                 0x04
#define DEV_8749                 0x05
#define DEV_8741                 0x06
#define DEV_8742                 0x07
#define DEV_8048                 0x08
#define DEV_8049                 0x09
#define DEV_8050                 0x0A
#define DEV_8755                 0x0B
#define DEV_8041                 0x0C
#define DEV_8042                 0x0D
#define DEV_TMS2716              0x0E 

#define ERR_OK                   0x00
#define ERR_PROCEED_DUALSOCKET   0x01
#define ERR_COMPLETE             0x02
#define ERR_INVALID_CMD          0x03
#define ERR_NOT_SUPPORTED        0x04
#define ERR_NO_DEV               0x05
#define ERR_INCORRECT_HW         0x06
#define ERR_INCORRECT_SWITCH_POS 0x07
#define ERR_OVERCURRENT          0x08
#define ERR_NOT_BLANK            0x09
#define ERR_MAX_RETRIES          0x0A

#define READ_CHUNK_SIZE          8
#define WRITE_CHUNK_SIZE         8
#define MCM6876X_MAX_RETRIES     25
#define C270X_MAX_RETRIES        100
#define MCS48_MAX_RETRIES        5

void pgm_process_command(uint8_t cmd);
void pgm_write_address(uint16_t address);
void pgm_write_data(uint8_t data);
uint8_t pgm_read_data(void);
void pgm_dir_out(void);
void pgm_dir_in(void);
void pgm_init(uint8_t type);
void pgm_power_on(void);

#endif /* _PGM_COMMON_H */
