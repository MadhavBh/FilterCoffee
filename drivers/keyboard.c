#include <stdint.h>
#include"../drivers/vga2.h"
#include"../cpu/idt.h"
#include"../cpu/isr.h"
#include"../src/ports.h"
#include "../src/utils.h"

void print_letter(uint8_t scancode){
  switch (scancode) {
    case 0x00:
      print_string("error");
      break;
    case 0x01:
      print_string("esc");
      break;
    case 0x02:
      print_string("1");
      break;
    case 0x03:
      print_string("2");
      break;

    default:
      if(scancode <= 0x7f){
        print_string("unknown key\n");
      }else if(scancode <= 0x39 +0x80 ){
        print_string("key up\n");
        print_letter(scancode-0x80);
      }else{
        print_string("unknown key");
      }
    break; 
  }
}
static void keyboard_callback(registers_t *regs){
  print_string("inkeyboardcallback\n");  
  port_byte_out(0x60, 0x3);
  uint8_t scancode = port_byte_in(0x60);
  print_letter(scancode);
}

void init_keyboard(){
  print_string("in init keyboard\n");
  register_interrupt_handler(IRQ1, keyboard_callback);
  //uint8_t scancode = port_byte_in(0x60);
  //print_letter(scancode);
}
