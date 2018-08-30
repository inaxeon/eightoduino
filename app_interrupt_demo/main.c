/*
 *   8OD - Arduino form factor i8086 based SBC
 *   Matthew Millman (tech.mattmillman.com)
 *
 *   Interrupt demo program
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
#include "adc.h"

uint16_t _g_intflags = 0;

char _g_a_rxChar;
char _g_b_rxChar;
char _g_c_rxChar;
char _g_d_rxChar;

#define FLG_PORTA_08_HIGH    0x001
#define FLG_PORTA_09_HIGH    0x002
#define FLG_PORTA_10_HIGH    0x004
#define FLG_PORTA_11_HIGH    0x008
#define FLG_EXTERNAL_INTA    0x010
#define FLG_EXTERNAL_INTB    0x020
#define FLG_UARTA_RX         0x040
#define FLG_UARTB_RX         0x080
#define FLG_UARTC_RX         0x100
#define FLG_UARTD_RX         0x200
#define FLG_TIMER_ELAPSED    0x400

/* Higher number = shorter period */
#define TIMER_RELOAD         0x0000

void interrupt_handler(void)
{
    /* Read status register (contains interrupt flags) */
    uint16_t status = cpld_read(STATUS);

    if (status & STATUS_PORTAF)
    {
        uint16_t porta = cpld_read(PORTA);

        /* Clear the PORTA interrupt flag
         *
         * The correct procedure for clearing interrupt flags
         * is to write a pattern containing all 1's, except the
         * bit wanting to be cleared. The CPLD ignores 1's written
         * to STATUS, so this practise doesn't end up creating
         * artificial interrupts, nor does it accidentially clear
         * anything that hasn't yet been flagged for processing.
         *
         * This ensures anything that interrupts occuring while
         * this code is running instantly generate another interrupt
         * when this function returns.
         */
        cpld_direct_write(STATUS, ~STATUS_PORTAF);

        if (porta & (1 << 8))
            _g_intflags |= FLG_PORTA_08_HIGH;

        if (porta & (1 << 9))
            _g_intflags |= FLG_PORTA_09_HIGH;

        if (porta & (1 << 10))
            _g_intflags |= FLG_PORTA_10_HIGH;

        if (porta & (1 << 11))
            _g_intflags |= FLG_PORTA_11_HIGH;
    }

    if (status & STATUS_EXTINTA)
    {
        _g_intflags |= FLG_EXTERNAL_INTA;

        /* Clear the External interrupt flag */
        cpld_direct_write(STATUS, ~STATUS_EXTINTA);
    }

    if (status & STATUS_EXTINTB)
    {
        _g_intflags |= FLG_EXTERNAL_INTB;

        /* Clear the External interrupt flag */
        cpld_direct_write(STATUS, ~STATUS_EXTINTB);
    }

    if (status & STATUS_UARTAF)
    {
        _g_intflags |= FLG_UARTA_RX;
        _g_a_rxChar = uart_blocking_getc(UARTA);

        /* UARTs clear their own interrupt flags */
    }

    if (status & STATUS_UARTBF)
    {
        _g_intflags |= FLG_UARTB_RX;
        _g_b_rxChar = uart_blocking_getc(UARTB);
    }

    if (status & STATUS_UARTCF)
    {
        _g_intflags |= FLG_UARTC_RX;
        _g_c_rxChar = uart_blocking_getc(UARTC);
    }

    if (status & STATUS_UARTDF)
    {
        _g_intflags |= FLG_UARTD_RX;
        _g_d_rxChar = uart_blocking_getc(UARTD);
    }

    if (status & STATUS_TMF)
    {
        _g_intflags |= FLG_TIMER_ELAPSED;
        /* Stop timer */
        cpld_write(CONFIG, CONFIG_TMRUN, 0);
        /* Reload timer */
        cpld_direct_write(TIMER, TIMER_RELOAD);
        /* Clear the timer flag */
        cpld_direct_write(STATUS, ~STATUS_TMF);
        /* Start timer */
        cpld_write(CONFIG, CONFIG_TMRUN, CONFIG_TMRUN);
    }
}

