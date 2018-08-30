/*
 *   8OD - Arduino form factor i8086 based SBC
 *   Matthew Millman (tech.mattmillman.com)
 *
 *   Quick'n'dirty SPI flash reader
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
#include "uart.h"
#include "util.h"
#include "spiflash.h"
#include "mid.h"

#define ADDRCMD_LEN                 4

#define WRITE_ADDR(cmd, offset) \
    cmd[1] = offset >> 16; \
    cmd[2] = offset >> 8; \
    cmd[3] = offset;

#define CMD_READ                    0x03
#define CMD_READ_STATUS_REGISTER    0x05

#define STATUS_WIP                  0x01

static uint8_t spiflash_read_status(void);

void interrupt_handler(void)
{
    /* Unused */
}

void main(void)
{
    int i = 0;
    uint32_t len = 4194304;
    uint8_t cmd[ADDRCMD_LEN];

    cpld_write(TRISA, (1 << 10), 0); //10 Output (CS)
    uart_open(UARTA, 115200, 8, PARITY_NONE, 1, 0);
    setup_printf(UARTA);

    //printf("Starting %lu\r\n", len);

    mid_init(M_CLK_DIV8);

    spiflash_read_to_uart(0,2097152/* 4194304*/, UARTA);
#if 0

    cpld_write(PORTA, (1 << 10), 0); /* CS Low */

    cpld_write(PORTA, (1 << 10), (1 << 10)); /* CS Low */
    delay_ncycles(65535);
    cpld_write(PORTA, (1 << 10), 0); /* CS Low */

    cmd[0] = CMD_READ;
    WRITE_ADDR(cmd, (uint32_t)0);

    /* Wait for previous operation to complete */
    while ((spiflash_read_status() & STATUS_WIP) == STATUS_WIP);

    //printf("Setup addr %x\r\n", spiflash_read_status());

    mid_xfer_to_uart(M_DEV_SPARE1, sizeof(cmd), &cmd, len, UARTA);

    //printf("Done\r\n");

    cpld_write(PORTA, (1 << 10), (1 << 10)); /* CS High */
	
#endif
    while (1);
}

static uint8_t spiflash_read_status(void)
{
    uint8_t cmd = CMD_READ_STATUS_REGISTER;
    uint8_t result;

    mid_xfer_x8(M_DEV_SPARE1, 1, &cmd, 1, &result);

    return result;
}
