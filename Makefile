default: run
.PHONY: default build run clean

run: build/filtercoffee.iso
	qemu-system-x86_64 -cdrom build/filtercoffee.iso

build/filtercoffee.iso: build/kernel.bin grub.cfg
	mkdir -p build/isofiles/boot/grub
	cp grub.cfg build/isofiles/boot/grub
	cp build/kernel.bin build/isofiles/boot/
	grub-mkrescue -o build/filtercoffee.iso build/isofiles

build/kernel.bin: build/boot.o build/mbhead.o build/kernel.o linker.ld
	#ld -n -m elf_i386 -o build/kernel.bin -T linker.ld build/boot.o build/mbhead.o
	/home/madhavbh/opt/cross/bin/i686-elf-gcc -T src/linker.ld -o build/kernel.bin -ffreestanding -O2 -nostdlib build/mbhead.o build/boot.o build/kernel.o -lgcc

build/kernel.o: src/kernel.c 
	/home/madhavbh/opt/cross/bin/i686-elf-gcc -c src/kernel.c -o build/kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra

build/boot.o: src/boottwo.asm
	mkdir -p build
	nasm -felf32 src/boottwo.asm -o build/boot.o
	#i686-elf-as boot.asm -o build/boot.o

build/mbhead.o: src/mbhead.asm
	mkdir -p build
	nasm -felf32 src/mbhead.asm -o build/mbhead.o
	#i686-elf-as mbhead.asm -o build/mbhead.o
clean: 
	rm -rf build
