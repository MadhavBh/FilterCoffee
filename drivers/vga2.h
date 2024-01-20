#pragma once

void video_mem_cp(char *source, char *dest, int nbytes);
void set_cursor(int offset);
int get_cursor();
int get_row_from_offset(int offset);
int get_offset(int col, int row);
int move_offset_Newline(int offset);
void set_char_at_video_mem(char character, int offset);
int scroll(int offset);
void clear_screen();
void print_string(char *string);




