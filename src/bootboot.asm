[bits 32]

global loader

loader:
  mov esp, sys_stack
  jmp __stub

boot:
  mb_page_align equ 1<<0
  mb_mem_info equ 1<<x10
  mb_aout_kludge equ 1<<16
  mb_header_magic equ 0x1BADB002
  mb_header_flags equ mb_page_align | mb_mem_info | mb_aout_kludge
  mb_checksum equ -(mb_header_magic + mb_header_flags)

  extern code, bss, end

  dd mb_header_magic
  dd mb_header_flags
  dd mb_checksum

  dd boot
  dd code
  dd bss
  dd end 
  dd loader

__stub:
  push ebx
  cli
  extern kernel_main
  call kernel_main
  jmp $ 


global flush_gdt
extern gdtptr

flush_gdt:
  lgdt [gdtptr]
  mov ax, 0x10
  mov ds, ax
  mov es, ax
  mov fs, ax
  mov gs, ax
  mov ss, ax
  jmp 0x80:flush_two

flush_two:
  ret

