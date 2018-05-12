#include "screen.h"
#include "types.h"
#include "io.h"
#include "kbd.h"

void isr_kbd_int(void)
{
        uchar i;
        do {
                i = inb(0x64);
        } while ((i & 0x01) == 0);
        
        i = inb(0x60);
        i--;
        
        if (i < 0x80) {
                pub_kbd_event(i, 0x1);
        } else {
                pub_kbd_event(i, 0x0);
        }
}