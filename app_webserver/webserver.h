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

#ifndef __WEBSERVER_H__
#define __WEBSERVER_H__

typedef struct
{
    int port;
    void (*http_response_sent)(uint8_t instance);
    void (*http_post)(uint8_t instance, char *filename, char *header, char *request);
    void (*http_get)(uint8_t instance, char *filename, char *header);
} ws_t;

void ws_interrupt(void);
uint16_t ws_send(uint8_t instance, const uint8_t *buf, uint16_t buflen);
void ws_init(ws_t *ws);
void ws_process(void);
void ws_disconnect(uint8_t instance);

#endif /* __WEBSERVER_H__ */
