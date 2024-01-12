#include"idt.h"
#include"../drivers/vga.h"
#define low_16(address)(uint16_t)((address) & 0xFFFF)
#define high_16(address)(uint16_t)(((address)>>16) & 0xFFFF)

idt_gate_t idt[256];

idt_register_t idt_reg;


void set_idt_gate(int n, uint32_t handler){
  idt[n].low_offset = low_16(handler);
  idt[n].selector = kernel_cs;
  idt[n].alwayszero = 0;
  idt[n].flags = 0x8E;
  idt[n].high_offset = high_16(handler);
}

void load_idt(){
  idt_reg.base = (uint32_t) &idt;
  idt_reg.limit = 256 * sizeof(idt_gate_t) - 1;

  asm volatile("lidt (%0)" : : "r"(&idt_reg));
  terminal_write_string("IDT loaded..\n");
}

