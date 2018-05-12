#ifndef __SCREEN__
#define __SCREEN__

#define RAMSCREEN 0xB8000
#define SCREENSIZE 0XFA0
#define SCREENLIMIT 0xB8FA0

char screen_width();
char screen_height();
void fill();

int is_cursor_oob(unsigned char* cursor);

unsigned char* cursor (char x, char y);
unsigned char* lim_cursor();
void set_curr_cursor(char x, char y);

unsigned char* curr_cursor();
void nl_cursor();
void next_curr_cursor();
void printc(char c);
void print(const char* string);
void printnl(const char* string);

void log_info(const char* string);
#endif