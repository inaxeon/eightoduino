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

#ifndef __IOPINS_H__
#define __IOPINS_H__

#ifdef _M8OD


#define SHIELD_ID_A               0x0001
#define SHIELD_ID_B               0x0002
#define SHIELD_ID_C               0x0004

#define SHIELD_ID_0               0x0008
#define SHIELD_ID_1               0x0010

#define MCMX_270X_DEVSEL          0x0020
#define MCMX_270X_NC_0            0x0040
#define MCMX_270X_NC_1            0x0080
#define MCMX_270X_WR              0x0100
#define MCMX_270X_RD              0x0200
#define MCMX_270X_PE              0x0400
#define MCMX_270X_PON             0x0800
#define MCMX_270X_NC_2            0x1000

#define C1702A_NC_0               0x0004
#define C1702A_IMAX               0x0020
#define C1702A_REN                0x0040
#define C1702A_PGMEN              0x0080
#define C1702A_CSEN               0x0100
#define C1702A_PEN                0x0200
#define C1702A_PGMVDD             0x0400
#define C1702A_PGMPWREN           0x0800
#define C1702A_READPWREN          0x1000

#define MCS48_CS                  0x2000
#define MCS48_A0                  0x1000
#define MCS48_PON                 0x0800
#define MCS48_PROGEN              0x0400
#define MCS48_EA                  0x0200
#define MCS48_ALE                 0x0100
#define MCS48_TEST0               0x0080
#define MCS48_VDDEN               0x0040
#define MCS48_RESET               0x0020

#define CTRL_PORT                 PORTA
#define CTRL_TRIS                 TRISA

#define DATA_PORT                 PORTC
#define DATA_TRIS                 TRISC

#endif /* _M8OD */

#ifdef _MDUINO

#define SHIELD_ID_0               PE5
#define SHIELD_ID_0_DDR           DDRE
#define SHIELD_ID_0_PIN           PINE

#define SHIELD_ID_1               PG5
#define SHIELD_ID_1_DDR           DDRG
#define SHIELD_ID_1_PIN           PING

#define SHIELD_ID_A               PH0
#define SHIELD_ID_A_DDR           DDRH
#define SHIELD_ID_A_PIN           PINH

#define SHIELD_ID_B               PH1
#define SHIELD_ID_B_DDR           DDRH
#define SHIELD_ID_B_PIN           PINH

#define SHIELD_ID_C               PE4
#define SHIELD_ID_C_DDR           DDRE
#define SHIELD_ID_C_PIN           PINE

#define MCMX_270X_DEVSEL          PE3
#define MCMX_270X_DEVSEL_DDR      DDRE
#define MCMX_270X_DEVSEL_PIN      PINE

#define MCMX_270X_NC_0            PE3
#define MCMX_270X_NC_0_DDR        DDRE

#define MCMX_270X_NC_1            PH3
#define MCMX_270X_NC_1_DDR        DDRH

#define MCMX_270X_NC_2            PH4
#define MCMX_270X_NC_2_DDR        DDRH

#define MCMX_270X_WR              PH5
#define MCMX_270X_WR_DDR          DDRH
#define MCMX_270X_WR_PORT         PORTH

#define MCMX_270X_RD              PH6
#define MCMX_270X_RD_DDR          DDRH
#define MCMX_270X_RD_PORT         PORTH

#define MCMX_270X_PE              PB4
#define MCMX_270X_PE_DDR          DDRB
#define MCMX_270X_PE_PORT         PORTB

#define MCMX_270X_PON             PB5
#define MCMX_270X_PON_DDR         DDRB
#define MCMX_270X_PON_PORT        PORTB

#define MCMX_270X_NC_3            PB6
#define MCMX_270X_NC_3_DDR        DDRB

#define C1702A_NC_0               PE4
#define C1702A_NC_0_DDR           DDRE

#define C1702A_IMAX               PE3
#define C1702A_IMAX_DDR           DDRE
#define C1702A_IMAX_PIN           PINE

#define C1702A_REN                PH3
#define C1702A_REN_DDR            DDRH
#define C1702A_REN_PORT           PORTH

#define C1702A_PGMEN              PH4
#define C1702A_PGMEN_DDR          DDRH
#define C1702A_PGMEN_PORT         PORTH

#define C1702A_CSEN               PH5
#define C1702A_CSEN_DDR           DDRH
#define C1702A_CSEN_PORT          PORTH

#define C1702A_PEN                PH6
#define C1702A_PEN_DDR            DDRH
#define C1702A_PEN_PORT           PORTH

#define C1702A_PGMVDD             PB4
#define C1702A_PGMVDD_DDR         DDRB
#define C1702A_PGMVDD_PORT        PORTB

