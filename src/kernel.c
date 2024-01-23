#include"../cpu/idt.h"
#include"../cpu/isr.h"
#include"../cpu/gdt/gdt.h"
#include"../drivers/vga2.h"
#include"../drivers/keyboard.h"

void kernel_main(void){
  clear_screen();

  print_string("good evening\n");
  asm volatile("cli");
  print_string("enabling gdt\n");
  init_gdt();
  print_string("ENABLING INTERRUPTS\n");

  print_string("installing Service Routines...\n");
  isr_install();
  repro_pic();
  irq_install();
  asm volatile("sti"); 

  print_string("initializing keyboard...\n");
  init_keyboard();
}
