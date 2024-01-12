#pragma once



void set_gdt_gate(int num,unsigned long base, unsigned long limit,unsigned char access,unsigned char gran );

//extern void set_gdt_gate(unsigned char num, unsigned long base, unsigned short sel, unsigned char flags);
void init_gdt();

