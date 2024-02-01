default: run
.PHONY: default build run clean

run: build/filtercoffee.iso
	qemu-system-x86_64 -d int  -no-reboot -cdrom build/filtercoffee.iso -k en-us 


build/filtercoffee.iso: build/kernel.bin grub.cfg
	mkdir -p build/isofiles/boot/grub
	cp grub.cfg build/isofiles/boot/grub
	cp build/kernel.bin build/isofiles/boot/
	grub-mkrescue -o build/filtercoffee.iso build/isofiles

build/kernel.bin: build/boot.o build/mbhead.o build/vga.o build/kernel.o build/isr.o build/idt.o build/gdt.o build/interrupt.o build/descriptor.o build/ports.o build/utils.o build/keyboard.o linker.ld
	#ld -n -m elf_i386 -o build/kernel.bin -T linker.ld build/boot.o build/mbhead.o
	/home/madhavbh/opt/cross/bin/i686-elf-gcc -T src/linker.ld -o build/kernel.bin -ffreestanding -O2 -nostdlib build/mbhead.o build/boot.o build/vga.o build/isr.o build/idt.o build/gdt.o build/interrupt.o build/descriptor.o build/ports.o build/utils.o build/keyboard.o  build/kernel.o -lgcc

build/kernel.o: src/kernel.c 
	/home/madhavbh/opt/cross/bin/i686-elf-gcc -c src/kernel.c -o build/kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra

build/vga.o: drivers/vga2.c 
	/home/madhavbh/opt/cross/bin/i686-elf-gcc -c drivers/vga2.c -o build/vga.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra

build/isr.o: cpu/isr.c #new CPU
	/home/madhavbh/opt/cross/bin/i686-elf-gcc -c cpu/isr.c -o build/isr.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra

build/idt.o: cpu/idt.c #new CPU
	/home/madhavbh/opt/cross/bin/i686-elf-gcc -c cpu/idt.c -o build/idt.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra

build/gdt.o: cpu/gdt/gdt.c 
	/home/madhavbh/opt/cross/bin/i686-elf-gcc -c cpu/gdt/gdt.c -o build/gdt.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra

build/descriptor.o: cpu/gdt/descriptor.asm
	nasm -felf32 cpu/gdt/descriptor.asm -o build/descriptor.o

build/interrupt.o: cpu/interrupt.asm # new CPU 
	nasm -felf32 cpu/interrupt.asm -o build/interrupt.o

build/ports.o: drivers/ports.c #new PORTS
	/home/madhavbh/opt/cross/bin/i686-elf-gcc -c drivers/ports.c -o build/ports.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra

build/utils.o: drivers/utils.c 
	/home/madhavbh/opt/cross/bin/i686-elf-gcc -c drivers/utils.c -o build/utils.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra

build/keyboard.o: drivers/keyboard2.c #new driver
	/home/madhavbh/opt/cross/bin/i686-elf-gcc -c drivers/keyboard2.c -o build/keyboard.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra

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
