/* An unused, utterly useless function
 *
 * When developing the app in this directory I noticed an issue
 * where the Open WATCOM 1.7a linker (wlink) crashes. Putting a little bit
 * of unused code into a seperate source file seems to fix the problem.
 *
 * This here is about the minimum that does the business.
 * This function would be stripped out of the final executable.
 */

#include <stdint.h>

uint8_t dummy(uint8_t *p, uint16_t c)
{
    uint8_t  a;
    uint16_t i;
    uint8_t  b;

    a = 0;

    for (i = 0; i != c; i++)
        b = p[i];

    a = 0;

    for (i = 0; i != c; i++)
        b = p[i];

    a = 0;

    for (i = 0; i != c; i++)
        b = p[i];

    return a;
}
