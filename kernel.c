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

static inline uint8_t vga_entry_color(enum vga_colours fg, enum vga_colours bg){
  return fg | bg << 4;
}

static inline uint16_t vga_entry(unsigned char uc, uint8_t color){
  return(uint16_t) uc | (uint16_t) color << 8;
}

