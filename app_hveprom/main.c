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

#include "project.h"

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdbool.h>

#ifdef _M8OD
#include "sys/eod_io.h"
#include "sys/uart.h"
#include "sys/util.h"
#endif /* _M8OD */

#ifdef _MDUINO
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>
#include <util/delay.h>
#include "usart_buffered.h"
#include "adc.h"
#endif /* _MDUINO */

#include "util.h"
#include "pgm_common.h"
#include "iopins.h"

static int8_t cmd_get_next(void);
static uint8_t detect_shield(void);

#ifdef _MDUINO
FILE uart_str = FDEV_SETUP_STREAM(print_char, NULL, _FDEV_SETUP_RW);
#endif /* _MDUINO */

void interrupt_handler(void)
{
    /* Unused */
}

int main(void)
{
    uint8_t shieldType;

#ifdef _M8OD
    uart_open(HOST_UART, HOST_BAUD, 8, PARITY_NONE, 1, 0);
#ifdef _DEBUG
    uart_open(DEBUG_UART, DEBUG_BAUD, 8, PARITY_NONE, 1, 0);
    setup_printf(DEBUG_UART);
#endif /* _DEBUG */
#endif  /* _M8OD */

#ifdef _MDUINO

#if HOST_BAUD > 38400
    // The USB-to-Serial AVR seems to set U2X to reduce error at higher baud rates.
    // This shouldn't be necessary for us since we are sharing its clock, however we
    // have to anyway otherwise we introduce errors due to integer rounding.
    host_usart_open(USART_CONT_RX | USART_BRGH, (((F_CPU / HOST_BAUD) / 8) - 1));
#else
    host_usart_open(USART_CONT_RX, (((F_CPU / HOST_BAUD) / 16) - 1));
#endif /* HOST_BAUD > 38400 */

#ifdef _DEBUG
    debug_usart_open(USART_CONT_RX, (((F_CPU / DEBUG_BAUD) / 16) - 1));
    stdout = &uart_str;
#endif /* _DEBUG */
    g_irq_enable();
    adc_init();
    wdt_enable(WDTO_1S);
#endif /* _MDUINO */

#ifdef _DEBUG
#endif /* _DEBUG */

    shieldType = detect_shield();
    if (shieldType == SHIELD_TYPE_UNKNOWN)
    {
#ifdef _DEBUG
        printf("No shield attached. Cannot proceed.\r\n");
#endif /* _DEBUG */
        infinite_loop();
    }

    pgm_init(shieldType);

    for (;;)
    {
        int cmd = cmd_get_next();
#ifdef _MDUINO
        wdt_reset();
#endif /* _MDUINO */
        if (cmd < 0)
            continue;

#ifdef _DEBUG
        printf("Got command: %x\r\n", cmd);
#endif /* _DEBUG */

        pgm_process_command(cmd);
    }

    return 0;
}

