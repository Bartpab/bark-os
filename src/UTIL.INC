; Take the segment DS:SI and print its content
clear_screen:
	push ax
	push bx
	mov ah, 0x0
	mov al, 0x03
	int 0x10
	pop bx
	pop ax
	ret
	
print:
	push ax
	push bx
.next:
	lodsb ; DS:SI 
	cmp al, 0
	jz .end
	mov ah, 0x0E
	mov bx, 0x07
	int 0x10
	jmp .next
.end:
	pop bx
	pop ax
	ret