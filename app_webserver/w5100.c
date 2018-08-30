/*
 *   8OD - Arduino form factor i8086 based SBC
 *   Matthew Millman (tech.mattmillman.com)
 *
 *   Wiznet W5100 Driver
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
 *   along with this software.  If not, see <http:/*www.gnu.org/licenses/>.
 */

#include <stdint.h>
#include <stdio.h>
#include <stddef.h>

#include "eod_io.h"
#include "util.h"
#include "mid.h"
#include "w5100.h"

//#define debug_printf(...)
#define debug_printf(...) printf(__VA_ARGS__)
#define error_printf(...) printf(__VA_ARGS__)

/* Wiznet w5100 Op Code */
#define WIZNET_WRITE_OPCODE 0xF0
#define WIZNET_READ_OPCODE 0x0F

/* Wiznet w5100 Register Addresses */
#define MR               0x0000   /* Mode Register */
#define GAR              0x0001   /* Gateway Address: 0x0001 to 0x0004 */
#define SUBR             0x0005   /* Subnet mask Address: 0x0005 to 0x0008 */
#define SAR              0x0009   /* Source Hardware Address (MAC): 0x0009 to 0x000E */
#define SIPR             0x000F   /* Source IP Address: 0x000F to 0x0012 */
#define IR               0x0015   /* Interrupt register */
#define IMR              0x0016   /* Interrupt mask register */
#define RMSR             0x001A   /* RX Memory Size Register */
#define TMSR             0x001B   /* TX Memory Size Register */

#define Sx_MR            0x0400   /* Socket: Mode Register Address */
#define Sx_CR            0x0401   /* Socket: Command Register Address */
#define Sx_IR            0x0402   /* Socket 0: Interrupt Register Address */
#define Sx_SR            0x0403   /* Socket: Status Register Address */
#define Sx_PORT          0x0404   /* Socket: Source Port: 0x0404 to 0x0405 */
#define Sx_TX_FSR        0x0420   /* Socket: Tx Free Size Register: 0x0420 to 0x0421 */
#define Sx_TX_RD         0x0422   /* Socket: Tx Read Pointer Register: 0x0422 to 0x0423 */
#define Sx_TX_WR         0x0424   /* Socket: Tx Write Pointer Register: 0x0424 to 0x0425 */
#define Sx_RX_RSR        0x0426   /* Socket: Rx Received Size Pointer Register: 0x0425 to 0x0427 */
#define Sx_RX_RD         0x0428   /* Socket: Rx Read Pointer: 0x0428 to 0x0429 */
#define TXBUFADDR        0x4000   /* w5100 Send Buffer Base Address */
#define RXBUFADDR        0x6000   /* w5100 Read Buffer Base Address */

#define BADDR_OF(x, idx) (x + (0x800 * idx))

/* Sx_CR values */
#define CR_OPEN          0x01      /* Initialize or open socket */
#define CR_LISTEN        0x02      /* Wait connection request in tcp mode(Server mode) */
#define CR_CONNECT       0x04      /* Send connection request in tcp mode(Client mode) */
#define CR_DISCON        0x08      /* Send closing reqeuset in tcp mode */
#define CR_CLOSE         0x10      /* Close socket */
#define CR_SEND          0x20      /* Update Tx memory pointer and send data */
#define CR_SEND_MAC      0x21      /* Send data with MAC address, so without ARP process */
#define CR_SEND_KEEP     0x22      /* Send keep alive message */
#define CR_RECV          0x40      /* Update Rx memory buffer pointer and receive data */

uint8_t _g_imr;

void w5100_write(unsigned int addr, uint8_t data)
{
    uint8_t toSend[4];

    cpld_write(PORTA, (1 << 10), 0); /* ETH CS Low */

    toSend[0] = WIZNET_WRITE_OPCODE;
    toSend[1] = (addr & 0xFF00) >> 8;
    toSend[2] = addr & 0x00FF;
    toSend[3] = data;

    mid_xfer_x8(M_DEV_SPARE1, 4, &toSend, 0, NULL);
    
    cpld_write(PORTA, (1 << 10), (1 << 10)); /* ETH CS High */
}

