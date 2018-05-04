extern isr_kbd_int
global _asm_irq_1, _asm_default_int

_asm_default_int:
    ; Send an EndOfInterrupt (EOI)
    ; to the PIC
    mov al, 0x20
    out 0x20, al
    iret

_asm_irq_1:
    call isr_kbd_int
    ; Send an EndOfInterrupt (EOI)
    ; to the PIC
    mov al, 0x20
    out 0x20, al
    iret