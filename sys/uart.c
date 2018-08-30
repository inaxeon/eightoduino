/*
 *   8OD - Arduino form factor i8086 based SBC
 *   Matthew Millman (tech.mattmillman.com)
 *
 *   16550A UART Driver
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
#include "eod_io.h"
#include "eod_map.h"
#include "uart.h"

static struct ns16550 {
    uint32_t baud;
    int data_bits;
    int parity;
    int stop_bits;
    uint16_t io_base;
    int enable_rx_int;
} ns16550_instance[4];

static int8_t _g_printfInstance = 0;

/* Register offsets */
#define RBR             0x00    /* receive buffer       */
#define THR             0x00    /* transmit holding     */
#define IER             0x01    /* interrupt enable     */
#define IIR             0x02    /* interrupt identity   */
#define FCR             0x02    /* FIFO control         */
#define LCR             0x03    /* line control         */
#define MCR             0x04    /* Modem control        */
#define LSR             0x05    /* line status          */
#define MSR             0x06    /* Modem status         */
#define DLL             0x00    /* divisor latch (ls) (DLAB=1) */
#define DLM             0x01    /* divisor latch (ms) (DLAB=1) */

/* Interrupt Enable Register */
#define IER_ERDAI       0x01    /* rx data recv'd       */
#define IER_ETHREI      0x02    /* tx reg. empty        */
#define IER_ELSI        0x04    /* rx line status       */
#define IER_EMSI        0x08    /* MODEM status         */

/* Interrupt Identification Register */
#define IIR_NOINT       0x01    /* no interrupt pending */
#define IIR_IMASK       0x06    /* interrupt identity:  */
#define IIR_LSI         0x06    /*  - rx line status    */
#define IIR_RDAI        0x04    /*  - rx data recv'd    */
#define IIR_THREI       0x02    /*  - tx reg. empty     */
#define IIR_MSI         0x00    /*  - MODEM status      */

/* FIFO Control Register */
#define FCR_ENABLE      0x01    /* enable FIFO          */
#define FCR_CLRX        0x02    /* clear Rx FIFO        */
#define FCR_CLTX        0x04    /* clear Tx FIFO        */
#define FCR_DMA         0x10    /* enter DMA mode       */
#define FCR_TRG1        0x00    /* Rx FIFO trig lev 1   */
#define FCR_TRG4        0x40    /* Rx FIFO trig lev 4   */
#define FCR_TRG8        0x80    /* Rx FIFO trig lev 8   */
#define FCR_TRG14       0xc0    /* Rx FIFO trig lev 14  */

/* Line Control Register */
#define LCR_DLAB        0x80    /* Divisor Latch Access */

/* Modem Control Register */
#define MCR_DTR         0x01    /* Data Terminal Ready  */
#define MCR_RTS         0x02    /* Request to Send      */
#define MCR_OUT2        0x08    /* OUT2: interrupt mask */

/* Line Status Register */
#define LSR_DR          0x01    /* Data ready           */
#define LSR_OE          0x02    /* Overrun              */
#define LSR_PE          0x04    /* Parity error         */
#define LSR_FE          0x08    /* Framing error        */
#define LSR_BI          0x10    /* Break                */
#define LSR_THRE        0x20    /* Xmit hold reg empty  */
#define LSR_TEMT        0x40    /* Xmitter empty        */
#define LSR_ERR         0x80    /* Error                */

/* These parity settings can be ORed directly into the LCR. */
#define PARITY_NONE     (0<<3)
#define PARITY_ODD      (1<<3)
#define PARITY_EVEN     (3<<3)
#define PARITY_MARK     (5<<3)
#define PARITY_SPACE    (7<<3)

#define UART_CLOCK_HZ   7372800

#define uart_read_reg(uart, reg)       inp(uart->io_base + reg)
#define uart_write_reg(uart, reg, c)   outp(uart->io_base + reg, c)

static void uart_ns16550_init(struct ns16550 *uart)
{
    unsigned char lcr;
    unsigned int  divisor;

    lcr = (uart->data_bits - 5) | ((uart->stop_bits - 1) << 2) | uart->parity;

    if (uart->enable_rx_int)
        uart_write_reg(uart, IER, IER_ERDAI);    
    else
        uart_write_reg(uart, IER, 0);

    /* Line control and baud-rate generator. */
    uart_write_reg(uart, LCR, lcr | LCR_DLAB);
    divisor = UART_CLOCK_HZ / (uart->baud * 16);
    uart_write_reg(uart, DLL, (char)divisor);
    uart_write_reg(uart, DLM, (char)(divisor >> 8));

    uart_write_reg(uart, LCR, lcr);

    /* No flow ctrl: DTR and RTS are both wedged high to keep remote happy. */
    uart_write_reg(uart, MCR, MCR_DTR | MCR_RTS | MCR_OUT2);

    /* Enable and clear the FIFOs. Set a large trigger threshold. */
    uart_write_reg(uart, FCR, FCR_ENABLE | FCR_CLRX | FCR_CLTX | FCR_TRG14);
}


