#include "types.h"

#define __KBD__
#include "kbd.h"

void init_kbd ()
{
        kbdeventr.limit = KBD_CALLBACK_SIZE;
        kbdeventr.cursor = 0x0;
}

int sub_kbd_event(kbd_callback_t callback)
{
        if (kbdeventr.cursor >= kbdeventr.limit) {
                return 0x01; // Error
        } else {
            kbdcallbacks[kbdeventr.cursor] = callback;
            kbdeventr.cursor++;
            return 0x0;
        }
}

void pub_kbd_event (uchar key, uchar pressed) 
{
        struct kbd_event event;
        u16 cursor;

        event.key = key;
        event.pressed = pressed;

        for (cursor = 0; cursor < kbdeventr.cursor; cursor++) {
                kbdcallbacks[cursor](event);
        }
        
}

uchar ktc(uchar key)
{
        return kbdmap[key * 4];
}
