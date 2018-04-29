nasm -f bin -o ./bin/bootsect ./src/bootsect.asm
gcc -c ./src/screen.c -o ./obj/screen.o
gcc -c ./src/kernel.c -o ./obj/kernel.o

ld --oformat binary -Ttext 1000 ./obj/kernel.o ./obj/screen.o -o ./tmp/kernel.tmp