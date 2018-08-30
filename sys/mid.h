/*
 *   8OD - Arduino form factor i8086 based SBC
 *   Matthew Millman (tech.mattmillman.com)
 *
 *   Microwire Interface Device driver
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

/*   MIDCLK varies depending on the selected CPU clock speed
 *
 *   CPU 10MHz: MIDCLK = 15MHz
 *   CPU 8MHz : MIDCLK = 12MHz
 *   CPU 5MHz : MIDCLK = 7.5MHz
 *
 *   therefore resulting SPI clocks are:
 *
 *   MIDCLK  @ 15MHz     @ 12MHz     @ 7.5MHz
 *
 *   DIV4    = 3.75MHz   = 3MHz      = 1.86MHz
 *   DIV8    = 1.86MHz   = 1.5MHz    = 938KHz
 *   DIV16   = 938KHz    = 750KHz    = 469KHz
 *   DIV32   = 469KHz    = 375KHz    = 234KHz
 *   DIV64   = 234KHz    = 188KHz    = 117KHz
 *   DIV128  = 117KHz    = 94KHz     = 59KHz
 */


//#define M_CLK_DIV2      1        /* Pointless without all assembly implementation */
#define M_CLK_DIV4      2
#define M_CLK_DIV8      3
#define M_CLK_DIV16     4
#define M_CLK_DIV32     5
#define M_CLK_DIV64     6
#define M_CLK_DIV128    7

#define M_D_8BIT        0
#define M_D_16BIT       1

#define M_CLK_DNEGEDGE  0
#define M_CLK_DPOSEDGE  1

#define M_DEV_EEPROM    0
#define M_DEV_ADC       1
#define M_DEV_SPARE1    2
#define M_DEV_SPARE2    3

#define SMB             0x00

#define FMB             0x01
#define FMB_CS0SEL      0x02
#define FMB_CS1SEL      0x03
#define FMB_CS2SEL      0x04
#define FMB_CS3SEL      0x05
#define FMB_CS4SEL      0x06
#define FMB_CS5SEL      0x07
#define FMB_CS6SEL      0x08
#define FMB_CS7SEL      0x09

#define CSEL            0x0A
#define SKP             0x0B
#define MWM             0x0C

#define SKR             0x0D
#define SKR_INTEN       (1 << 7)
#define SKR_SOI         (1 << 6)
#define SKR_MS          (1 << 5)
#define SKR_DIV_MASK    0x07

#define ST              0x0E
#define ST_UWDONE       (1 << 7)

#define PD              0x0F

void mid_init(int speed);
void mid_cfg_dev(int dev, int enabled, int clkpol, int width);
void mid_xfer_x8_two(int dev, int tx1Len, uint8_t *tx1Buf, int tx2Len, uint8_t *tx2Buf, int rxLen, uint8_t *rxBuf);
void mid_xfer_x16(int dev, int txLen, uint16_t *txBuf, int rxLen, uint16_t *rxBuf); /* Untested */
void mid_xfer_to_uart(int dev, int txLen, uint8_t *txBuf, uint32_t rxLen, int rxUart);
#define mid_xfer_x8(dev, txLen, txBuf, rxLen, rxBuf) mid_xfer_x8_two(dev, txLen, txBuf, 0, NULL, rxLen, rxBuf)

