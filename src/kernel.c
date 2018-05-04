#include "types.h"
#include "screen.h"
#include "pic.h"
#include "gdt.h"
#include "idt.h"
#include "io.h"

void _start(void)
{
        fill();
        printnl("--------------");
        printnl("- BARK OS v1 -");
        printnl("--------------");

        log_info("Loading the IDT");
        init_idt();
        log_info("IDT loaded !");
        
        log_info("Initializing the PIC");
        init_pic();
        log_info("PIC initialized");
        
        log_info("Loading the GDT");
        init_gdt();
        log_info("GDT loaded !");
        

        // Init stack ptr %esp
        asm("\
                movw $0x18, %ax     \n \
                movw %ax, %ss       \n \
                movl $0x20000, %esp \n \
        ");

        // enable the interruptions
        sti;
        // jump to main
        main();
}

int main() 
{
        while(1);
}
