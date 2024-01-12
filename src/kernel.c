#include"../cpu/idt.h"
#include"../cpu/isr.h"
//#include"../cpu/gdt.h"
#include"../drivers/vga.h"
#include"../drivers/keyboard.h"

void kernel_main(void){
  vga_init();
  //asm volatile("cli");
  //terminal_write_string("enabling gdt\n");
  //init_gdt();
  terminal_write_string("enabling interrupts...\n");
  asm volatile("sti");
  terminal_write_string("installing Service Routines...\n");
  isr_install();
  repro_pic();
  irq_install();
  load_idt();
  

  terminal_write_string("initializing keyboard...\n");
  init_keyboard();
}