void uart_open(int index, uint32_t baud, int data_bits, int parity, int stop_bits, int rxint)
{
    struct ns16550 *uart = &ns16550_instance[index];

    if ((index < UARTA) || (index > UARTD))
        return;

    uart->baud             = baud;
    uart->data_bits        = data_bits;
    uart->parity           = parity;
    uart->stop_bits        = stop_bits;
    uart->enable_rx_int    = rxint;

    switch (index)
    {
    case UARTA:
        uart->io_base = UARTA_BASE;
        cpld_write(CONFIG, CONFIG_UAEN, CONFIG_UAEN);
        cpld_write(TRISA, 0x0003, 0x0001);
        break;
    case UARTB:
        uart->io_base = UARTB_BASE;
        cpld_write(CONFIG, CONFIG_UBEN, CONFIG_UBEN);
        cpld_write(TRISB, 0x000C, 0x0008);
        break;
    case UARTC:
        uart->io_base = UARTC_BASE;
        cpld_write(CONFIG, CONFIG_UCEN, CONFIG_UCEN);
        cpld_write(TRISB, 0x0003, 0x0002);
        break;
    case UARTD:
        uart->io_base = UARTD_BASE;
        cpld_write(CONFIG, CONFIG_UDEN, CONFIG_UDEN);
        cpld_write(TRISA, 0xC000, 0x8000);
        break;
    }

    uart_ns16550_init(uart);
}

void uart_pgm_open(void)
{
    struct ns16550 *uart = &ns16550_instance[UARTD];
    
    uart->baud             = 115200;
    uart->data_bits        = 8;
    uart->parity           = PARITY_NONE;
    uart->stop_bits        = 1;
    uart->enable_rx_int    = 0;
    uart->io_base          = UARTD_BASE;
    
    cpld_write(CONFIG, CONFIG_UDEN, 0);

    uart_ns16550_init(uart);
}

void uart_close(int index)
{
    switch (index)
    {
    case UARTA:
        cpld_write(CONFIG, CONFIG_UAEN, 0);
        break;
    case UARTB:
        cpld_write(CONFIG, CONFIG_UBEN, 0);
        break;
    case UARTC:
        cpld_write(CONFIG, CONFIG_UCEN, 0);
        break;
    case UARTD:
        cpld_write(CONFIG, CONFIG_UDEN, 0);
        break;
    }
}

void uart_putc(int index, char c)
{
    struct ns16550 *uart = &ns16550_instance[index];

    while ((uart_read_reg(uart, LSR) & LSR_THRE) == 0);
    uart_write_reg(uart, THR, c);
}

void uart_wait_tx(int index)
{
    struct ns16550 *uart = &ns16550_instance[index];

    while ((uart_read_reg(uart, LSR) & LSR_TEMT) == 0);
}

int uart_getc(int index, char *pc)
{
    struct ns16550 *uart = &ns16550_instance[index];

    if (!(uart_read_reg(uart, LSR) & LSR_DR))
        return 0;

    *pc = uart_read_reg(uart, RBR);
    return 1;
}

char uart_blocking_getc(int index)
{
    struct ns16550 *uart = &ns16550_instance[index];

    while (!(uart_read_reg(uart, LSR) & LSR_DR));

    return uart_read_reg(uart, RBR);
}

uint16_t uart_read(int index, uint16_t count, void *buf)
{
    struct ns16550 *uart = &ns16550_instance[index];
    uint8_t *readBytes = (uint8_t *)buf;
    uint16_t read = 0;
   
    while (read < count)
    {
        while (!(uart_read_reg(uart, LSR) & LSR_DR));
        readBytes[read] = uart_read_reg(uart, RBR);
        read++;
    }

    return read;
}

void setup_printf(int index)
{
    _g_printfInstance = index;
}

_WCRTLINK int fputc(int c, FILE *fp)
{
    uart_putc(_g_printfInstance, (char)c);
    return c;
}
