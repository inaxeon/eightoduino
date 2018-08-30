/*
 *   8OD - Arduino form factor i8086 based SBC
 *   Matthew Millman (tech.mattmillman.com)
 *
 *   Misc web server helper routines
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
#include <ctype.h>

int strqry(const char *in, const char *key, char *val, int valmax)
{
    const char *vp = NULL;
    int foundlen = 0;

    if (in == NULL || key == NULL || valmax == 0)
        return NULL;

    for ( ; *in; in++) {
        const char *h, *n;
        for (h = in, n = key; *h && *n && (*h == *n); ++h, ++n) {
        }
        if (*n == '\0' && *h == '=') {
            vp = ++h;
            break;
        }
    }

    if (!vp)
        return 0;

    for ( ; *vp && *vp != '&' && --valmax > 0; vp++, foundlen++)
        *val++ = *vp;
    *val = '\0';

    return foundlen;
}

void urldecode(char *dst, const char *src)
{
    char a, b;
    while (*src) {
        if ((*src == '%') &&
        ((a = src[1]) && (b = src[2])) && (isxdigit(a) && isxdigit(b))) {
                if (a >= 'a')
                    a -= 'a'-'A';
                if (a >= 'A')
                    a -= ('A' - 10);
                else
                    a -= '0';
                if (b >= 'a')
                    b -= 'a'-'A';
                if (b >= 'A')
                    b -= ('A' - 10);
                else
                    b -= '0';
                *dst++ = 16 * a + b;
                src += 3;
        } else if (*src == '+') {
            *dst++ = ' ';
            src++;
        }
        else {
            *dst++ = *src++;
        }
    }
    *dst++ = '\0';
}

void removexss(char *s)
{
    for (; *s; s++)
    {
        if (*s == '>' || *s == '<' || *s == '&' || *s == '"' || *s == '\'')
            *s = ' ';
    }
}
