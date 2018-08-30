/*
 *   8OD - Arduino form factor i8086 based SBC
 *   Matthew Millman (tech.mattmillman.com)
 *
 *   Wiznet W5100 web server
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

#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

#include "util.h"
#include "mid.h"
#include "w5100.h"
#include "webserver.h"
#include "eod_io.h"

#define STATE_DEBUG 
#define ACTIVITY_DEBUG

#ifdef ACTIVITY_DEBUG
#define debug_printf(...) printf(__VA_ARGS__)
#else
#define debug_printf(...)
#endif

#define MAX_BUF                 2048
#define MAX_SOCKS               4
#define MAX_SOCK_TIMEOUT_INTRS  300     /* Timeout after 30s */
#define TIMER_RELOAD            0xC000  /* Approx 100ms */

/* Web specific server socket states */
#define WS_DISCONNECTED        0
#define WS_LISTENING           1
#define WS_CONNECTED           2
#define WS_DISCONNECTING       3

#define RQ_NONE                0
#define RQ_OPENED              1
#define RQ_HEADER_RECEIVED     2
#define RQ_REQUEST_RECEIVED    3
#define RQ_REQUEST_PROCESSED   4

/* Flags which come from the interrupt handler */
#define FLG_W5100_INTR         0x01
#define FLG_SOCK_TIMEOUT       0x02
#define FLG_IP_CONFLICT        0x04
#define FLG_TIMER_LAPSED       0x08


typedef struct
{
    uint8_t state;
    uint8_t request_state;
    uint8_t timedout;
    uint16_t request_timeout;
    uint8_t request_buffer[MAX_BUF];
    uint8_t *header_end;
    uint16_t request_remaining;
    uint16_t bytes_received;
} ws_instance_t;

ws_instance_t _g_ws_instances[MAX_SOCKS];
ws_t _g_ws;

uint8_t _g_intflags;

static int do_request(uint8_t sock);
static void sock_restart(uint8_t sock);
static void sock_connected(uint8_t sock);
static void sock_disconnect(uint8_t sock);
static void sock_data_received(uint8_t sock);

inline void process_timeouts(void);
inline void process_incoming_connection_intrs(void);
inline void process_socks(void);

#ifdef STATE_DEBUG
#define MAX_DEBUG_TIMEOUT_INTRS 100     /* 10s */
uint16_t _g_debugTimeoutInts;
uint16_t _g_debugSequence;
inline void process_state_debug(void);
#endif

void interrupt_handler(void)
{
    /* Read status register (contains interrupt flags) */
    uint16_t status = cpld_read(STATUS);

    /* W5100's interrupt */
    if (status & STATUS_EXTINTA)
    {
        _g_intflags |= FLG_W5100_INTR;

        /* Mask it, because we can't make it go away right now */
        cpld_write(CONFIG, CONFIG_EXTINTA, 0);
    }

    /* Timer overflow interrupt */
    if (status & STATUS_TMF)
    {
        int i;
        for (i = 0; i < MAX_SOCKS; i++)
        {
            if (_g_ws_instances[i].state == WS_CONNECTED)
                _g_ws_instances[i].request_timeout++;

            if (_g_ws_instances[i].request_timeout >= MAX_SOCK_TIMEOUT_INTRS)
            {
                _g_ws_instances[i].request_timeout = 0;
                _g_ws_instances[i].timedout = 1;

                _g_intflags |= FLG_SOCK_TIMEOUT;
            }
        }

#ifdef STATE_DEBUG
        _g_debugTimeoutInts++;
        if (_g_debugTimeoutInts >= MAX_DEBUG_TIMEOUT_INTRS)
        {
            _g_intflags |= FLG_TIMER_LAPSED;
            _g_debugTimeoutInts = 0;
        }
#endif

        /* Stop timer */
        cpld_write(CONFIG, CONFIG_TMRUN, 0);
        /* Reload timer */
        cpld_direct_write(TIMER, TIMER_RELOAD);
        /* Clear the timer flag */
        cpld_direct_write(STATUS, ~STATUS_TMF);
        /* Start timer */
        cpld_write(CONFIG, CONFIG_TMRUN, CONFIG_TMRUN);
    }
}

/* Web server idle process */
void ws_process(void)
{
    process_timeouts();
    process_incoming_connection_intrs();
    process_socks();

#ifdef STATE_DEBUG
    process_state_debug();
#endif
}

inline void process_timeouts(void)
{
    int sock;

    if (_g_intflags & FLG_SOCK_TIMEOUT)
    {
        int sock;
        for (sock = 0; sock < MAX_SOCKS; sock++)
        {
            if (_g_ws_instances[sock].timedout)
            {
                debug_printf("sock_process(%u): Timeout kill\r\n", sock);
                w5100_disconnect(sock);
            }
        }
        
        _g_intflags &= ~FLG_SOCK_TIMEOUT;
    }
}

