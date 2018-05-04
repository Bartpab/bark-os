#include "lib.h"
#include "types.h"

#define __GDT__
#include "gdt.h"

void init_gdt_desc(u32 base, u32 limit, u8 access, u8 other, struct gdtdesc *desc) 
{
              desc->limit0_15 = (limit & 0xFFFF);
              desc->limit16_19 = (limit & 0xF0000) >> 16;

              desc->base0_15  = (base & 0xFFFF);
              desc->base16_23 = (base & 0xFF0000) >> 16;  
              desc->base24_31 = (base & 0xFF000000) >> 24;

              desc->acces = access;
              desc->other = (other & 0xF);
              return;
}

void init_gdt(void) 
{
        init_gdt_desc(0x0, 0x0, 0x0, 0x0, &kgdt[0]); 
        // Code, 4G0 0x1
        init_gdt_desc(0x0, 0xFFFFF, 0x9B, 0x0D, &kgdt[1]);
        // Data
        init_gdt_desc(0x0, 0xFFFFF, 0x93, 0x0D, &kgdt[2]);
        // Stack
        init_gdt_desc(0x0, 0x0, 0x97, 0x0D, &kgdt[3]);

        // Init the struct for the GDT Register
        kgdtr.limit = GDTSIZE * 8;
        kgdtr.base  = GDTBASE;

        // Copy the gdt to its addr
        memcpy((char*) kgdtr.base, (char*)kgdt, kgdtr.limit);
        // Load the gdtr
        asm("\
                lgdtl (kgdtr)           \n \
        ");
        // Init the mem. segments
        asm("\
                movw $0x10, %ax         \n \
                movw %ax, %ds           \n \
                movw %ax, %es           \n \
                movw %ax, %fs           \n \
                movw %ax, %gs           \n \
                ljmp $0x08, $next       \n \
                next:                   \n \
        ");
}