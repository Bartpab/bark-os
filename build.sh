rm bin/* 
rm obj/*

nasm -f bin -o bin/bootsect src/bootsect.asm
nasm -f elf src/isr.asm	-o obj/isr.o
gcc -c src/screen.c 	-o obj/screen.o -m32
gcc -c src/lib.c 		-o obj/lib.o	-m32
gcc -c src/gdt.c		-o obj/gdt.o	-m32
gcc -c src/idt.c		-o obj/idt.o	-m32
gcc -c src/pic.c		-o obj/pic.o	-m32
gcc -c src/interrupt.c	-o obj/interrupt.o	-m32
gcc -c src/kernel.c 	-o obj/kernel.o -m32


ld --oformat binary -Ttext 1000 \
		obj/kernel.o 	\
		obj/screen.o 	\
		obj/gdt.o 	 	\
		obj/idt.o 	 	\
		obj/pic.o 	 	\
		obj/lib.o 	 	\
		obj/isr.o 	 	\
		obj/interrupt.o	\
		-o bin/kernel -m elf_i386
cat bin/bootsect bin/kernel /dev/zero | dd of=build/bark-os.iso bs=512 count=2880