inline void process_incoming_connection_intrs(void)
{
    int sock;

    if (_g_intflags & FLG_W5100_INTR)
    {
        uint8_t intFlags = w5100_get_ints();

        if (intFlags & IR_UNREACH)
            w5100_ack_ints(IR_UNREACH);

        if (intFlags & IR_CONFLICT)
        {
            printf("IP Address conflict detected\r\n");
            w5100_ack_ints(IR_CONFLICT);
        }

        if (intFlags & IR_PPPOE_CLOSE)
            w5100_ack_ints(IR_PPPOE_CLOSE);

        for (sock = 0; sock < MAX_SOCKS; sock++)
        {
            if (intFlags & (1 << sock))
            {
                uint8_t flags = w5100_get_sock_intflags(sock);
                
                if (flags & Sx_IR_CONNECTED)
                {
                    w5100_ack_sock_intflags(sock, Sx_IR_CONNECTED);
                    sock_connected(sock);
                }

                if (flags & Sx_IR_TIMEOUT)
                {
                    w5100_ack_sock_intflags(sock, Sx_IR_TIMEOUT);
                    w5100_close(sock);
                    sock_restart(sock);
                }

                w5100_ack_sock_intflags(sock, Sx_IR_DATA_RECVD | Sx_IR_DISCONNECTED | Sx_IR_DATA_SENT);
            }
        }

        _g_intflags &= ~FLG_W5100_INTR;

        /* Unmask and clear */
        cpld_write(CONFIG, CONFIG_EXTINTA, CONFIG_EXTINTA);
        cpld_direct_write(STATUS, ~STATUS_EXTINTA);
    }
}

#ifdef STATE_DEBUG
inline void process_state_debug(void)
{
    int sock;
    for (sock = 0; sock < MAX_SOCKS; sock++)
    {
        if (_g_ws_instances[sock].state == WS_LISTENING && w5100_get_sock_state(sock) == SOCK_CLOSED)
            sock_restart(sock);
    }

    if (_g_intflags & FLG_TIMER_LAPSED)
    {
        printf("\r\nState dump: %u\r\n\r\n", _g_debugSequence++);

        printf("WS states .......: 0x%u 0x%u 0x%u 0x%u\r\n",
            _g_ws_instances[0].state,
            _g_ws_instances[1].state,
            _g_ws_instances[2].state,
            _g_ws_instances[3].state);

        printf("SOCK states .....: 0x%x 0x%x 0x%x 0x%x\r\n",
            w5100_get_sock_state(0),
            w5100_get_sock_state(1),
            w5100_get_sock_state(2),
            w5100_get_sock_state(3));

        printf("SOCK int flags ..: 0x%x 0x%x 0x%x 0x%x\r\n", 
            w5100_get_sock_intflags(0),
            w5100_get_sock_intflags(1),
            w5100_get_sock_intflags(2),
            w5100_get_sock_intflags(3));

        printf("INT flags .......: 0x%x\r\n",
            w5100_get_ints());

        printf("STATUS register .: 0x%x\r\n",
            cpld_read(STATUS) & STATUS_MASK);

        printf("CONFIG register .: 0x%x\r\n",
            cpld_shadow_read(CONFIG));

        _g_intflags &= ~FLG_TIMER_LAPSED;
    }
}
#endif

inline void process_socks(void)
{
    int sock;

    for (sock = 0; sock < MAX_SOCKS; sock++)
    {
        if (_g_ws_instances[sock].state == WS_CONNECTED || _g_ws_instances[sock].state == WS_DISCONNECTING)
        {
            switch (w5100_get_sock_state(sock))
            {
            case SOCK_CLOSED:
                {
                    debug_printf("sock_process(%u): Sock disconnected\r\n", sock);
                    sock_restart(sock);
                }
                break;
            case SOCK_ESTABLISHED:
                {
                    switch (_g_ws_instances[sock].request_state)
                    {
                    case RQ_OPENED:
                    case RQ_HEADER_RECEIVED:
                        {
                            sock_data_received(sock);
                        }
                        break;
                    case RQ_REQUEST_RECEIVED:
                        {
                            if (!do_request(sock))
                                sock_disconnect(sock);
                        }
                        break;
                    case RQ_REQUEST_PROCESSED:
                        {
                            if (!w5100_sock_busy(sock))
                            {
                                debug_printf("sock_process(%u): Data sent\r\n", sock);
                                if (_g_ws.http_response_sent)
                                    _g_ws.http_response_sent(sock);
                            }
                        }
                        break;
                    }
                }
                break;
            case SOCK_FIN_WAIT:
            case SOCK_CLOSING:
            case SOCK_TIME_WAIT:
            case SOCK_CLOSE_WAIT:
            case SOCK_LAST_ACK:
                {
                    if (_g_ws_instances[sock].state == WS_DISCONNECTING && w5100_sock_busy(sock))
                    {
                        /* Unlikely */
                        debug_printf("sock_process(%u): Not ready to close yet\r\n", sock);
                    }
                    else
                    {
                        debug_printf("sock_process(%u): Close\r\n", sock);
                        w5100_close(sock);
                    }
                }
                break;
            }
        }
        else if (_g_ws_instances[sock].state == WS_DISCONNECTED)
        {
            sock_restart(sock);
        }
    }
}

