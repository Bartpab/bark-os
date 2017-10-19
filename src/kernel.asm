[BITS 16]
[ORG 0x0]

jmp start

%include "./src/UTIL.INC"


_sum:
	push bx
	add ax, bx
	pop bx
	ret

start:
; initialisation des segments en 0x100
    mov ax, 0x100
    mov ds, ax
    mov es, ax

; initialisation du segment de pile
    mov ax, 0x8000
    mov ss, ax
    mov sp, 0xf000

; affiche un msg
    mov si, kernelVersion
    call print
	mov si, helloMarie
	call print
	
	mov al, 0
end:
	inc al
	call _sum
	mov bh, al
	add al, 0x30
	mov ah, 0x09
	int 0x10
	mov al, bh
    jmp end



kernelVersion: db 'BARK x86 v1.2', 13, 10, 0
helloMarie: db 'Hello world', 13, 10, 0
