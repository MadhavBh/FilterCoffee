global loader

extern mbheader

MAGIC_NUMBER    equ 0xe85250d6
PAGE_ALIGN      equ 1<<0 
MEM_INFO        equ 1<<1
FLAGS           equ PAGE_ALIGN | MEM_INFO 
CHECKSUM        equ -0xe85250d6 

section .mbheader
header_start:
  dd 0xe85250d6 ;magic MAGIC_NUMBER
  dd 0          ; protected mode code
  dd header_end - header_start ; length

  dd 0x100000000 - (0xe85250d6 + 0 + (header_end - header_start))


  dw 0 ; type
  dw 0 ; FLAGS
  dd 8 ; size
header_end:
