/*
* File:   usart_buffered.c
* Author: Matt
*
* Created on 22 May 2018, 16:32
*/

#include "project.h"

#include <stdint.h>
#include <stdbool.h>

#include <avr/io.h>
#include <avr/interrupt.h>

#include "iopins.h"
#include "usart_buffered.h"

#ifdef _USART0_

#define UART0_TX_BUFFER_SIZE 16
#define UART0_RX_BUFFER_SIZE 32

/* size of RX/TX buffers */
#define UART0_RX_BUFFER_MASK (UART0_RX_BUFFER_SIZE - 1)
#define UART0_TX_BUFFER_MASK (UART0_TX_BUFFER_SIZE - 1)

#if (UART0_RX_BUFFER_SIZE & UART0_RX_BUFFER_MASK)
#error RX buffer size is not a power of 2
#endif
#if (UART0_TX_BUFFER_SIZE & UART0_TX_BUFFER_MASK)
#error TX buffer size is not a power of 2
#endif

static volatile uint8_t _g_usart0_txbuf[UART0_TX_BUFFER_SIZE];
static volatile uint8_t _g_usart0_rxbuf[UART0_RX_BUFFER_SIZE];
static volatile uint8_t _g_usart0_txhead;
static volatile uint8_t _g_usart0_txtail;
static volatile uint8_t _g_usart0_rxhead;
static volatile uint8_t _g_usart0_rxtail;
static volatile uint8_t _g_usart0_last_rx_error;

ISR(USART0_RX_vect)
{
    uint8_t tmphead;
    uint8_t data;
    uint8_t usr;
    uint8_t lastRxError;
 
    usr  = UCSR0A;
    data = UDR0;
    
    lastRxError = (usr & (_BV(FE0) | _BV(DOR0)));
    tmphead = (_g_usart0_rxhead + 1) & UART0_RX_BUFFER_MASK;
    
    if (tmphead == _g_usart0_rxtail)
    {
        lastRxError = UART_BUFFER_OVERFLOW >> 8;
    }
    else
    {
        _g_usart0_rxhead = tmphead;
        _g_usart0_rxbuf[tmphead] = data;
    }

    _g_usart0_last_rx_error = lastRxError;   
}

ISR(USART0_UDRE_vect)
{
    uint8_t tmptail;
    
    if (_g_usart0_txhead != _g_usart0_txtail)
    {
        tmptail = (_g_usart0_txtail + 1) & UART0_TX_BUFFER_MASK;
        _g_usart0_txtail = tmptail;
        UDR0 = _g_usart0_txbuf[tmptail];
    }
    else
    {
        UCSR0B &= ~_BV(UDRIE0);
    }
}

void usart0_open(uint8_t flags, uint16_t brg)
{
    _g_usart0_txhead = 0;
    _g_usart0_txtail = 0;
    _g_usart0_rxhead = 0;
    _g_usart0_rxtail = 0;
    
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

    UCSR0B |= _BV(RXCIE0);

    UBRR0L = (brg & 0xFF);
    UBRR0H = (brg >> 8);

    UCSR0B |= _BV(TXEN0);

    USART0_DDR |= _BV(USART0_TX);
    USART0_DDR &= ~_BV(USART0_RX);
}

bool usart0_data_ready(void)
{
    if (_g_usart0_rxhead == _g_usart0_rxtail)
        return false;
    return true;
}

char usart0_get(void)
{
    uint8_t tmptail;

    if (_g_usart0_rxhead == _g_usart0_rxtail)
        return 0x00;
    
    tmptail = (_g_usart0_rxtail + 1) & UART0_RX_BUFFER_MASK;
    _g_usart0_rxtail = tmptail;
    
    return _g_usart0_rxbuf[tmptail];
}

void usart0_put(char c)
{
    uint8_t tmphead = (_g_usart0_txhead + 1) & UART0_TX_BUFFER_MASK;
    
    while (tmphead == _g_usart0_txtail);
    
    _g_usart0_txbuf[tmphead] = c;
    _g_usart0_txhead = tmphead;

    UCSR0B |= _BV(UDRIE0);
}

bool usart0_busy(void)
{
    return (_g_usart0_txhead != _g_usart0_txtail || (UCSR0A & _BV(UDRE0)) == 0);
}

