#include "io.h"

void init_pic(void)
{
        // Init ICW1
        outb(0x20, 0x11);
        outb(0xA0, 0x11);

        // Init ICW2
        outb(0x21, 0x20);
        outb(0xA1, 0x70);

        // Init ICW3
        outb(0x21, 0x04);
        outb(0xA1, 0x02);

        // Init ICW4
        outb(0x21, 0x01);
        outb(0xA1, 0x01);

        // Mask the interrupt
        outb(0x21, 0x0);
        outb(0xA1, 0x0);
}