uint8_t w5100_read(unsigned int addr)
{
    uint8_t ret;
    uint8_t toSend[3];

    cpld_write(PORTA, (1 << 10), 0); /* ETH CS Low */

    toSend[0] = WIZNET_READ_OPCODE;
    toSend[1] = (addr & 0xFF00) >> 8;
    toSend[2] = addr & 0x00FF;

    mid_xfer_x8(M_DEV_SPARE1, 3, &toSend, 1, &ret);

    cpld_write(PORTA, (1 << 10), (1 << 10)); /* ETH CS High */

    return ret;
}

void w5100_init(w5100_config_t *config)
{
    /* Ethernet Setup */

    /* Setting the Wiznet w5100 Mode Register: 0x0000 */
    w5100_write(MR, 0x80);

    delay_ncycles(554); /* 1ms */

    debug_printf("Reading MR: %d\r\n\r\n", w5100_read(MR));

    /* Setting the Wiznet w5100 Gateway Address (GAR): 0x0001 to 0x0004 */

    debug_printf("Setting Gateway Address %d.%d.%d.%d\r\n",
        config->gw_addr[0],
        config->gw_addr[1],
        config->gw_addr[2],
        config->gw_addr[3]);

    w5100_write(GAR + 0, config->gw_addr[0]);
    w5100_write(GAR + 1, config->gw_addr[1]);
    w5100_write(GAR + 2, config->gw_addr[2]);
    w5100_write(GAR + 3, config->gw_addr[3]);

    delay_ncycles(554); /* 1ms */

    debug_printf("Reading GAR: %d.%d.%d.%d\r\n\r\n",
        w5100_read(GAR + 0),
        w5100_read(GAR + 1),
        w5100_read(GAR + 2),
        w5100_read(GAR + 3));

    /* Setting the Wiznet w5100 Source Address Register (SAR): 0x0009 to 0x000E */
    debug_printf("Setting Source Address %.2x:%.2x:%.2x:%.2x:%.2x:%.2x\r\n",
        config->mac_addr[0],
        config->mac_addr[1],
        config->mac_addr[2],
        config->mac_addr[3],
        config->mac_addr[4],
        config->mac_addr[5]);

    w5100_write(SAR + 0, config->mac_addr[0]);
    w5100_write(SAR + 1, config->mac_addr[1]);
    w5100_write(SAR + 2, config->mac_addr[2]);
    w5100_write(SAR + 3, config->mac_addr[3]);
    w5100_write(SAR + 4, config->mac_addr[4]);
    w5100_write(SAR + 5, config->mac_addr[5]);
    
    delay_ncycles(554); /* 1ms */
    
    debug_printf("Reading SAR: %.2x:%.2x:%.2x:%.2x:%.2x:%.2x\r\n\r\n",
        w5100_read(SAR + 0),
        w5100_read(SAR + 1),
        w5100_read(SAR + 2),
        w5100_read(SAR + 3),
        w5100_read(SAR + 4),
        w5100_read(SAR + 5));

    /* Setting the Wiznet w5100 Sub Mask Address (SUBR): 0x0005 to 0x0008 */
    
    debug_printf("Setting Sub Mask Address %d.%d.%d.%d\r\n",
        config->sub_mask[0],
        config->sub_mask[1],
        config->sub_mask[2],
        config->sub_mask[3]);

    w5100_write(SUBR + 0, config->sub_mask[0]);
    w5100_write(SUBR + 1, config->sub_mask[1]);
    w5100_write(SUBR + 2, config->sub_mask[2]);
    w5100_write(SUBR + 3, config->sub_mask[3]);

    delay_ncycles(554); /* 1ms */
    
    debug_printf("Reading SUBR: %d.%d.%d.%d\r\n\r\n",
        w5100_read(SUBR + 0),
        w5100_read(SUBR + 1),
        w5100_read(SUBR + 2),
        w5100_read(SUBR + 3));
    /* Setting the Wiznet w5100 IP Address (SIPR): 0x000F to 0x0012 */

    debug_printf("Setting IP Address %d.%d.%d.%d\r\n",
        config->ip_addr[0],
        config->ip_addr[1],
        config->ip_addr[2],
        config->ip_addr[3]);

    w5100_write(SIPR + 0, config->ip_addr[0]);
    w5100_write(SIPR + 1, config->ip_addr[1]);
    w5100_write(SIPR + 2, config->ip_addr[2]);
    w5100_write(SIPR + 3, config->ip_addr[3]);
    
    delay_ncycles(554); /* 1ms */

    debug_printf("Reading SIPR: %d.%d.%d.%d\r\n\r\n",
        w5100_read(SIPR + 0),
        w5100_read(SIPR + 1),
        w5100_read(SIPR + 2),
        w5100_read(SIPR + 3));

    /* Setting the Wiznet w5100 RX and TX Memory Size, we use 2KB for Rx/Tx 4 channels */
    debug_printf("Setting Wiznet RMSR and TMSR\r\n\r\n");

    w5100_write(RMSR, 0x55);
    w5100_write(TMSR, 0x55);

    debug_printf("Done Wiznet w5100 Initialized!\r\n");

    _g_imr = 0x00;
}

