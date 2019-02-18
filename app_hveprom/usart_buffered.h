/*
* File:   usart_buffered.h
* Author: Matt
*
* Created on 22 May 2018, 16:32
*/

#ifndef __USART_BUFFERED_H__
#define __USART_BUFFERED_H__

#define USART_SYNC            0x01
#define USART_9BIT            0x02
#define USART_SYNC_MASTER     0x04
#define USART_CONT_RX         0x08
#define USART_BRGH            0x10
#define USART_IOR             0x20
#define USART_IOT             0x40

#define UART_BUFFER_OVERFLOW  0x02

#ifdef _USART0_

void usart0_open(uint8_t flags, uint16_t brg);
bool usart0_busy(void);
void usart0_put(char c);
bool usart0_data_ready(void);
char usart0_get(void);
uint8_t usart0_get_last_rx_error(void);

#endif /* _USART0_ */

#ifdef _USART1_

void usart1_open(uint8_t flags, uint16_t brg);
bool usart1_busy(void);
void usart1_put(char c);
bool usart1_data_ready(void);
char usart1_get(void);
uint8_t usart1_get_last_rx_error(void);

#endif /* _USART1_ */

#ifdef _USART2_

void usart2_open(uint8_t flags, uint16_t brg);
bool usart2_busy(void);
void usart2_put(char c);
bool usart2_data_ready(void);
char usart2_get(void);
uint8_t usart2_get_last_rx_error(void);

#endif /* _USART2_ */

#endif /* __USART_BUFFERED_H__ */
