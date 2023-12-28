#include<stdbool.h>
#include<stddef.h>
#include<stdint.h>
#include"vga.h"

#if defined(__Linux__)
#error "You are not using a cross-compiler,files not compiled targeting the required architecture"
#endif

#if ! defined(__i386__)
#error "compile with an ix86-elf compiler"
#endif

static const size_t vga_width = 80;
static const size_t vga_height = 25;

size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint16_t* terminal_buffer;

enum vga_colours{
  VGA_C_BLACK = 0,
  VGA_C_WHITE = 15
};

static inline uint8_t vga_entry_color(enum vga_colours fg, enum vga_colours bg){  //appending the dual 4 bit VGA color entry values into a singular 8 bit value
  return fg | bg << 4;
}

static inline uint16_t vga_entry(unsigned char uc, uint8_t color){
  return(uint16_t) uc | (uint16_t) color << 8;
}

size_t strlen(const char* str){
  size_t len = 0;
  while(str[len]){len++;}
  return len;
}

void terminal_init(void){
  terminal_row = 0;
  terminal_column = 0;

  terminal_color = vga_entry_color(VGA_C_WHITE,VGA_C_BLACK);
  terminal_buffer = (uint16_t*) 0xB8000;
  for(size_t y = 0; y < vga_height; y++){
    for(size_t x = 0; x < vga_width; x++){
      const size_t index = y * vga_width + x;
      terminal_buffer[index] = vga_entry(' ', terminal_color);
    }
  }
}

void terminal_setcolor(uint8_t color){
  terminal_color = color;
}

void terminal_put_entry(char c, uint8_t color, size_t x, size_t y){
  const size_t index = y * vga_width + x;
  terminal_buffer[index] = vga_entry(c, color);
}

void terminal_putchar(char c){
  terminal_put_entry(c, terminal_color, terminal_column, terminal_row);
  if(c ==  '\n'){
    terminal_row++;
    terminal_column = 0;
  }
  if(++terminal_column == vga_width){
    terminal_column = 0;
    if(++terminal_row == vga_height){
      terminal_row = 0;
    }
  }
}

void terminal_write(const char* data, size_t size){
  for(size_t i = 0; i < size; i++){
    terminal_putchar(data[i]);
  }
}
void terminal_new_line(){
  terminal_putchar('\n');
}
void terminal_write_string(const char* data){
  terminal_write(data, strlen(data));
}

//void terminal_main(void){
//  terminal_init();
//  terminal_write_string("Hello from the kernel ");
//  terminal_new_line();
//  terminal_new_line();
//  terminal_write_string("hello from the other line ");
//}