void w5100_close(uint8_t sock)
{
    /* Send close Command */
    w5100_write(SADDR_OF(Sx_CR, sock), CR_CLOSE);

    while (w5100_read(SADDR_OF(Sx_CR, sock)));
}

void w5100_disconnect(uint8_t sock)
{
    /* Send disconnect command */
    w5100_write(SADDR_OF(Sx_CR, sock), CR_DISCON);
}

uint8_t w5100_socket(uint8_t sock, uint8_t eth_protocol, uint16_t tcp_port)
{
    uint8_t retval = 0;

    /* Make sure we close the socket first */
    if (w5100_read(SADDR_OF(Sx_SR, sock)) == SOCK_CLOSED)
        w5100_close(sock);

    /* Assigned Socket Mode Register */
    w5100_write(SADDR_OF(Sx_MR, sock), eth_protocol);

    /* Now open the Socket */
    w5100_write(SADDR_OF(Sx_PORT, sock),    ((tcp_port & 0xFF00) >> 8));
    w5100_write(SADDR_OF(Sx_PORT, sock) + 1, (tcp_port & 0x00FF));

    w5100_write(SADDR_OF(Sx_CR, sock), CR_OPEN);

    /* Wait for open */
    while (w5100_read(SADDR_OF(Sx_CR, sock)));

    /* Check for init status */
    if (w5100_read(SADDR_OF(Sx_SR, sock)) == SOCK_INIT)
      retval = 1;
    else
      w5100_close(sock);

    return retval;
}

uint8_t w5100_listen(uint8_t sock)
{
    uint8_t retval = 0;
    
    if (w5100_read(SADDR_OF(Sx_SR, sock)) == SOCK_INIT)
    {
        /* Send the LISTEN Command */
        w5100_write(SADDR_OF(Sx_CR, sock), CR_LISTEN);

        /* Wait for Listening Process */
        while (w5100_read(SADDR_OF(Sx_CR, sock)));

        /* Check for Listen Status */
        if (w5100_read(SADDR_OF(Sx_SR, sock)) == SOCK_LISTEN)
            retval = 1;
        else
            w5100_close(sock);
    }

    return retval;
}

