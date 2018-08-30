/*
 *   8OD - Arduino form factor i8086 based SBC
 *   Matthew Millman (tech.mattmillman.com)
 *
 *   Wiznet W5100 web server program
 *
 *   Communication with the W5100 is entirely interrupt driven,
 *   meaning that there's no CPU time wasted polling, or in tight delay
 *   loops, so this app is able to make effective use of multiple sockets.
 *   All four of the W5100 sockets are used by this app.
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
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <ctype.h>

#include "eod_io.h"
#include "lcd_io.h"
#include "uart.h"
#include "lcd.h"
#include "util.h"
#include "httputil.h"
#include "w5100.h"
#include "webserver.h"

//#define debug_printf(...)
//#define error_printf(...)
#define debug_printf(...) printf(__VA_ARGS__)
#define error_printf(...) printf(__VA_ARGS__)

#define MAX_BUF      8912
#define LINE_LEN     40
#define LINE_COUNT   4

static void add_message(char *name, char *message);
static void update_lcd(void);
static void send_index(uint8_t sock);
static void send_404(uint8_t sock);

static void http_post(uint8_t instance, char *filename, char *header, char *request);
static void http_get(uint8_t instance, char *filename, char *header);
static void http_response_sent(uint8_t instance);

char *_g_lcdLines[LINE_COUNT];

#define RFLG_UPDATE_LCD     0x01

uint8_t _g_runFlags;

void main(void)
{
    int i;
    w5100_config_t w5100config;
    ws_t ws_config;

    uart_open(UARTA, 115200, 8, PARITY_NONE, 1, 0);
    setup_printf(UARTA);
    
    for (i = 0; i < LINE_COUNT; i++)
        _g_lcdLines[i] = NULL;

    cpld_write(PORTA, (1 << 10), (1 << 10)); //ETH CS High
    cpld_write(TRISA, (1 << 10), 0); //PIN 10 Output (ETH CS)

    /* Set Bit 2 (EXTINTA) of PORTA as input */
    cpld_write(TRISA, (1 << 2), (1 << 2));

    /* Enable interrupts globally, and enable the external interrupt A (on GFP2)
     * which is negative logic, and the ethernet shield happens to be connected to
     */
    cpld_write(CONFIG, (CONFIG_GINT | CONFIG_EXTINTA | CONFIG_TMINT), (CONFIG_GINT | CONFIG_EXTINTA | CONFIG_TMINT));

#if 0
    SET4(w5100config.ip_addr, 81, 187, 233, 78); /* Spare public IP address - incendiary.inaxeon.co.uk */
    SET4(w5100config.sub_mask, 255, 255, 255, 248);
    SET4(w5100config.gw_addr, 81, 187, 233, 73);
#else
    SET4(w5100config.ip_addr, 192, 168, 0, 68);
    SET4(w5100config.sub_mask, 255, 255, 255, 0);
    SET4(w5100config.gw_addr, 192, 168, 0, 1);
#endif

    SET6(w5100config.mac_addr, 0x00, 0x00, 0xCD, 0x28, 0x07, 0xC7);

    w5100_init(&w5100config);

    _g_runFlags = 0;

    lcd_init();

    ws_config.port = 80;
    ws_config.http_post = &http_post;
    ws_config.http_get = &http_get;
    ws_config.http_response_sent = &http_response_sent;

    ws_init(&ws_config);

    for (;;)
    {
        ws_process();

        if (_g_runFlags & RFLG_UPDATE_LCD)
        {
            _g_runFlags &= ~RFLG_UPDATE_LCD;
            update_lcd();
        }

        /* Do other stuff here */
    }
}

static void http_post(uint8_t instance, char *filename, char *header, char *request)
{
    char namebuf[LINE_LEN * 3];
    char messagebuf[LINE_LEN * 3];

    if (stricmp(filename, "/"))
    {
        send_404(instance);
        return;
    }

    strqry(request, "name", namebuf, sizeof(namebuf));
    strqry(request, "message", messagebuf, sizeof(messagebuf));

    add_message(namebuf, messagebuf);

    send_index(instance);
}

static void http_get(uint8_t instance, char *filename, char *header)
{
    if (stricmp(filename, "/"))
    {
        send_404(instance);
        return;
    }

    send_index(instance);
}

static void http_response_sent(uint8_t instance)
{
    /* Due to the simplicity of this app, we can disconnect now. */
    ws_disconnect(instance);
}

static void add_message(char *name, char *message)
{
    int i;

    urldecode(name, name);
    urldecode(message, message);

    removexss(name);
    removexss(message);

    name[LINE_LEN - 5] = '\0';
    message[LINE_LEN - 5] = '\0';

    if (!*name || !*message)
        return;

    if (_g_lcdLines[3])
        free(_g_lcdLines[3]);

    for (i = (LINE_COUNT - 2); i >= 0; i--)
        _g_lcdLines[i + 1] = _g_lcdLines[i];

    _g_lcdLines[0] = malloc(LINE_LEN + 1);

    /* Truncate what's left from the name len from the message */
    message[LINE_LEN - 2 - strlen(name)] = '\0';

    sprintf(_g_lcdLines[0], "%s: %s", name, message);

    _g_runFlags |= RFLG_UPDATE_LCD;
}

#define IDT0 "    "
#define IDT1 "        "
#define IDT2 "            "
#define IDT3 "                "
#define IDT4 "                    "
#define IDT5 "                        "
#define IDT6 "                            "
#define IDT7 "                                "

