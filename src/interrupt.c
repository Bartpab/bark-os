#include "screen.h"
#include "types.h"
#include "io.h"

void isr_kbd_int(void)
{
        uchar i;
        do {
                i = inb(0x64);
        } while ((i & 0x01) == 0);
        i = inb(0x60);
        i--;
        
        if (i < 0x80) {
                char c[2];
                c[0] = (char)i;
                c[1] = '\0';

                print(c);
        }
}