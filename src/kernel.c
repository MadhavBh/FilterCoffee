#include"../cpu/idt.h"
#include"../cpu/isr.h"
#include"../cpu/gdt/gdt.h"
#include"../drivers/vga2.h"
#include"../drivers/keyboard.h"

void kernel_main(void){
  clear_screen();
  print_string("good evening\n");
  print_string("enabling gdt\n");
  init_gdt();
  asm volatile("cli");
  isr_install();
  //asm volatile("sti"); 
  print_string("installing Service Routines...\n");


  print_string("initializing keyboard...\n");
  init_keyboard();
}