static uint8_t detect_shield(void)
{
    bool bit_0 = false;
    bool bit_1 = false;
    bool bit_c = false;
    bool bit_b = false;
    bool bit_a = false;

#ifdef _M8OD
    cpld_write(SHIELDID_C01_TRIS, (SHIELD_ID_0 | SHIELD_ID_1 | SHIELD_ID_C), (SHIELD_ID_0 | SHIELD_ID_1 | SHIELD_ID_C));
    cpld_write(SHIELDID_AB_TRIS, (SHIELD_ID_A | SHIELD_ID_B), (SHIELD_ID_A | SHIELD_ID_B));
    bit_0 = (cpld_read(SHIELDID_C01_PORT) & SHIELD_ID_0) == SHIELD_ID_0;
    bit_1 = (cpld_read(SHIELDID_C01_PORT) & SHIELD_ID_1) == SHIELD_ID_1;
    bit_c = (cpld_read(SHIELDID_C01_PORT) & SHIELD_ID_C) == SHIELD_ID_C;
    bit_b = (cpld_read(SHIELDID_AB_PORT) & SHIELD_ID_B) == SHIELD_ID_B;
    bit_a = (cpld_read(SHIELDID_AB_PORT) & SHIELD_ID_A) == SHIELD_ID_A;
#endif /* _M8OD */

#ifdef _MDUINO
    SHIELD_ID_0_DDR &= ~_BV(SHIELD_ID_0);
    SHIELD_ID_1_DDR &= ~_BV(SHIELD_ID_1);
    SHIELD_ID_C_DDR &= ~_BV(SHIELD_ID_C);
    SHIELD_ID_B_DDR &= ~_BV(SHIELD_ID_B);
    SHIELD_ID_A_DDR &= ~_BV(SHIELD_ID_A);
    bit_0 = (SHIELD_ID_0_PIN & _BV(SHIELD_ID_0)) == _BV(SHIELD_ID_0);
    bit_1 = (SHIELD_ID_1_PIN & _BV(SHIELD_ID_1)) == _BV(SHIELD_ID_1);
    bit_c = (SHIELD_ID_C_PIN & _BV(SHIELD_ID_C)) == _BV(SHIELD_ID_C);
    bit_b = (SHIELD_ID_B_PIN & _BV(SHIELD_ID_B)) == _BV(SHIELD_ID_B);
    bit_a = (SHIELD_ID_A_PIN & _BV(SHIELD_ID_A)) == _BV(SHIELD_ID_A);
#endif /* _MDUINO */

    if (!bit_0 && bit_1)
    {
#ifdef _DEBUG
        printf("Shield type: Detected SHIELD_TYPE_270X_MCM6876X\r\n");
#endif /* _DEBUG */
        return SHIELD_TYPE_270X_MCM6876X;
    }

    if (bit_0 && !bit_1)
    {
#ifdef _DEBUG
        printf("Shield type: Detected SHIELD_TYPE_1702A\r\n");
#endif /* _DEBUG */
        return SHIELD_TYPE_1702A;
    }

    // This is a fucking mess. Because I didn't anticipate more than two shields,
    // and the two previous shield designs are now "out there", subsequent designs
    // set bit 0 and 1, then we look at bits A, B and C to see which design it is.
    if (bit_0 && bit_1)
    {
        if (!bit_a && !bit_b && !bit_c)
        {
#ifdef _DEBUG
            printf("Shield type: Detected SHIELD_TYPE_MCS48\r\n");
#endif /* _DEBUG */
            return SHIELD_TYPE_MCS48;
        }
    }

#ifdef _DEBUG
    printf("Shield type: Unknown. bit_0: %u bit_1: %u\r\n", bit_0, bit_1);
#endif /* _DEBUG */
    return SHIELD_TYPE_UNKNOWN;
}

static int8_t cmd_get_next(void)
{
    uint8_t c;
    if (host_try_read8((char *)&c))
    {
        uint8_t i = 0;
        uint8_t d;

        for (i = 0; i < 100; i++)
        {
            if (host_try_read8((char *)&d))
            {
                if ((uint8_t)~d == c)
                {
                    switch (c)
                    {
                    case CMD_START_WRITE:
                    case CMD_WRITE_CHUNK:
                    case CMD_START_READ:
                    case CMD_READ_CHUNK:
                    case CMD_START_BLANK_CHECK:
                    case CMD_BLANK_CHECK:
                    case CMD_DEV_RESET:
                    case CMD_MEASURE_12V:
                    case CMD_TEST:
                    case CMD_TEST_READ:
                        return c;
                    default:
                        return -1;
                    }
                }
                else
                {
#ifdef _DEBUG
                    printf("Command compliment byte wrong. Got: 0x%02X 0x%02X\r\n", c, d);
#endif /* _DEBUG */
                    return -1;
                }
            }
            cmd_retry_delay();
        }
    }

    return -1;
}
