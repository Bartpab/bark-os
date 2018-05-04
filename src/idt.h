#include "types.h"

#define IDTBASE 0x800  // Physical addr of the IDT
#define IDTSIZE 0xFF   // Max number of desc
#define INTGATE 0x8E00 // INT Gate
/*
        63                                 32
        -------------------------------------
        | offset 31:16 |1|00|0|1110|000|....|
        -------------------------------------
        | seg selector | offset 15:0        |
        -------------------------------------
        31                                  0

*/
struct idtdesc {
        u16 offset0_15;
        u16 select;
        u16 type;
        u16 offset16_31;
} __attribute__ ((packed));

struct idtr {
	u16 limit;
	u32 base;
} __attribute__ ((packed));

struct idtr kidtr;              // IDT Register
struct idtdesc kidt[IDTSIZE];   // IDT Table

void init_idt_desc(u16 select, u32 offset, u16 type, struct idtdesc* desc);
void init_idt(void);