void main(void)
{
    uint16_t t8 = 0;
    uint16_t t9 = 0;
    uint16_t t10 = 0;
    uint16_t t11 = 0;
    uint16_t exta = 0;
    uint16_t extb = 0;
    uint16_t tmnum = 0;

    uart_open(UARTA, 115200, 8, PARITY_NONE, 1, 1);
    uart_open(UARTB, 115200, 8, PARITY_NONE, 1, 1);
    uart_open(UARTC, 115200, 8, PARITY_NONE, 1, 1);
    uart_open(UARTD, 115200, 8, PARITY_NONE, 1, 1);

    setup_printf(UARTA);

    /* Set 8, 9, 10, 11 and 2, 3 (EXTINTA and EXTINTB) of PORTA as inputs */
    cpld_write(TRISA, 0x0F0C, 0x0F0C);

    /* Enable interrupts */
    cpld_write(CONFIG, CONFIG_GINT | CONFIG_PORTAINT | CONFIG_EXTINTA | CONFIG_EXTINTB | CONFIG_UAINT
        | CONFIG_UBINT | CONFIG_UCINT | CONFIG_UDINT | CONFIG_TMINT,
        CONFIG_GINT | CONFIG_PORTAINT | CONFIG_EXTINTA | CONFIG_EXTINTB | CONFIG_UAINT | 
        CONFIG_UBINT | CONFIG_UCINT | CONFIG_UDINT | CONFIG_TMINT);

    /* Load timer */
    cpld_direct_write(TIMER, TIMER_RELOAD);
    /* Start timer */
    cpld_write(CONFIG, CONFIG_TMRUN, CONFIG_TMRUN);

    while (1)
    {
        if (_g_intflags & FLG_PORTA_08_HIGH)
        {
            printf("Button attached to PORTA/08 pressed %u times\r\n", t8++);
            _g_intflags &= ~FLG_PORTA_08_HIGH;
        }

        if (_g_intflags & FLG_PORTA_09_HIGH)
        {
            printf("Button attached to PORTA/09 pressed %u times\r\n", t9++);
            _g_intflags &= ~FLG_PORTA_09_HIGH;
        }

        if (_g_intflags & FLG_PORTA_10_HIGH)
        {
            printf("Button attached to PORTA/10 pressed %u times\r\n", t10++);
            _g_intflags &= ~FLG_PORTA_10_HIGH;
        }

        if (_g_intflags & FLG_PORTA_11_HIGH)
        {
            printf("Button attached to PORTA/11 pressed %u times\r\n", t11++);
            _g_intflags &= ~FLG_PORTA_11_HIGH;
        }

        if (_g_intflags & FLG_EXTERNAL_INTA)
        {
            printf("External interrupt PORTA/2 asserted %u times\r\n", exta++);
            _g_intflags &= ~FLG_EXTERNAL_INTA;
        }

        if (_g_intflags & FLG_EXTERNAL_INTB)
        {
            printf("External interrupt PORTA/3 asserted %u times\r\n", extb++);
            _g_intflags &= ~FLG_EXTERNAL_INTB;
        }

        if (_g_intflags & FLG_UARTA_RX)
        {
            printf("UARTA received char: %c\r\n", _g_a_rxChar);
            _g_intflags &= ~FLG_UARTA_RX;
        }

        if (_g_intflags & FLG_UARTB_RX)
        {
            printf("UARTB received char: %c\r\n", _g_b_rxChar);
            _g_intflags &= ~FLG_UARTB_RX;
        }

        if (_g_intflags & FLG_UARTC_RX)
        {
            printf("UARTC received char: %c\r\n", _g_c_rxChar);
            _g_intflags &= ~FLG_UARTC_RX;
        }

        if (_g_intflags & FLG_UARTD_RX)
        {
            printf("UARTD received char: %c\r\n", _g_d_rxChar);
            _g_intflags &= ~FLG_UARTD_RX;
        }

        if (_g_intflags & FLG_TIMER_ELAPSED)
        {
            printf("Timer elapsed %u times\r\n", tmnum++);
            _g_intflags &= ~FLG_TIMER_ELAPSED;
        }
    }
}