#define C1702A_PGMPWREN           PB5
#define C1702A_PGMPWREN_DDR       DDRB
#define C1702A_PGMPWREN_PORT      PORTB
#define C1702A_PGMPWREN_PIN       PINB

#define C1702A_READPWREN          PB6
#define C1702A_READPWREN_DDR      DDRB
#define C1702A_READPWREN_PORT     PORTB
#define C1702A_READPWREN_PIN      PINB

#define MCS48_CS                  PB7
#define MCS48_CS_DDR              DDRB
#define MCS48_CS_PORT             PORTB

#define MCS48_A0                  PB6
#define MCS48_A0_DDR              DDRB
#define MCS48_A0_PORT             PORTB

#define MCS48_PON                 PB5
#define MCS48_PON_DDR             DDRB
#define MCS48_PON_PORT            PORTB
#define MCS48_PON_PIN             PINB

#define MCS48_PROGEN              PB4
#define MCS48_PROGEN_DDR          DDRB
#define MCS48_PROGEN_PORT         PORTB

#define MCS48_EA                  PH6
#define MCS48_EA_DDR              DDRH
#define MCS48_PORT                PORTH

#define MCS48_ALE                 PH5
#define MCS48_ALE_DDR             DDRH
#define MCS48_ALE_PORT            PORTH
#define MCS48_ALE_PIN             PINH

#define MCS48_TEST0               PH4
#define MCS48_TEST0_DDR           DDRH
#define MCS48_TEST0_PORT          PORTH

#define MCS48_VDDEN               PH3
#define MCS48_VDDEN_DDR           DDRH
#define MCS48_VDDEN_PORT          PORTH

#define MCS48_RESET               PE3
#define MCS48_RESET_DDR           DDRE
#define MCS48_RESET_PORT          PORTE

#define ADDRESS_0                 PD7
#define ADDRESS_0_DDR             DDRD
#define ADDRESS_0_PORT            PORTD
#define ADDRESS_0_PIN             PIND

#define ADDRESS_1                 PG2
#define ADDRESS_1_DDR             DDRG
#define ADDRESS_1_PORT            PORTG
#define ADDRESS_1_PIN             PING

#define ADDRESS_2                 PG1
#define ADDRESS_2_DDR             DDRG
#define ADDRESS_2_PORT            PORTG
#define ADDRESS_2_PIN             PING

#define ADDRESS_3                 PG0
#define ADDRESS_3_DDR             DDRG
#define ADDRESS_3_PORT            PORTG
#define ADDRESS_3_PIN             PING

#define ADDRESS_4                 PL7
#define ADDRESS_4_DDR             DDRL
#define ADDRESS_4_PORT            PORTL
#define ADDRESS_4_PIN             PINL

#define ADDRESS_5                 PL6
#define ADDRESS_5_DDR             DDRL
#define ADDRESS_5_PORT            PORTL
#define ADDRESS_5_PIN             PINL

#define ADDRESS_6                 PL5
#define ADDRESS_6_DDR             DDRL
#define ADDRESS_6_PORT            PORTL
#define ADDRESS_6_PIN             PINL

#define ADDRESS_7                 PL4
#define ADDRESS_7_DDR             DDRL
#define ADDRESS_7_PORT            PORTL
#define ADDRESS_7_PIN             PINL

#define ADDRESS_8                 PL3
#define ADDRESS_8_DDR             DDRL
#define ADDRESS_8_PORT            PORTL
#define ADDRESS_8_PIN             PINL

#define ADDRESS_9                 PL2
#define ADDRESS_9_DDR             DDRL
#define ADDRESS_9_PORT            PORTL
#define ADDRESS_9_PIN             PINL

#define ADDRESS_10                PL1
#define ADDRESS_10_DDR            DDRL
#define ADDRESS_10_PORT           PORTL
#define ADDRESS_10_PIN            PINL

#define ADDRESS_11                PL0
#define ADDRESS_11_DDR            DDRL
#define ADDRESS_11_PORT           PORTL
#define ADDRESS_11_PIN            PINL

#define ADDRESS_12                PB3
#define ADDRESS_12_DDR            DDRB
#define ADDRESS_12_PORT           PORTB
#define ADDRESS_12_PIN            PINB

#define DATA_PORT                 PORTA
#define DATA_DDR                  DDRA
#define DATA_PIN                  PINA

#define USART0_DDR                DDRE
#define USART0_XCK                PE2
#define USART0_TX                 PE1
#define USART0_RX                 PE0

#define USART1_DDR                DDRD
#define USART1_XCK                PD4
#define USART1_TX                 PD3
#define USART1_RX                 PD2

#define USART2_DDR                DDRH
#define USART2_XCK                PH2
#define USART2_TX                 PH1
#define USART2_RX                 PH0

#endif /* _MDUINO */

#endif /* __IOPINS_H__ */