void ws_init(ws_t *ws)
{
    int sock;

    _g_intflags = 0;

#ifdef STATE_DEBUG
    _g_debugTimeoutInts = 0;
    _g_debugSequence = 0;
#endif

    memcpy(&_g_ws, ws, sizeof(ws_t));

    for (sock = 0; sock < MAX_SOCKS; sock++)
        _g_ws_instances[sock].state = WS_DISCONNECTED;

    /* Load timer */
    cpld_direct_write(TIMER, TIMER_RELOAD);
    /* Start timer */
    cpld_write(CONFIG, CONFIG_TMRUN, CONFIG_TMRUN);
}

void ws_disconnect(uint8_t instance)
{
    w5100_disconnect(instance);
}

uint16_t ws_send(uint8_t instance, const uint8_t *buf, uint16_t buflen)
{
    int written = 0;

    while (buflen > 0)
    {
        int thisWrite = buflen > 2048 ? 2048 : buflen;
        w5100_send(instance, buf + written, thisWrite);
        buflen -= thisWrite;
        written += thisWrite;
    }

    return written;
}

static int do_request(uint8_t sock)
{
    int i;
    char *s;
    char *getstr;
    char *poststr;
    char *request;
    char filename[256];

    *_g_ws_instances[sock].header_end = '\0';

    //debug_printf("do_request(%u): Content:\r\n%s\r\n", instance, req);

    getstr = strstr(_g_ws_instances[sock].request_buffer, "GET /");
    poststr = strstr(_g_ws_instances[sock].request_buffer, "POST /");
    
    if (!getstr && !poststr)
    {
        debug_printf("do_request(%u): No valid HTTP verb found\r\n", sock);
        return 0;
    }

    s = (getstr != NULL) ? getstr + 4 : poststr + 5;
    for (i = 0; i < (sizeof(filename) - 1) && !isspace(*s) && *s; i++, s++)
        filename[i] = *s;
    filename[i] = '\0';

    debug_printf("do_request(%u): Requested filename: %s\r\n", sock, filename);

    if (getstr)
    {
        if (_g_ws.http_get)
            _g_ws.http_get(sock, filename, _g_ws_instances[sock].request_buffer);
        else
            return 0;
    }
    else
    {
        if (_g_ws.http_post)
            _g_ws.http_post(sock, filename, _g_ws_instances[sock].request_buffer, _g_ws_instances[sock].header_end + 4 /* \r\n\r\n */);
        else
            return 0;
    }

    _g_ws_instances[sock].request_state = RQ_REQUEST_PROCESSED;

    return 1;
}

static void sock_connected(uint8_t sock)
{
    debug_printf("sock_process(%u): Sock connected\r\n", sock);

    _g_ws_instances[sock].state = WS_CONNECTED;
    _g_ws_instances[sock].request_state = RQ_OPENED;
    _g_ws_instances[sock].request_remaining = 0;
    _g_ws_instances[sock].bytes_received = 0;

    /* We expect request data from the client.
     * 
     * So reset the request timeout. The interrupt handler
     * will tick this up. If the sock doesn't finish processing
     * before the timeout, it's toast.
     */
    _g_ws_instances[sock].request_timeout = 0;
    
    /* Mask out this sockets interrupt because it'll be polled
     * while it's active. This works out to be more efficient
     * than having everything interrupt driven.
     */
    w5100_mask_int(sock);
}

static void sock_restart(uint8_t sock)
{
    _g_ws_instances[sock].state = WS_DISCONNECTED;
    _g_ws_instances[sock].request_state = RQ_NONE;
    _g_ws_instances[sock].request_timeout = 0;
    _g_ws_instances[sock].timedout = 0;
    _g_ws_instances[sock].request_remaining = 0;
    _g_ws_instances[sock].header_end = NULL;

    /* Set up the socket again and start listening*/
    if (!w5100_socket(sock, MR_TCP, _g_ws.port))
    {
        debug_printf("sock_restart(%u): Failed creating socket\r\n", sock);
        return;
    }

    if (!w5100_listen(sock))
    {
        debug_printf("sock_restart(%u): Failed listening\r\n", sock);
        return;
    }

    if (w5100_get_sock_state(sock) == SOCK_LISTEN)
    {
        debug_printf("sock_restart(%u): Started listening\r\n", sock);
        _g_ws_instances[sock].state = WS_LISTENING;

        /* Re-enable the interrupt so we get the connected int */
        w5100_unmask_int(sock);
    }
}

