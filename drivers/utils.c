#include <stdbool.h>
#include <stdint.h>
#include"utils.h"
#include "vga2.h"

//returns less than 0 if s < d, 0 is s==d, more than 0 if s > d
int compare_string(char s[],char d[]){
  int i; 
  for(i = 0; s[i] == d[i]; i++){
    if(s[i] == '\0') return 0;
  }
  return s[i] - d[i];
}

int string_len(char s[]){
  int i = 0;
  while(s[i] != '\0'){
    i++;
  }
  return i;
}

void append(char s[], char n){
  int len = string_len(s);
  s[len] = n;
  s[len+1] = '\0';
}

bool backspaceBuffer(char s[]){
  int len = string_len(s);
  if(len > 0){
    s[len-1] = '\0';
    return true;
  }
  else {
    return false;
  }
}

void execute(char *input){
  if(compare_string(input, "HELLO") == 0){
    print_string("Hello ji kya haal hai");
    print_string("\n>> ");
  }
  else if(compare_string(input, "EXIT") == 0){
    print_string("Halting the CPU..\n");
    asm volatile("hlt");
  }
  else if(compare_string(input, "CLEAR")==0){
    clear_screen();
    print_string("\n>> ");
  }
  else if(compare_string(input, "") == 0){
    print_string("\n>> ");
  }
  else{
    print_string("unknown command: ");
    print_string(input);
    print_string("\n>> ");
  }
}
