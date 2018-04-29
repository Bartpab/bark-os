[BITS 32]

EXTERN scrollup, print
GLOBAL _start

_start:
    mov eax, msg
    push eax
    call print
    pop eax


end:
    jmp end

msg db 'Coucou ma cherie ;)', 10, 0