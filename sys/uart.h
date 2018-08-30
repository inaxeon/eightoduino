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

#ifndef __UART_H__
#define __UART_H__

#define UARTA   0
#define UARTB   1
#define UARTC   2
#define UARTD   3

/* Values to OR straight on to the LCR. No need to mess around I thinks. */
#define PARITY_NONE     (0<<3)
#define PARITY_ODD      (1<<3)
#define PARITY_EVEN     (3<<3)
#define PARITY_MARK     (5<<3)
#define PARITY_SPACE    (7<<3)

void uart_open(int index, uint32_t baud, int data_bits, int parity, int stop_bits, int rxint);
void uart_pgm_open(void);
void uart_close(int index);
void uart_putc(int index, char c);
void uart_wait_tx(int index);
int uart_getc(int index, char *pc);
uint16_t uart_read(int index, uint16_t count, void *buf);
char uart_blocking_getc(int index);
void setup_printf(int index);

#endif /* __UART_H__ */
