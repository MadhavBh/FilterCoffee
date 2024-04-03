#include"ports.h"
#include"../cpu/idt.h"
#include"../cpu/isr.h"
#include"utils.h"
#include"vga2.h"
#include"keyboard.h"
#include <stdint.h>

#define SC_MAX 59
#define BACKSPACE 0x0E
#define ENTER 0x1C
static char key_buffer[1024];

const char scanmap[] = {
  '?', '?', '1','2','3','4','5','6','7','8','9','0','-','=','?',' ',
  'Q','W','E','R','T','Y','U','I','O','P','[',']','|','?',
  'A','S','D','F','G','H','J','K','L',';','/','`','?','?','Z','X',
  'C','V','B','N','M',',','.','/','?','?','?',' '
};

static void keyboard_callback(registers_t *regs){
  uint8_t scancode = port_byte_in(0x60);
  if (scancode > SC_MAX) return;

  if(scancode == BACKSPACE){
    if(backspaceBuffer(key_buffer)){
      backspace();
    }
  }
  else if(scancode == ENTER){
    print_string("\n");
    handleCommand(key_buffer);
    key_buffer[0] = '\0';
  }
  else{
  char letter = scanmap[(int) scancode];
  append(key_buffer, letter);
  char str[2] = {letter,'\0'};
  print_string(str);
  }
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
  print_string("\n>> ");
}
