section .text

global flush_gdt
[extern gdtptr]

flush_gdt:
  lgdt[gdtptr]
  mov ax, 0x10
  mov ds, ax
  mov es, ax
  mov fs, ax 
  mov gs, ax
  mov ss, ax
  jmp 0x08: flush_two 

flush_two:
  ret


