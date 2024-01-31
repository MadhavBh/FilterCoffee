
#include <stdint.h>
#include"../drivers/vga2.h"
#include"../cpu/idt.h"
#include"../cpu/isr.h"
#include"../drivers/ports.h"

void print_letter(uint8_t scancode){
  switch (scancode) {
    case 0x00:
      print_string("error");
      break;
    case 0x39:
      print_string(" ");
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
    case 0x04:
      print_string("3");
      break;
    case 0x05:
      print_string("4");
      break;
    case 0x06:
      print_string("5");
      break;
    case 0x07:
      print_string("6");
      break;
    case 0x08:
      print_string("7");
      break;
    case 0x09:
      print_string("8");
      break;
    case 0x0a:
      print_string("9");
      break;
    case 0x0b:
      print_string("0");
      break;
    case 0x0e:
      backspace();
      break;
    case 0x0f:
      print_string("    ");
      break;
    case 0x10:
      print_string("Q");
      break;
    case 0x11:
      print_string("W");
      break;
    case 0x12:
      print_string("E");
      break;
    case 0x13:
      print_string("R");
      break;
    case 0x14:
      print_string("T");
      break;
    case 0x15:
      print_string("Y");
      break;
    case 0x16:
      print_string("U");
      break;
    case 0x17:
      print_string("I");
      break;
    case 0x18:
      print_string("O");
      break;
    case 0x19:
      print_string("P");
      break;
    case 0x1a:
      print_string("[");
      break;
    case 0x1b:
      print_string("]");
      break;
    case 0x1c:
      print_string("\n");
      break;
    case 0x1e:
      print_string("A");
      break;
    case 0x1f:
      print_string("S");
      break;
    case 0x20:
      print_string("D");
      break;
    case 0x21:
      print_string("F");
      break;
    case 0x22:
      print_string("G");
      break;
    case 0x23:
      print_string("H");
      break;
    case 0x24:
      print_string("J");
      break;
    case 0x25:
      print_string("K");
      break;
    case 0x26:
      print_string("L");
      break;
    case 0x27:
      print_string(";");
      break;
    case 0x28:
      print_string("'");
      break;
    case 0x2c:
      print_string("Z");
      break;
    case 0x2d:
      print_string("X");
      break;
    case 0x2e:
      print_string("C");
      break;
    case 0x2f:
      print_string("V");
      break;
    case 0x30:
      print_string("B");
      break;
    case 0x31:
      print_string("N");
      break;
    case 0x32:
      print_string("M");
      break;
    case 0x33:
      print_string("<");
      break;
    case 0x34:
      print_string(">");
      break;
    case 0x35:
      print_string("/");
      break;    
    default:
      if(scancode <= 0x7f){
        print_string("unknown key\n");
      }else if(scancode <= 0x39 +0x80 ){
        //print_string("key up\n");
        //print_letter(scancode-0x80);
      }else{
        print_string("unknown key");
      }
    break; 
  }
}
static void keyboard_callback(registers_t *regs){
  uint8_t scancode = port_byte_in(0x60);
  print_letter(scancode);
}

void flush_keyboard_buffer(){
  uint8_t status;
  uint8_t data;

  while((port_byte_in(0x64) & 0x01) != 0 ){
    data = port_byte_in(0x60);
  }
}

void init_keyboard(){
  flush_keyboard_buffer();
  print_string("in init keyboard\n");
  register_interrupt_handler(IRQ1, keyboard_callback);
  //uint8_t scancode = port_byte_in(0x60);
  //print_letter(scancode);
}
