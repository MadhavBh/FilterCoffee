#include <stdint.h>
#include"ports.h"

unsigned char port_byte_in(unsigned short port){
  unsigned char result;

  asm("in %%dx,%%al" : "=a"(result) : "d"(port));
  return result;
}

void port_byte_out(unsigned short port, uint8_t data){
  asm("out %%al, %%dx" : : "a" (data), "d" (port));
}