uint8_t usart0_get_last_rx_error(void)
{
    return _g_usart0_last_rx_error;
}

#endif /* _USART0_ */

#ifdef _USART1_

#define UART1_TX_BUFFER_SIZE 16
#define UART1_RX_BUFFER_SIZE 32

/* size of RX/TX buffers */
#define UART1_RX_BUFFER_MASK (UART1_RX_BUFFER_SIZE - 1)
#define UART1_TX_BUFFER_MASK (UART1_TX_BUFFER_SIZE - 1)

#if (UART1_RX_BUFFER_SIZE & UART1_RX_BUFFER_MASK)
#error RX buffer size is not a power of 2
#endif
#if (UART1_TX_BUFFER_SIZE & UART1_TX_BUFFER_MASK)
#error TX buffer size is not a power of 2
#endif

static volatile uint8_t _g_usart1_txbuf[UART1_TX_BUFFER_SIZE];
static volatile uint8_t _g_usart1_rxbuf[UART1_RX_BUFFER_SIZE];
static volatile uint8_t _g_usart1_txhead;
static volatile uint8_t _g_usart1_txtail;
static volatile uint8_t _g_usart1_rxhead;
static volatile uint8_t _g_usart1_rxtail;
static volatile uint8_t _g_usart1_last_rx_error;

ISR(USART1_RX_vect)
{
    uint8_t tmphead;
    uint8_t data;
    uint8_t usr;
    uint8_t lastRxError;
 
    usr  = UCSR1A;
    data = UDR1;
    
    lastRxError = (usr & (_BV(FE1) | _BV(DOR1)));
    tmphead = (_g_usart1_rxhead + 1) & UART1_RX_BUFFER_MASK;
    
    if (tmphead == _g_usart1_rxtail)
    {
        lastRxError = UART_BUFFER_OVERFLOW >> 8;
    }
    else
    {
        _g_usart1_rxhead = tmphead;
        _g_usart1_rxbuf[tmphead] = data;
    }

    _g_usart1_last_rx_error = lastRxError;   
}

ISR(USART1_UDRE_vect)
{
    uint8_t tmptail;
    
    if (_g_usart1_txhead != _g_usart1_txtail)
    {
        tmptail = (_g_usart1_txtail + 1) & UART1_TX_BUFFER_MASK;
        _g_usart1_txtail = tmptail;
        UDR1 = _g_usart1_txbuf[tmptail];
    }
    else
    {
        UCSR1B &= ~_BV(UDRIE1);
    }
}

void usart1_open(uint8_t flags, uint16_t brg)
{
    _g_usart1_txhead = 0;
    _g_usart1_txtail = 0;
    _g_usart1_rxhead = 0;
    _g_usart1_rxtail = 0;
    
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

    UCSR1B |= _BV(RXCIE1);

    UBRR1L = (brg & 0xFF);
    UBRR1H = (brg >> 8);

    UCSR1B |= _BV(TXEN1);

    USART1_DDR |= _BV(USART1_TX);
    USART1_DDR &= ~_BV(USART1_RX);
}

bool usart1_data_ready(void)
{
    if (_g_usart1_rxhead == _g_usart1_rxtail)
        return false;
    return true;
}

char usart1_get(void)
{
    uint8_t tmptail;

    if (_g_usart1_rxhead == _g_usart1_rxtail)
        return 0x00;
    
    tmptail = (_g_usart1_rxtail + 1) & UART1_RX_BUFFER_MASK;
    _g_usart1_rxtail = tmptail;
    
    return _g_usart1_rxbuf[tmptail];
}

void usart1_put(char c)
{
    uint8_t tmphead = (_g_usart1_txhead + 1) & UART1_TX_BUFFER_MASK;
    
    while (tmphead == _g_usart1_txtail);
    
    _g_usart1_txbuf[tmphead] = c;
    _g_usart1_txhead = tmphead;

    UCSR1B |= _BV(UDRIE1);
}

bool usart1_busy(void)
{
    return (_g_usart1_txhead != _g_usart1_txtail || (UCSR1A & _BV(UDRE1)) == 0);
}

