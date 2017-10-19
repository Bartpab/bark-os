%define BASE	0x100 ; 0x0100:0x00 = 0x1000
%define KSIZE	1 ; Number of sector of 512 bytes to load

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
	
; Jump to the kernel
	jmp dword BASE:0
; -----------
; Variables
; -----------
	bootSectMsg:		db "Welcome to BABS (Bart's Awesome Boot Sector) !", 13, 10, 0
	loadingKernelMsg: 	db "Loading kernel...", 13, 10, 0 ; Hello World + CR + LF + NULL
	
	bootdrv: 			db 0
; -----------
	
; --- No Operation until 510 bytes to fill the rester of the 
	times 510 - ($-$$) db 144
	dw 0xAA55 ; Word that indicate to the BIOs that this sector is a MBR
	