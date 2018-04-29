%define BASE	0x100 ; 0x0100:0x00 = 0x1000
%define KSIZE	50 ; Number of sector of 512 bytes to load

[BITS 16] ; We work on 16-bits
[ORG 0x0] ; Addr offset to add to each addr referenced after

jmp start
%include "./src/UTIL.INC"
start:

; Init segment 0x07C00:0000, the boot sector loaded by the BIOS
	mov ax, 0x07C0
	mov ds, ax
	mov es, ax

; Create stack 0x8F000:80000
	mov ax, 0x8000
	mov ss, ax
	mov sp, 0xf000

; Get the boot unit
	mov [bootdrv], dl
	
; print loading
	call clear_screen
	mov si, bootSectMsg
	call print
	mov si, loadingKernelMsg
	call print

; Load kernel
	xor ax, ax
	int 0x13
	
	push es
	mov ax, BASE
	mov es, ax
	mov bx, 0
	
	mov ah, 2
	mov al, KSIZE
	mov ch, 0
	mov cl, 2
	mov dh, 0
	mov dl, [bootdrv]
	int 0x13
	pop es

; init ptr on Global Descriptor Table (GDT)
	mov ax, gdtend 		;compute the limit of the GDT
	mov bx, gdt
	sub ax, bx
	mov word [gdtptr], ax
	
	; compute the linear addr of the GDT
	xor eax, eax		
	xor ebx, ebx
	mov ax, ds
	mov ecx, eax
	shl ecx, 4
	mov bx, gdt
	add ecx,  ebx
	mov dword [gdtptr + 2], ecx

; Jump to protected mode
	cli; clear interrup flags
	lgdt [gdtptr]
	; Set the protected mode by switching CR0 reg to 1 
	mov eax, cr0
	or ax, 1
	mov cr0, eax
	
	jmp next

next:
	; Init data selector
	mov ax, 0x10
	mov ds, ax
	mov fs, ax
	mov gs, ax
	mov es, ax
	; Init seg. stack
	mov ss, ax
	mov esp, 0x9F000
	
; Jump to the kernel
	jmp dword 0x8:0x1000    ; reinitialise le segment de code

; -----------
; Variables
; -----------
	bootSectMsg:		db "Welcome to BABS (Bart's Awesome Boot Sector) !", 13, 10, 0
	loadingKernelMsg: 	db "Loading kernel...", 13, 10, 0 ; Hello World + CR + LF + NULL
	bootdrv: 			db 0
	
	gdt:
		db 0, 0, 0, 0, 0, 0, 0, 0
	gdt_cs:
		db 0xFF, 0xFF, 0x0, 0x0, 0x0, 10011011b, 11011111b, 0x0
	gdt_ds:
		db 0xFF, 0xFF, 0x0, 0x0, 0x0, 10010011b, 11011111b, 0x0
	gdtend:
	gdtptr:
		dw 0; limit
		dd 0; base
; -----------
	
; --- No Operation until 510 bytes to fill the rester of the 
	times 510 - ($-$$) db 144
	dw 0xAA55 ; Word that indicate to the BIOs that this sector is a MBR
	