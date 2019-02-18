/*
 * File:   usart.h
 * Author: Matt
 *
 * Created on 13 November 2017, 10:32
 */

#ifndef _USART_H
#define _USART_H

#define USART_SYNC         0x01
#define USART_9BIT         0x02
#define USART_SYNC_MASTER  0x04
#define USART_CONT_RX      0x08
#define USART_BRGH         0x10
#define USART_IOR          0x20
#define USART_IOT          0x40

#ifdef _USART0_

void usart0_open(uint8_t flags, uint16_t brg);
bool usart0_busy(void);
void usart0_put(char c);
bool usart0_data_ready(void);
char usart0_get(void);
void usart0_clear_oerr(void);

#endif /* _USART0_ */

#ifdef _USART1_

void usart1_open(uint8_t flags, uint16_t brg);
bool usart1_busy(void);
void usart1_put(char c);
bool usart1_data_ready(void);
char usart1_get(void);
void usart1_clear_oerr(void);

#endif /* _USART1_ */

#ifdef _USART2_

void usart2_open(uint8_t flags, uint16_t brg);
bool usart2_busy(void);
void usart2_put(char c);
bool usart2_data_ready(void);
char usart2_get(void);
void usart2_clear_oerr(void);

#endif /* _USART2_ */

#endif /* _USART_H */
