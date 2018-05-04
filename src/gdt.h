#include "types.h"

#define GDTBASE 0x0  // Addr of the gdt
#define GDTSIZE 0xFF // Max number of seg. dec

// Seg. descriptor
struct gdtdesc {
        u16 limit0_15;
        u16 base0_15;
        u8 base16_23;
        u8 acces;
        u8 limit16_19: 4;
        u8 other: 4;
        u8 base24_31;
} __attribute__ ((packed));

// GDTR Register
struct gdtr {
        u16 limit;
        u32 base;
} __attribute__ ((packed));


void init_gdt_desc(u32 base, u32 limit, u8 access, u8 other, struct gdtdesc *desc);
void init_gdt(void);

#ifdef __GDT__
        struct gdtdesc  kgdt[GDTSIZE];
        struct gdtr     kgdtr;
#else
        extern struct gdtdesc   kgdt[];
        extern struct gdtr      kgdtr;
#endif