uint16_t w5100_send(uint8_t sock, const uint8_t *buf, uint16_t buflen)
{
    uint16_t ptr;
    uint16_t offaddr;
    uint16_t txsize;
    uint16_t timeout;   

    if (buflen == 0)
        return 0;

    debug_printf("Send Size: %d\r\n",buflen);

    /* Make sure the TX Free Size Register is available */
    txsize = w5100_read(SADDR_OF(Sx_TX_FSR, sock));
    txsize = (((txsize & 0x00FF) << 8 ) + w5100_read(SADDR_OF(Sx_TX_FSR, sock) + 1));

    debug_printf("TX Free Size: %d\r\n",txsize);

    timeout = 0;
    while (txsize < buflen)
    {
        delay_ncycles(554); /* 1ms */
        txsize = w5100_read(SADDR_OF(Sx_TX_FSR, sock));
        txsize = (((txsize & 0x00FF) << 8 ) + w5100_read(SADDR_OF(Sx_TX_FSR, sock) + 1));
        
        /* Timeout for approx 1000 ms */
        if (timeout++ > 1000)
        {
            debug_printf("TX Free Size Error!\r\n");
            /* Disconnect */
            w5100_disconnect(sock);
            return 0;
        }
    }    

    /* Read the Tx Write Pointer */
    ptr = w5100_read(SADDR_OF(Sx_TX_WR, sock));
    offaddr = (((ptr & 0x00FF) << 8 ) + w5100_read(SADDR_OF(Sx_TX_WR, sock) + 1));

    debug_printf("TX Buffer: %x\r\n", offaddr);

    while (buflen)
    {
        buflen--;
        /* Calculate the real w5100 physical Tx Buffer Address */
        /* Copy the application data to the w5100 Tx Buffer */
        w5100_write(BADDR_OF(TXBUFADDR, sock) + (offaddr & TX_BUF_MASK), *buf);
        offaddr++;
        buf++;
    }

    /* Increase the S0_TX_WR value, so it point to the next transmit */
    w5100_write(SADDR_OF(Sx_TX_WR, sock),     (offaddr & 0xFF00) >> 8);
    w5100_write(SADDR_OF(Sx_TX_WR, sock) + 1, (offaddr & 0x00FF));    

    /* Now Send the SEND command */
    w5100_write(SADDR_OF(Sx_CR, sock), CR_SEND);

    return 1;
}

uint16_t w5100_recv(uint8_t sock, char *buf, uint16_t rxlen)
{
    uint16_t ptr;
    uint16_t offaddr;
    
    if (rxlen == 0)
        return 0;

    /* Read the Rx Read Pointer */
    ptr = w5100_read(SADDR_OF(Sx_RX_RD, sock));
    offaddr = (((ptr & 0x00FF) << 8 ) + w5100_read(SADDR_OF(Sx_RX_RD, sock) + 1));

    debug_printf("RX Buffer: %x\r\n", offaddr);

    while (rxlen > 0)
    {
        rxlen--;
        *buf = w5100_read(BADDR_OF(RXBUFADDR, sock) + (offaddr & RX_BUF_MASK));
        offaddr++;
        buf++;
    }

    /* Increase the S0_RX_RD value, so it point to the next receive */
    w5100_write(SADDR_OF(Sx_RX_RD, sock),     (offaddr & 0xFF00) >> 8);
    w5100_write(SADDR_OF(Sx_RX_RD, sock) + 1, (offaddr & 0x00FF));    

    /* Now Send the RECV command */
    w5100_write(SADDR_OF(Sx_CR, sock), CR_RECV);

    return 1;
}

uint16_t w5100_rx_buffer_length(uint8_t sock)
{
    return (((w5100_read(SADDR_OF(Sx_RX_RSR, sock)) & 0x00FF) << 8) + w5100_read(SADDR_OF(Sx_RX_RSR, sock) + 1));
}

void w5100_unmask_int(uint8_t intr)
{
    _g_imr |= (1 << intr);
    w5100_write(IMR, _g_imr);
}

void w5100_mask_int(uint8_t intr)
{
    _g_imr &= ~(1 << intr);
    w5100_write(IMR, _g_imr);
}

uint8_t w5100_get_ints(void)
{
    return w5100_read(IR);
}

void w5100_ack_ints(uint8_t flags)
{
    w5100_write(IR, flags);
}

uint8_t w5100_get_sock_intflags(uint8_t sock)
{
    return w5100_read(SADDR_OF(Sx_IR, sock));
}

void w5100_ack_sock_intflags(uint8_t sock, uint8_t flags)
{
    w5100_write(SADDR_OF(Sx_IR, sock), flags);
}

uint8_t w5100_get_sock_state(uint8_t sock)
{
    return w5100_read(SADDR_OF(Sx_SR, sock));
}

uint8_t w5100_sock_busy(uint8_t sock)
{
    return (w5100_read(SADDR_OF(Sx_CR, sock)) != 0);
}
