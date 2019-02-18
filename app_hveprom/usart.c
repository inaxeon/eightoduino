/*
 *   8OD - Arduino form factor i8086 based SBC
 *   Matthew Millman (tech.mattmillman.com/8od)
 *
 *   1702A/2704/2708/MCM68764/MCM68766 EPROM Programmer
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
#include <stdbool.h>

#include <avr/io.h>

#include "iopins.h"
#include "usart.h"

#ifdef _USART0_

void usart0_open(uint8_t flags, uint16_t brg)
{
    UCSR0C |= _BV(UMSEL01);

    if (flags & USART_SYNC)
        UCSR0C |= _BV(UMSEL00);
    else
        UCSR0C &= ~_BV(UMSEL00);

    if (flags & USART_9BIT)
    {
        UCSR0C |= _BV(UCSZ00);
        UCSR0C |= _BV(UCSZ01);
        UCSR0B |= _BV(UCSZ02);
    }
    else
    {
        UCSR0C |= _BV(UCSZ00);
        UCSR0C |= _BV(UCSZ01);
        UCSR0B &= ~_BV(UCSZ02);
    }

    if (flags & USART_SYNC)
    {
        if (flags & USART_SYNC_MASTER)
            USART0_DDR |= _BV(USART0_XCK);
        else
            USART0_DDR &= ~_BV(USART0_XCK);
    }

    if (flags & USART_CONT_RX)
        UCSR0B |= _BV(RXEN0);
    else
        UCSR0B &= ~_BV(RXEN0);

    if (flags & USART_IOR)
        UCSR0B |= _BV(RXCIE0);
    else
        UCSR0B &= ~_BV(RXCIE0);

    if (flags & USART_IOT)
        UCSR0B |= _BV(TXCIE0);
    else
        UCSR0B &= ~_BV(TXCIE0);

    UBRR0L = (brg & 0xFF);
    UBRR0H = (brg >> 8);
    
    UCSR0B |= _BV(TXEN0);

    USART0_DDR |= _BV(USART0_TX);
    USART0_DDR &= ~_BV(USART0_RX);
}

bool usart0_busy(void)
{
    if ((UCSR0A & _BV(UDRE0)) == 0)
        return true;
    return false;
}

void usart0_put(char c)
{
    UDR0 = c;
}

bool usart0_data_ready(void)
{
    if ((UCSR0A &_BV(RXC0)) != 0)
        return true;

    return false;
}

char usart0_get(void)
{
    char data;
    data = UDR0;
    return data;
}

void usart0_clear_oerr(void)
{
    UCSR0A &= ~_BV(DOR0);
}

#endif /* _USART1_ */

#ifdef _USART1_

void usart1_open(uint8_t flags, uint16_t brg)
{
    UCSR1C |= _BV(UMSEL11);

    if (flags & USART_SYNC)
        UCSR1C |= _BV(UMSEL10);
    else
        UCSR1C &= ~_BV(UMSEL10);

    if (flags & USART_9BIT)
    {
        UCSR1C |= _BV(UCSZ10);
        UCSR1C |= _BV(UCSZ11);
        UCSR1B |= _BV(UCSZ12);
    }
    else
    {
        UCSR1C |= _BV(UCSZ10);
        UCSR1C |= _BV(UCSZ11);
        UCSR1B &= ~_BV(UCSZ12);
    }

    if (flags & USART_SYNC)
    {
        if (flags & USART_SYNC_MASTER)
            USART1_DDR |= _BV(USART1_XCK);
        else
            USART1_DDR &= ~_BV(USART1_XCK);
    }

    if (flags & USART_CONT_RX)
        UCSR1B |= _BV(RXEN1);
    else
        UCSR1B &= ~_BV(RXEN1);

    if (flags & USART_IOR)
        UCSR1B |= _BV(RXCIE1);
    else
        UCSR1B &= ~_BV(RXCIE1);

    if (flags & USART_IOT)
        UCSR1B |= _BV(TXCIE1);
    else
        UCSR1B &= ~_BV(TXCIE1);

    UBRR1L = (brg & 0xFF);
    UBRR1H = (brg >> 8);

    UCSR1B |= _BV(TXEN1);

    USART1_DDR |= _BV(USART1_TX);
    USART1_DDR &= ~_BV(USART1_RX);
}

bool usart1_busy(void)
{
    if ((UCSR1A & _BV(UDRE1)) == 0)
        return true;
    return false;
}

void usart1_put(char c)
{
    UDR1 = c;
}

bool usart1_data_ready(void)
{
    if ((UCSR1A &_BV(RXC1)) != 0)
        return true;

    return false;
}

char usart1_get(void)
{
    char data;
    data = UDR1;
    return data;
}

void usart1_clear_oerr(void)
{
    UCSR1A &= ~_BV(DOR1);
}

#endif /* _USART1_ */

#ifdef _USART2_

void usart2_open(uint8_t flags, uint16_t brg)
{
    UCSR2C |= _BV(UMSEL21);

    if (flags & USART_SYNC)
        UCSR2C |= _BV(UMSEL20);
    else
        UCSR2C &= ~_BV(UMSEL20);

    if (flags & USART_9BIT)
    {
        UCSR2C |= _BV(UCSZ20);
        UCSR2C |= _BV(UCSZ21);
        UCSR2B |= _BV(UCSZ22);
    }
    else
    {
        UCSR2C |= _BV(UCSZ20);
        UCSR2C |= _BV(UCSZ21);
        UCSR2B &= ~_BV(UCSZ22);
    }

    if (flags & USART_SYNC)
    {
        if (flags & USART_SYNC_MASTER)
            USART2_DDR |= _BV(USART2_XCK);
        else
            USART2_DDR &= ~_BV(USART2_XCK);
    }

    if (flags & USART_CONT_RX)
        UCSR2B |= _BV(RXEN2);
    else
        UCSR2B &= ~_BV(RXEN2);

    if (flags & USART_IOR)
        UCSR2B |= _BV(RXCIE2);
    else
        UCSR2B &= ~_BV(RXCIE2);

    if (flags & USART_IOT)
        UCSR2B |= _BV(TXCIE2);
    else
        UCSR2B &= ~_BV(TXCIE2);

    UBRR2L = (brg & 0xFF);
    UBRR2H = (brg >> 8);

    UCSR2B |= _BV(TXEN1);

    USART2_DDR |= _BV(USART2_TX);
    USART2_DDR &= ~_BV(USART2_RX);
}

bool usart2_busy(void)
{
    if ((UCSR2A & _BV(UDRE2)) == 0)
        return true;
    return false;
}

void usart2_put(char c)
{
    UDR2 = c;
}

bool usart2_data_ready(void)
{
    if ((UCSR2A &_BV(RXC2)) != 0)
        return true;

    return false;
}

char usart2_get(void)
{
    char data;
    data = UDR2;
    return data;
}

void usart2_clear_oerr(void)
{
    UCSR2A &= ~_BV(DOR2);
}

#endif /* _USART2_ */
