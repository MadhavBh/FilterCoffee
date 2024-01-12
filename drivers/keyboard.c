#include <stdint.h>
#include"../src/vga.h"
#include"../cpu/idt.h"
#include"../cpu/isr.h"
#include"../src/ports.h"

void print_letter(uint8_t scancode){
  switch (scancode) {
    case 0x00:
      terminal_write_string("error");
      break;
    case 0x16:
      terminal_write_string("esc");
      break;
    case 0x02:
      terminal_write_string("1");
      break;
    case 0x41:
      terminal_write_string("2");
      break;

    default:
      if(scancode <= 0x7f){
        terminal_write_string("unknown key");
      } else if(scancode <= 0x39 + 0x80){
        terminal_write_string("key up");
      }else{
        terminal_write_string("unknown key");
      }
    break; 
  }
}

static void keyboard_callback(registers_t *regs){
  uint8_t scancode = port_byte_in(0x60);
  print_letter(scancode);
  terminal_write_string("hjello"); 
  terminal_new_line();
}


void init_keyboard(){
  register_interrupt_handler(IRQ1, keyboard_callback);
}
