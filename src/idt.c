#include "types.h"
#include "lib.h"
#include "io.h"
#include "idt.h"

extern void _asm_default_int(void);
extern void _asm_irq_1(void);

void init_idt_desc(u16 select, u32 offset, u16 type, struct idtdesc* desc)
{
        desc->offset0_15  = (offset & 0xFFFF);
        desc->select      = select;
        desc->type        = type;
        desc->offset16_31 = (offset & 0xFFFF0000) >> 16;
        return;
}

void init_idt(void)
{
        int i;

        for(i = 0; i < IDTSIZE; i++) {
                init_idt_desc(0x08, (u32) _asm_default_int, INTGATE, &kidt[i]);
        }

        init_idt_desc(0x08, (u32) _asm_irq_1, INTGATE, &kidt[33]); // Keyboard interrupt

        kidtr.base = IDTBASE;
        kidtr.limit = 8 * IDTSIZE;

        // Copy the IDT to its addr
        memcpy((char*) kidtr.base, (char*) kidt, kidtr.limit);

        // Load the IDT
        asm("lidtl (kidtr)");
}