section .data
    ; Define the GDT entries
    gdt_start:
        ; Null descriptor
        dd 0
        dd 0
        ; Code segment descriptor
        dw 0FFFFh         ; Limit (low)
        dw 0              ; Base (low)
        db 0              ; Base (middle)
        db 10011010b      ; Access byte
        db 11001111b      ; Granularity byte
        db 0              ; Base (high)

        ; Data segment descriptor
        dw 0FFFFh         ; Limit (low)
        dw 0              ; Base (low)
        db 0              ; Base (middle)
        db 10010010b      ; Access byte
        db 11001111b      ; Granularity byte
        db 0              ; Base (high)

    gdt_end:

section .text
global loader;: function (loader.end - loader)

loader:
    ; Calculate the size of the GDT
    gdt_size equ gdt_end - gdt_start - 1

    ; Create the GDT descriptor
    gdtr:
        dw gdt_size            ; Size of the GDT - 1
        dd gdt_start           ; Address of the GDT

    ; Load the GDT
    lgdt [gdtr]

    ; Set up data segment
    mov ax, 0x10   ; Data segment selector (0x10 is the offset in the GDT)
    mov ds, ax     ; Load the data segment register

    ; Set up stack segment
    mov ss, ax     ; Stack segment same as data segment for simplicity

    mov esp, stack_top  ; Set the stack pointer to the end of stack

    extern kernel_main
    call kernel_main
    ; Hang or loop here (halt the CPU or loop indefinitely)
    cli       ; Clear interrupts
.hang: hlt  ; halt the cpu 
  jmp .hang

.end 

section .bss
align 16 
stack_bottom:
    resb 16384  ; Reserve space for stack
stack_top:       ; Define the end of stack marker

