#include"../drivers/vga2.h"
#include"comm.h"

void print_help(){
  print_string("Enter commands: HELP -- EXIT -- CLEAR \n");
}

void halt_cpu(){
  print_string("Halting the CPU");
  asm volatile("hlt");
} 

void clearScreen(){

  clear_screen();
  print_string("\n>>");
}


