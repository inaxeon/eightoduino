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

#include <stdint.h>
#include "eod_map.h"
#include "eod_io.h"
#include "mid.h"
#include "uart.h"

void mid_init(int speed)
{
    /* Sets maser mode, disables interrupt, and clock divider */
    outp(MID_BASE + SKR, speed & SKR_DIV_MASK);
}

void mid_cfg_dev(int dev, int enabled, int clkpol, int width)
{
    uint8_t currentPd;

    /* Impossible on this platform */
    if (dev > M_DEV_SPARE2)
        return;

    currentPd = inp(MID_BASE + PD);

    if (enabled)
    {
        uint8_t currentSkp = inp(MID_BASE + SKP);
        uint8_t currentMwm = inp(MID_BASE + MWM);

        /* Clear SKP7 and MWM7, making 8-bit negative edge the default for
         * all accesses done via the FMD/SMB registers
         */
        currentSkp &= ~(1 << 7);
        currentMwm &= ~(1 << 7);

        /* Make the associated CS an output */
        outp(MID_BASE + PD, currentPd & ~(1 << dev));

        if (clkpol == M_CLK_DNEGEDGE)
            outp(MID_BASE + SKP, currentSkp & ~(1 << dev));
        else if (clkpol == M_CLK_DPOSEDGE)
            outp(MID_BASE + SKP, currentSkp | (1 << dev));

        if (width == M_D_8BIT)
            outp(MID_BASE + MWM, currentMwm & ~(1 << dev));
        else if (width == M_D_16BIT)
            outp(MID_BASE + MWM, currentMwm | (1 << dev));
    }
    else
    {
        /* Make the associated CS an input */
        outp(MID_BASE + PD, currentPd | (1 << dev));
    }
}

void mid_xfer_x8_two(int dev, int tx1Len, uint8_t *tx1Buf, int tx2Len,
	uint8_t *tx2Buf, int rxLen, uint8_t *rxBuf)
{
    int pos = 0;

    /* Select requested device */
    outp(MID_BASE + CSEL, ~(1 << dev));

    if (tx1Len > 0)
    {
        while (pos < tx1Len)
        {
            outp(MID_BASE + FMB, tx1Buf[pos++]);

            /* By observarion on a logic analyser, the MID, using an SCK of 3.75MHz
             * manages to complete the transaction in about one quarter of the time
             * it takes a CPU running this code at 10MHz to get back to the beginning
             * of this while loop, therefore, there's no need to waste time polling
             * UWDONE.
             */
        }
    
        if (tx2Len > 0)
        {
            /* Transmit a second buffer if needed */
            pos = 0;
            while (pos < tx2Len)
                outp(MID_BASE + FMB, tx2Buf[pos++]);
        }
    }

    if (rxLen > 0)
    {
        pos = 0;

        /* Kick off the first trasaction */
        outp(MID_BASE + FMB, 0x00);

        rxLen--;

        /* Only here do we need to poll UWDONE,
         * because that first read is going to happen fast.
         */
        while ((inp(MID_BASE + ST) & ST_UWDONE) == 0);

        do
        {
            register uint8_t read = inp(MID_BASE + FMB);
            if (rxLen > pos)
                outp(MID_BASE + FMB, 0x00); /* Kick off another */
            rxBuf[pos++] = read;

           /* As per TX, there is even less need to poll UWDONE here */
        } while (pos <= rxLen);
    }

    /* De-select everything */
    outp(MID_BASE + CSEL, 0xFF);
}

/* Untested */
void mid_xfer_x16(int dev, int txLen, uint16_t *txBuf, int rxLen, uint16_t *rxBuf)
{
    int pos = 0;

    /* Select requested device */
    outp(MID_BASE + CSEL, ~(1 << dev));

    while (pos < txLen)
    {
        outp(MID_BASE + SMB, (uint8_t)(txBuf[pos] >> 8));
        outp(MID_BASE + FMB_CS0SEL + dev, (uint8_t)(txBuf[pos++] & 0xFF));

        /* By observarion on a logic analyser, the MID, using an SCK of 3.75MHz
         * manages to complete the transaction in about one quarter of the time
         * it takes a CPU running this code at 10MHz to get back to the beginning
         * of this while loop, therefore, there's no need to waste time polling
         * UWDONE.
         */
    }

    if (rxLen > 0)
    {
        pos = 0;

        /* Kick off the first trasaction */
        outp(MID_BASE + FMB_CS0SEL + dev, 0x00);

        rxLen--;

        /* Only here do we need to poll UWDONE,
         * because that first read is going to happen fast.
         */
        while ((inp(MID_BASE + ST) & ST_UWDONE) == 0);

        do
        {
            register uint16_t read = inp(MID_BASE + SMB);
            read <<= 8;
            read |= inp(MID_BASE + FMB);
            if (rxLen > pos)
                outp(MID_BASE + FMB_CS0SEL + dev, 0x00); /* Kick off another */
            rxBuf[pos++] = read;

           /* As per TX, there is even less need to poll UWDONE here */
        } while (pos <= rxLen);
    }

    /* De-select everything */
    outp(MID_BASE + CSEL, 0xFF);
}

/* Special IO function allowing large amounts to be streamed directly to the UART
 * without having to go via RAM.
 */
void mid_xfer_to_uart(int dev, int txLen, uint8_t *txBuf, uint32_t rxLen, int uart_index)
{
    uint32_t pos = 0;

    if (!rxLen)
        return;

    outp(MID_BASE + CSEL, ~(1 << dev));

    while (pos < txLen)
        outp(MID_BASE + FMB, txBuf[pos++]);

    pos = 0;

    outp(MID_BASE + FMB, 0x00);
    rxLen--;

    while ((inp(MID_BASE + ST) & ST_UWDONE) == 0);

    do
    {
        register uint8_t read = inp(MID_BASE + FMB);
        if (rxLen > pos)
            outp(MID_BASE + FMB, 0x00); 

        uart_putc(uart_index, read);
        pos++;

    } while (pos <= rxLen);

    outp(MID_BASE + CSEL, 0xFF);
}
