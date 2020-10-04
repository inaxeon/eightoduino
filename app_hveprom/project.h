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

#ifndef _PROJECT_H
#define _PROJECT_H

//#define _DEBUG
//#ifdef _RS232_BUILD_

#define HOST_UART   UARTB
#define DEBUG_UART  UARTC

#define SHIELD_TYPE_UNKNOWN         0x00
#define SHIELD_TYPE_1702A           0x01
#define SHIELD_TYPE_270X_MCM6876X   0x02
#define SHIELD_TYPE_MCS48           0x03

#define HOST_BAUD                   38400
#define DEBUG_BAUD                  38400

#ifdef _MDUINO

#ifdef _RS232_BUILD_

#define host_usart_open        usart1_open
#define host_usart_busy        usart1_busy
#define host_usart_put         usart1_put
#define host_usart_data_ready  usart1_data_ready
#define host_usart_get         usart1_get
#define host_usart_clear_oerr  usart1_clear_oerr

#define debug_usart_open       usart0_open
#define debug_usart_busy       usart0_busy
#define debug_usart_put        usart0_put
#define debug_usart_data_ready usart0_data_ready
#define debug_usart_get        usart0_get
#define debug_usart_clear_oerr usart0_clear_oerr

#else

#define host_usart_open        usart0_open
#define host_usart_busy        usart0_busy
#define host_usart_put         usart0_put
#define host_usart_data_ready  usart0_data_ready
#define host_usart_get         usart0_get
#define host_usart_clear_oerr  usart0_clear_oerr

#define debug_usart_open       usart1_open
#define debug_usart_busy       usart1_busy
#define debug_usart_put        usart1_put
#define debug_usart_data_ready usart1_data_ready
#define debug_usart_get        usart1_get
#define debug_usart_clear_oerr usart1_clear_oerr

#endif /* _RS232_BUILD_ */

#define g_irq_disable cli
#define g_irq_enable sei

#endif /* _MDUINO */

#define _USART0_
#define _USART1_
//#define _USART2_

#endif /* _PROJECT_H */
