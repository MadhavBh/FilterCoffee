#include<stdbool.h>
#include<stddef.h>
#include<stdint.h>


#if defined(__Liux__)
#error "You are not using a cross-compiler,files not compiled targeting the required architecture"
#endif

#if ! defined(__i386__)
#error "compile with an ix86-elf compiler"
#endif


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

static const size_t vga_width = 80;
static const size_t vga_height = 25;

size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint16_t* terminal_buffer;

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