uint8_t usart1_get_last_rx_error(void)
{
    return _g_usart1_last_rx_error;
}

#endif /* _USART1_ */

#ifdef _USART2_

#define UART2_TX_BUFFER_SIZE 16
#define UART2_RX_BUFFER_SIZE 16

/* size of RX/TX buffers */
#define UART2_RX_BUFFER_MASK (UART2_RX_BUFFER_SIZE - 1)
#define UART2_TX_BUFFER_MASK (UART2_TX_BUFFER_SIZE - 1)

#if (UART2_RX_BUFFER_SIZE & UART2_RX_BUFFER_MASK)
#error RX buffer size is not a power of 2
#endif
#if (UART2_TX_BUFFER_SIZE & UART2_TX_BUFFER_MASK)
#error TX buffer size is not a power of 2
#endif

static volatile uint8_t _g_usart2_txbuf[UART2_TX_BUFFER_SIZE];
static volatile uint8_t _g_usart2_rxbuf[UART2_RX_BUFFER_SIZE];
static volatile uint8_t _g_usart2_txhead;
static volatile uint8_t _g_usart2_txtail;
static volatile uint8_t _g_usart2_rxhead;
static volatile uint8_t _g_usart2_rxtail;
static volatile uint8_t _g_usart2_last_rx_error;

ISR(USART2_RX_vect)
{
    uint8_t tmphead;
    uint8_t data;
    uint8_t usr;
    uint8_t lastRxError;
 
    usr  = UCSR2A;
    data = UDR2;
    
    lastRxError = (usr & (_BV(FE2) | _BV(DOR2)));
    tmphead = (_g_usart2_rxhead + 1) & UART2_RX_BUFFER_MASK;
    
    if (tmphead == _g_usart2_rxtail)
    {
        lastRxError = UART_BUFFER_OVERFLOW >> 8;
    }
    else
    {
        _g_usart2_rxhead = tmphead;
        _g_usart2_rxbuf[tmphead] = data;
    }

    _g_usart2_last_rx_error = lastRxError;   
}

ISR(USART2_UDRE_vect)
{
    uint8_t tmptail;
    
    if (_g_usart2_txhead != _g_usart2_txtail)
    {
        tmptail = (_g_usart2_txtail + 1) & UART2_TX_BUFFER_MASK;
        _g_usart2_txtail = tmptail;
        UDR2 = _g_usart2_txbuf[tmptail];
    }
    else
    {
        UCSR2B &= ~_BV(UDRIE2);
    }
}

void usart2_open(uint8_t flags, uint16_t brg)
{
    _g_usart2_txhead = 0;
    _g_usart2_txtail = 0;
    _g_usart2_rxhead = 0;
    _g_usart2_rxtail = 0;
    
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

    UCSR2B |= _BV(RXCIE2);

    UBRR2L = (brg & 0xFF);
    UBRR2H = (brg >> 8);

    UCSR2B |= _BV(TXEN2);

    USART2_DDR |= _BV(USART2_TX);
    USART2_DDR &= ~_BV(USART2_RX);
}

bool usart2_data_ready(void)
{
    if (_g_usart2_rxhead == _g_usart2_rxtail)
        return false;
    return true;
}

char usart2_get(void)
{
    uint8_t tmptail;

    if (_g_usart2_rxhead == _g_usart2_rxtail)
        return 0x00;
    
    tmptail = (_g_usart2_rxtail + 1) & UART2_RX_BUFFER_MASK;
    _g_usart2_rxtail = tmptail;
    
    return _g_usart2_rxbuf[tmptail];
}

void usart2_put(char c)
{
    uint8_t tmphead = (_g_usart2_txhead + 1) & UART2_TX_BUFFER_MASK;
    
    while (tmphead == _g_usart2_txtail);
    
    _g_usart2_txbuf[tmphead] = c;
    _g_usart2_txhead = tmphead;

    UCSR2B |= _BV(UDRIE2);
}

bool usart2_busy(void)
{
    return (_g_usart2_txhead != _g_usart2_txtail || (UCSR2A & _BV(UDRE2)) == 0);
}

uint8_t usart2_get_last_rx_error(void)
{
    return _g_usart2_last_rx_error;
}

#endif /* _USART2_ */