void sock_disconnect(uint8_t sock)
{
    _g_ws_instances[sock].state = WS_DISCONNECTING;
    w5100_disconnect(sock);
}

void sock_data_received(uint8_t sock)
{
    uint16_t rsize;
    uint16_t toread;

    rsize = w5100_rx_buffer_length(sock);

    toread = rsize > (MAX_BUF - _g_ws_instances[sock].bytes_received - 1) ?
        (MAX_BUF - _g_ws_instances[sock].bytes_received - 1) : rsize;

    if (rsize > toread)
    {
        debug_printf("sock_data_received(%u): Request is too large by %u bytes\r\n", sock, rsize - toread);
        w5100_disconnect(sock);
        return;
    }

    if (toread > 0)
    {
        debug_printf("sock_data_received(%u): Reading %u (of actual %u) bytes\r\n", sock, toread, rsize);

        w5100_recv(sock, _g_ws_instances[sock].request_buffer + _g_ws_instances[sock].bytes_received, toread);
        _g_ws_instances[sock].bytes_received += toread;
        _g_ws_instances[sock].request_buffer[_g_ws_instances[sock].bytes_received] = '\0';

        if (_g_ws_instances[sock].request_state == RQ_OPENED)
        {
            char *clstr = strstr(_g_ws_instances[sock].request_buffer, "Content-Length:");
            char *headerend = strstr(_g_ws_instances[sock].request_buffer, "\r\n\r\n");

            if (!_g_ws_instances[sock].header_end)
                _g_ws_instances[sock].header_end = headerend;

            if (headerend == NULL)
            {
                debug_printf("sock_data_received(%u): Header incomplete. Leaving as RQ_OPENED.\r\n", sock);
            }
            else if (clstr == NULL)
            {
                debug_printf("sock_data_received(%u): No content. Changing to RQ_REQUEST_RECEIVED.\r\n", sock);
                _g_ws_instances[sock].request_state = RQ_REQUEST_RECEIVED;
            }
            else
            {
                char nbuf[16];
                int i;
                int content_received;

                /* Skip past "Content-Length:" */
                clstr += 15;
                
                /* Parse Content-Length: <len> in a reasonably safe way */
                while (*clstr && isspace(*clstr))
                        clstr++;

                for (i = 0; i < (sizeof(nbuf) - 1) && isdigit(*clstr); i++, clstr++)
                    nbuf[i] = *clstr;
                
                nbuf[i] = '\0';

                _g_ws_instances[sock].request_remaining = atoi(nbuf);

                content_received = &(_g_ws_instances[sock].request_buffer[_g_ws_instances[sock].bytes_received]) - (headerend + 4 /* \r\n\r\n */);

                if (content_received >= _g_ws_instances[sock].request_remaining)
                {
                    debug_printf("sock_data_received(%u): Changing to RQ_REQUEST_RECEIVED. All %u bytes of content received.\r\n",
                    sock, content_received);

                    _g_ws_instances[sock].request_state = RQ_REQUEST_RECEIVED;
                }
                else
                {
                    debug_printf("sock_data_received(%u): Changing to RQ_HEADER_RECEIVED. %s bytes of content remain\r\n",
                        sock, nbuf);
                    _g_ws_instances[sock].request_state = RQ_HEADER_RECEIVED;
                }
            }
        }
        else if (_g_ws_instances[sock].request_state == RQ_HEADER_RECEIVED)
        {
            if (toread <= _g_ws_instances[sock].request_remaining)
            {
                _g_ws_instances[sock].request_remaining -= toread;

                if (_g_ws_instances[sock].request_remaining == 0)
                {
                    debug_printf("sock_data_received(%u): No content left to receive. Changing to RQ_REQUEST_RECEIVED.\r\n", sock);
                    _g_ws_instances[sock].request_state = RQ_REQUEST_RECEIVED;
                }
            }
            else
            {
                debug_printf("sock_data_received(%u): Trying to read in more than expected! Wanted: %u Got: %u\r\n",
                    sock, _g_ws_instances[sock].request_remaining, toread);

                _g_ws_instances[sock].request_state = RQ_REQUEST_RECEIVED;
            }
        }
        else if (_g_ws_instances[sock].request_state == RQ_REQUEST_RECEIVED)
        {
            debug_printf("sock_data_received(%u): Got %u bytes more data when not expecting any!\r\n",
                    sock, toread);
        }
    }
}
