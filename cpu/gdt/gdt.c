#include"gdt.h"
#include"../../drivers/vga2.h"
#include <stdint.h>
//#include <sys/types.h>

struct gdt_entry{
  unsigned short limit_low;
  unsigned short base_low;
  unsigned char base_middle;
  unsigned char access;
  unsigned char granularity; 
  unsigned char base_high;
}__attribute__((packed));


struct gdt_pointer{
  unsigned short limit;
  unsigned int base;
}__attribute__((packed));

struct gdt_entry gdt[3];
struct gdt_pointer gdtptr;

//extern void flush_gdt(unsigned char gdtptr);
extern void flush_gdt();

void set_gdt_gate(int num, unsigned long base, unsigned long limit,unsigned char access,unsigned char gran){
  gdt[num].base_low = (base & 0xFFFF);
 gdt[num].base_middle = (base >> 16) & 0xFF;
  gdt[num].base_high = (base >> 24) & 0xFF;

  gdt[num].limit_low = (limit & 0xFFFF);
  gdt[num].granularity = (limit >> 16) & 0x0F;
  gdt[num].granularity |= (gran & 0xF0);

  gdt[num].access = access;
}

void init_gdt(){
  gdtptr.limit = (sizeof(struct gdt_entry) * 3) - 1;
  gdtptr.base = (uint32_t)&gdt;

  print_string("setting up kernel segments \n");
  set_gdt_gate(0, 0, 0, 0, 0); //Null segment
  set_gdt_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xDF); //Code segment
  set_gdt_gate(2, 0, 0xFFFFFFFF, 0x92, 0xDF); //data segment
  print_string("kernel segments have been setup hehehhehehe\n");
  //flush_gdt((unsigned char)&gdtptr);
  flush_gdt();
}




