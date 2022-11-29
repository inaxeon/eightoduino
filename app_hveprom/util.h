/*
 *   8OD - Arduino form factor i8086 based SBC
 *   Matthew Millman (tech.mattmillman.com/8od)
 *
 *   1702A/2704/2708/TMS2716/MCM6876x/MCS48 EPROM Programmer
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

#ifndef _UTIL_H
#define _UTIL_H

#ifdef _M8OD

#define cmd_respond(cmd, x) do { uart_putc(HOST_UART, cmd); uart_putc(HOST_UART, x); } while (0)
#define cmd_retry_delay() delay_ncycles(1 * 554)

#define host_read8() uart_blocking_getc(HOST_UART)
#define host_try_read8(x) uart_getc(HOST_UART, x)
#define host_write8(x) uart_putc(HOST_UART, x)
#define host_write16(x) do { uart_putc(HOST_UART, ((uint8_t)(((uint16_t)x) >> 8)));    \
                             uart_putc(HOST_UART, ((uint8_t)(((uint16_t)x) & 0xFF)));  \
                           } while (0)
#define host_write32(x) do { uart_putc(HOST_UART, ((uint8_t)(((uint32_t)x) >> 24)));   \
                             uart_putc(HOST_UART, ((uint8_t)(((uint32_t)x) >> 16)));   \
                             uart_putc(HOST_UART, ((uint8_t)(((uint32_t)x) >> 8)));    \
                             uart_putc(HOST_UART, ((uint8_t)(((uint32_t)x) & 0xFF)));  \
                           } while (0)

#endif /* _M8OD */

#ifdef _MDUINO

#define cmd_respond(cmd, x) do { while (host_usart_busy()); host_usart_put(cmd); while (host_usart_busy()); host_usart_put(x); } while (0)
#define cmd_retry_delay() _delay_ms(1)

#define host_read8() host_blocking_getc() 
#define host_try_read8(x) host_getc(x)
#define host_write8(x)  do { while (host_usart_busy()); host_usart_put(x); } while (0)
#define host_write16(x) do { while (host_usart_busy()); host_usart_put(((uint8_t)(((uint16_t)x) >> 8)));   \
                             while (host_usart_busy()); host_usart_put(((uint8_t)(((uint16_t)x) & 0xFF))); \
                           } while (0)
#define host_write32(x) do { while (host_usart_busy()); host_usart_put(((uint8_t)(((uint32_t)x) >> 24)));  \
                             while (host_usart_busy()); host_usart_put(((uint8_t)(((uint32_t)x) >> 16)));  \
                             while (host_usart_busy()); host_usart_put(((uint8_t)(((uint32_t)x) >> 8)));   \
                             while (host_usart_busy()); host_usart_put(((uint8_t)(((uint32_t)x) & 0xFF))); \
                           } while (0)

char host_blocking_getc(void);
bool host_getc(char *c);
int print_char(char byte, FILE *stream);

#undef printf
#define printf(fmt, ...) printf_P(PSTR(fmt) __VA_OPT__(,) __VA_ARGS__)
#define sprintf(buf, fmt, ...) sprintf_P(buf, PSTR(fmt) __VA_OPT__(,) __VA_ARGS__)
#define strcmp_p(str, to) strcmp_P(str, PSTR(to))
#define strncmp_p(str, to, n) strncmp_P(str, PSTR(to), n)
#define stricmp(str, to) strcasecmp_P(str, PSTR(to))

#endif /* _MDUINO */

#define infinite_loop() do {} while (1)

#endif /* _UTIL_H */
