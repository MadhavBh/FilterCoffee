#include <stdint.h>
#include"../drivers/vga2.h"
#include"../cpu/idt.h"
#include"../cpu/isr.h"
#include"../src/ports.h"

void print_letter(uint8_t scancode){
  switch (scancode) {
    case 0x00:
      print_string("error");
      break;
    case 0x16:
      print_string("esc");
      break;
    case 0x02:
      print_string("1");
      break;
    case 0x41:
      print_string("2");
      break;

    default:
      if(scancode <= 0x7f){
        print_string("unknown key");
      } else if(scancode <= 0x39 + 0x80){
        print_string("key up");
      }else{
        print_string("unknown key");
      }
    break; 
  }
}

static void keyboard_callback(registers_t *regs){
  uint8_t scancode = port_byte_in(0x60);
  print_letter(scancode);
  print_string("hjello\n"); 
}


void init_keyboard(){
  register_interrupt_handler(IRQ1, keyboard_callback);
}
