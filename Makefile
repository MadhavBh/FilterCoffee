default: run
.PHONY: default build run clean

run: sugama.iso
	qemu-system-x86_64 -cdrom build/sugama.iso

sugama.iso: build/kernel.bin grub.cfg
	mkdir -p build/isofiles/boot/grub
	cp grub.cfg build/isofiles/boot/grub
	cp build/kernel.bin build/isofiles/boot/
	grub-mkrescue -o build/sugama.iso build/isofiles
	
build/kernel.bin: build/boot.o linker.ld
	ld -n -o build/kernel.bin -T linker.ld build/boot.o build/mbhead.o

build/boot.o: boot.asm
	mkdir -p build
	nasm -f elf64 boot.asm -o build/boot.o

build/mbhead.o: mbhead.asm
	mkdir -p build
	nasm -f elf64 mbhead.asm -o build/mbhead.o

clean: 
	rm -rf build
