cat ./bin/bootsect ./bin/kernel /dev/zero | dd of=build/floppyA bs=512 count=2880
