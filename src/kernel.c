#include"../cpu/idt.h"
#include"../cpu/isr.h"
#include"vga.h"
#include"../drivers/keyboard.h"

void kernel_main(void){
  terminal_init();
  terminal_write_string("hello\n");
  terminal_write_string("installing Service Routines...\n");
  isr_install();
  irq_install();
  repro_pic();
  load_idt();
  

  terminal_write_string("enabling interrupts...\n");
  asm volatile("sti");

  terminal_write_string("initializing keyboard...\n");
  init_keyboard();
}