#define HEAD \
    "<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Strict//EN\" \"http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd\">\r\n"   \
    "<html xmlns=\"http://www.w3.org/1999/xhtml\" lang=\"en\" xml:lang=\"en\">\r\n"                                           \
    IDT0 "<head>\r\n"                                                                                                         \
    IDT1 "<title>8OD Web demo</title>\r\n"                                                                                    \
    IDT1 "<meta http-equiv=\"content-type\" content=\"text/html; charset=ISO-8859-1\" />\r\n"                                 \
    IDT1 "<style type=\"text/css\">\r\n" \
    IDT2 "@media only screen and (-moz-min-device-pixel-ratio: 1.5),\r\n" \
    IDT3 "only screen and (-o-min-device-pixel-ratio: 3/2),\r\n" \
    IDT3 "only screen and (-webkit-min-device-pixel-ratio: 1.5),\r\n" \
    IDT3 "only screen and (min-device-pixel-ratio: 1.5),\r\n" \
    IDT3 "only screen and (-moz-min-device-pixel-ratio: 2),\r\n" \
    IDT3 "only screen and (-o-min-device-pixel-ratio: 2/1),\r\n" \
    IDT3 "only screen and (-webkit-min-device-pixel-ratio: 2),\r\n" \
    IDT3 "only screen and (min-device-pixel-ratio: 2)\r\n" \
    IDT2 "{\r\n"                   \
    IDT2 "body\r\n" \
    IDT2 "{\r\n"                               \
    IDT3 "font-size: 50px;\r\n"                \
    IDT3 "padding: 30px;\r\n"                  \
    IDT2 "}\r\n"\
    IDT2 "ol\r\n" \
    IDT2 "{\r\n"                               \
    IDT3 "margin-left: 40px;\r\n"                  \
    IDT2 "}\r\n"\
    IDT2 "h1\r\n" \
    IDT2 "{\r\n"                               \
    IDT3 "font-size: 60px;\r\n"                  \
    IDT2 "}\r\n"\
    IDT2 ".mobilehide\r\n" \
    IDT2 "{\r\n"                               \
    IDT3 "display: none;\r\n"                  \
    IDT2 "}\r\n"\
    IDT2 "input[type=text]\r\n"                \
    IDT2 "{\r\n"\
    IDT3 "font-size: 50px;\r\n"\
    IDT3 "padding: 10px;\r\n"\
    IDT2 "}\r\n"\
    IDT2 "input[type=submit]\r\n"\
    IDT2 "{\r\n"\
    IDT3 "font-size: 50px;\r\n"\
    IDT3 "padding: 30px;\r\n"\
    IDT2 "}\r\n"\
    IDT1 "}\r\n"\
    IDT1 "</style>\r\n" \
    IDT0 "</head>\r\n" \
    IDT0 "<body>\r\n"

#define TAIL            \
    IDT0 "</body>\r\n"  \
    "</html>\r\n"

#define INDEX1 \
    IDT1 "<h1>8OD Web server demo app</h1>\r\n" \
    IDT1 "<div class=\"mobilehide\">This application shows the last four messages posted to it here, and on a 40x4 LCD screen</div>\r\n" \
    IDT1 "<div>\r\n"
    

#define INDEX2 \
    IDT1 "</div>\r\n" \
    IDT1 "<form method=\"post\" action=\"/\">\r\n" \
    IDT2 "<div style=\"margin-top: 1.0em\">\r\n" \
    IDT3 "<p>\r\n" \
    IDT4 "<label for=\"name\">Name:</label>\r\n" \
    IDT3 "</p>\r\n" \
    IDT3 "<p>\r\n" \
    IDT4 "<input id=\"name\" name=\"name\" type=\"text\" />\r\n" \
    IDT3 "</p>\r\n" \
    IDT3 "<p>\r\n" \
    IDT4 "<label for=\"message\">Message:</label>\r\n" \
    IDT3 "</p>\r\n" \
    IDT3 "<p>\r\n" \
    IDT4 "<input id=\"message\" name=\"message\" type=\"text\" />\r\n" \
    IDT3 "</p>\r\n" \
    IDT3 "<p>\r\n" \
    IDT4 "<input type=\"submit\" value=\"Submit\" />\r\n" \
    IDT3 "</p>\r\n" \
    IDT2 "</div>\r\n" \
    IDT1 "</form>\r\n"


static void send_index(uint8_t instance)
{
    int i;
    int sendsize;
    char buf[MAX_BUF];
    char line[128];

    strcpy(buf, "HTTP/1.0 200 OK\r\n");
    strcat(buf, "Content-type: text/html\r\n\r\n");

    strcat(buf, HEAD);
    strcat(buf, INDEX1);

    if (_g_lcdLines[0] != NULL)
        strcat(buf, IDT2 "<ol>\r\n");

    for (i = 0; i < LINE_COUNT; i++)
    {
        if (_g_lcdLines[i])
        {
            sprintf(line, IDT3 "<li>%s</li>\r\n", _g_lcdLines[i]);
            strcat(buf, line);
        }
    }

    if (_g_lcdLines[0] != NULL)
        strcat(buf, IDT2 "</ol>\r\n");

    strcat(buf, INDEX2);
    strcat(buf, TAIL);

    sendsize = strlen(buf);
    debug_printf("Index page size: %u\r\n", sendsize);
    ws_send(instance, buf, sendsize);
}

static void send_404(uint8_t sock)
{
    uint8_t buf[MAX_BUF];

    strcpy(buf, "HTTP/1.0 404 Not Found\r\n\r\n");

    ws_send(sock, buf, strlen(buf));
}

static void update_lcd(void)
{
    int line;

    lcd_clear01();
    lcd_clear23();

    for (line = 0; line < LINE_COUNT; line++)
    {
        lcd_pos(line, 0);
        if (_g_lcdLines[line])
            lcd_string(_g_lcdLines[line]);
    }
}

