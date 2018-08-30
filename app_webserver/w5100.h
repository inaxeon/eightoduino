/*
 *   8OD - Arduino form factor i8086 based SBC
 *   Matthew Millman (tech.mattmillman.com)
 *
 *   Wiznet w5100 Driver
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

#ifndef __W5100_H__
#define __W5100_H__

/* S0_MR values */
#define MR_CLOSE            0x00      /* Unused socket */
#define MR_TCP              0x01      /* TCP */
#define MR_UDP              0x02      /* UDP */
#define MR_IPRAW            0x03      /* IP LAYER RAW SOCK */
#define MR_MACRAW           0x04      /* MAC LAYER RAW SOCK */
#define MR_PPPOE            0x05      /* PPPoE */
#define MR_ND               0x20      /* No Delayed Ack(TCP) flag */
#define MR_MULTI            0x80      /* support multicating */

/* Sx_SR values */
#define SOCK_CLOSED         0x00      /* Closed */
#define SOCK_INIT           0x13      /* Init state */
#define SOCK_LISTEN         0x14      /* Listen state */
#define SOCK_SYNSENT        0x15      /* Connection state */
#define SOCK_SYNRECV        0x16      /* Connection state */
#define SOCK_ESTABLISHED    0x17      /* Success to connect */
#define SOCK_FIN_WAIT       0x18      /* Closing state */
#define SOCK_CLOSING        0x1A      /* Closing state */
#define SOCK_TIME_WAIT      0x1B      /* Closing state */
#define SOCK_CLOSE_WAIT     0x1C      /* Closing state */
#define SOCK_LAST_ACK       0x1D      /* Closing state */
#define SOCK_UDP            0x22      /* UDP socket */
#define SOCK_IPRAW          0x32      /* IP raw mode socket */
#define SOCK_MACRAW         0x42      /* MAC raw mode socket */
#define SOCK_PPPOE          0x5F      /* PPPOE socket */
#define TX_BUF_MASK         0x07FF    /* Tx 2K Buffer Mask: */
#define RX_BUF_MASK         0x07FF    /* Rx 2K Buffer Mask: */
#define NET_MEMALLOC        0x05      /* Use 2K of Tx/Rx Buffer */

#define IR_CONFLICT         0x80
#define IR_UNREACH          0x40
#define IR_PPPOE_CLOSE      0x20

#define Sx_IR_DISCONNECTED  0x02
#define Sx_IR_CONNECTED     0x01
#define Sx_IR_DATA_RECVD    0x04
#define Sx_IR_TIMEOUT       0x08
#define Sx_IR_DATA_SENT     0x10

#define Sx_IR_MASK          0x1F

#define SADDR_OF(x, idx) (x + (0x100 * idx))

#define SET4(x, x1, x2, x3, x4) \
    do { \
        x[0] = x1; \
        x[1] = x2; \
        x[2] = x3; \
        x[3] = x4; \
    } while (0); 

#define SET6(x, x1, x2, x3, x4, x5, x6) \
    do { \
        x[0] = x1; \
        x[1] = x2; \
        x[2] = x3; \
        x[3] = x4; \
        x[4] = x5; \
        x[5] = x6; \
    } while (0); 

typedef struct
{
    uint8_t mac_addr[6];
    uint8_t ip_addr[4];
    uint8_t sub_mask[4];
    uint8_t gw_addr[4];
} w5100_config_t;

uint8_t w5100_read(unsigned int addr);
void w5100_write(unsigned int addr, uint8_t data);
void w5100_init(w5100_config_t *config);
void w5100_close(uint8_t sock);
void w5100_disconnect(uint8_t sock);
void w5100_mask_int(uint8_t intr);
void w5100_unmask_int(uint8_t intr);
void w5100_ack_ints(uint8_t flags);
void w5100_ack_sock_intflags(uint8_t sock, uint8_t flags);
uint8_t w5100_get_sock_state(uint8_t sock);
uint8_t w5100_sock_busy(uint8_t sock);
uint8_t w5100_get_ints(void);
uint8_t w5100_get_sock_intflags(uint8_t sock);
uint8_t w5100_socket(uint8_t sock, uint8_t eth_protocol, uint16_t tcp_port);
uint8_t w5100_listen(uint8_t sock);
uint16_t w5100_send(uint8_t sock, const uint8_t *buf, uint16_t buflen);
uint16_t w5100_recv(uint8_t sock, char *buf, uint16_t buflen);
uint16_t w5100_rx_buffer_length(uint8_t sock);

#endif /* __W5100_H__ */
