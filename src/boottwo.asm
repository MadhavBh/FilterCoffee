global loader

stack_size equ 0x8000

; Unintialized memory for the stack
section .bss
align 16
stack_bottom:
  resb 16384 ;reserve 16kb for stack
stack_top:


;executable instruction set.
section .text
global loader: function ( loader.end - loader)

loader: 
  mov esp, stack_top ; setting stack top 

  extern kernel_main 
  call kernel_main  ; calling external C kernel

  cli ;Invalidates a line containing the byte addressed in either the data or instruction cache, causing subsequent references to       retrieve the line again from main memory.

.hang: hlt
  jmp .hang ; loop

.end:
