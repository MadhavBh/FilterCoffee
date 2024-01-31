#include <stdint.h>
#define VGA_CTRL_REG 0x3d4 
#define VGA_DATA_REG 0x3d5 
#define VGA_OFFSET_LOW 0x0f
#define VGA_OFFSET_HIGH 0x0e
#define VIDEO_ADD 0xb8000
#define MAX_ROWS 25
#define MAX_COL 80 
#define WHITE_ON_BLACK 0x0f
#include "../src/ports.h"
#include "vga2.h"

void video_mem_cp(char *source, char *dest, int nbytes){
  int i;
  for( i = 0; i < nbytes; i++){
    *(dest + i) = *(source + i);
  }
}


void set_cursor(int offset){
  offset /= 2;
  port_byte_out(VGA_CTRL_REG, VGA_OFFSET_HIGH);
  port_byte_out(VGA_DATA_REG, (unsigned char) (offset >> 8));
  port_byte_out(VGA_CTRL_REG, VGA_OFFSET_LOW);
  port_byte_out(VGA_DATA_REG, (unsigned char)(offset & 0xff));
}

int get_cursor(){
  port_byte_out(VGA_CTRL_REG, VGA_OFFSET_HIGH);
  int offset = port_byte_in(VGA_DATA_REG) << 8;
  port_byte_out(VGA_CTRL_REG, VGA_OFFSET_LOW);
  offset += port_byte_in(VGA_DATA_REG);
  return offset * 2;
}

int get_row_from_offset(int offset){
  return offset / (2 * MAX_COL);
}

int get_offset(int col, int row){
  return 2 * (row * MAX_COL + col);
}

int move_offset_Newline(int offset){
  return get_offset(0, get_row_from_offset(offset) + 1);
}

void set_char_at_video_mem(char character, int offset){
  uint8_t *vidmem = (uint8_t*) VIDEO_ADD;
  vidmem[offset]= character;
  vidmem[offset + 1] = WHITE_ON_BLACK;
}

int scroll(int offset){
  video_mem_cp((uint8_t *) (get_offset(0,1) + VIDEO_ADD),
               (uint8_t *) (get_offset(0,0) + VIDEO_ADD),
               MAX_COL * (MAX_ROWS - 1) *2);

  for (int col = 0; col < MAX_COL ; col++){
    set_char_at_video_mem(' ', get_offset(col, MAX_ROWS - 1));
  }
  return offset - 2 * MAX_COL; 
}

void print_string(char *string){
  int offset = get_cursor();
  int i = 0;
  while(string[i] != 0){
    if(offset >= MAX_ROWS * MAX_COL * 2){
      offset = scroll(offset);
    }
    if (string[i] == '\n'){
      offset = move_offset_Newline(offset);
    }
    else{
      set_char_at_video_mem(string[i], offset);
      offset +=2;
    }
    i++;
  }
  set_cursor(offset);
}

void clear_screen(){
  for(int i = 0; i < MAX_COL * MAX_ROWS; ++i){
    set_char_at_video_mem(' ', i*2);
  }
  set_cursor(get_offset(0 , 0));
}




