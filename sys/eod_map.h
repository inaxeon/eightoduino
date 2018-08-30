/*
 *   8OD - Arduino form factor i8086 based SBC
 *   Matthew Millman (tech.mattmillman.com)
 *
 *   Memory and I/O map
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

/* NOR Flash layout */

#define PGM_SEG             0xFC00
#define APP_SEG             0x8000
#define ROM_SEG             0x8000

/* Memory mapped addresses */

#define RAM_START           0x00000
#define RAM_END             0x7FFFF

#define ROM_START           0x80000
#define ROM_END             0xFFFFF

/* I/O mapped addresses */

#define STATUS              0x00    /* Interrupt status register IO Addr. Read only except bits 0 and 1 */
/* STATUS bits */
#define STATUS_TMF          (1 << 0)  /* Timer interrupt flag */
#define STATUS_PORTAF       (1 << 1)  /* PORTA Change flag */
#define STATUS_UARTAF       (1 << 2)  /* UART A Interrupt flag */
#define STATUS_UARTBF       (1 << 3)  /* UART B Interrupt flag */
#define STATUS_UARTCF       (1 << 4)  /* UART C Interrupt flag */
#define STATUS_UARTDF       (1 << 5)  /* UART D Interrupt flag */
#define STATUS_EXTINTA      (1 << 6)  /* External interrupt flag A (GFP2) */
#define STATUS_EXTINTB      (1 << 7)  /* External interrupt flag A (GFP3) */

#define STATUS_MASK         0xFF

#define CONFIG              0x02    /* Configuration register IO Addr. Write only. Must be shadowed */
/* CONFIG bits */
#define CONFIG_GINT         (1 << 0)  /* Global interrupt enable */
#define CONFIG_TMINT        (1 << 1)  /* Timer interrupt enable */
#define CONFIG_PORTAINT     (1 << 2)  /* PORTA change interrupt enable */
#define CONFIG_UAINT        (1 << 3)  /* UARTA interrupt enable */
#define CONFIG_UBINT        (1 << 4)  /* UARTB interrupt enable */
#define CONFIG_UCINT        (1 << 5)  /* UARTC interrupt enable */
#define CONFIG_UDINT        (1 << 6)  /* UARTD interrupt enable */
#define CONFIG_EXTINTA      (1 << 7)  /* External interrupt A (GFP2) enable */
#define CONFIG_EXTINTB      (1 << 8)  /* External interrupt B (GFP3) enable */
#define CONFIG_EEWP         (1 << 9)  /* Flash write protect bit */
#define CONFIG_UAEN         (1 << 10) /* Route UARTA to PORTA pins */
#define CONFIG_UBEN         (1 << 11) /* Route UARTB to PORTB pins */
#define CONFIG_UCEN         (1 << 12) /* Route UARTC to PORTB pins */
#define CONFIG_UDEN         (1 << 13) /* Route UARTD to PORTA pins */
#define CONFIG_TMRUN        (1 << 14) /* Timer run */
#define CONFIG_RST          (1 << 15) /* Suicide bit. Asserts MRST causing system hard reset */

#define PORTA               0x04    /* PORTA IO Addr. Readable and writable */
#define PORTB               0x06    /* PORTB IO Addr. Readable and writable */
#ifndef LBUS_CPLD
#define PORTC               0x08    /* PORTC IO Addr. Readable and writable */
#define PORTD               0x0A    /* PORTB IO Addr. Write only. Must be shadowed */
#endif /* !LBUS_CPLD */

#define TRISA               0x0C    /* TRISA IO Addr. Write only. Must be shadowed */
#define TRISB               0x0E    /* TRISB IO Addr. Write only. Must be shadowed */
#ifndef LBUS_CPLD
#define TRISC               0x10    /* TRISC IO Addr. Write only. Must be shadowed */
#endif /* !LBUS_CPLD */
#define TIMER               0x18    /* Timer register. Sets start count for timer */

#define UARTA_BASE          0x20    /* UART A IO Addr. Only supports 8 bit accesses */
#define UARTB_BASE          0x28    /* UART B IO Addr. Only supports 8 bit accesses */
#define UARTC_BASE          0x30    /* UART C IO Addr. Only supports 8 bit accesses */
#define UARTD_BASE          0x38    /* UART D IO Addr. Only supports 8 bit accesses */

#define MID_BASE            0x40    /* Microwire Interface Device */

#define I2C_BASE            0x50    /* I2C Master (PCF8584) */

#define EXT_LOWIO_BASE      0x80    /* Expansion bus header range 1 (IO 0x80 - 0xFF) */
#define EXT_HIGHIO_BASE     0x8000  /* Expansion bus header range 2 (IO 0x8000 - 0xFFFF) */

/* Shadow registers */
#define NUM_CPLD_SHADOWS    16      /* Number of 16 bit shorts to store CPLD shadow registers */
