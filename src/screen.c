#include "screen.h"
#include "io.h"

char _cX = 0;
char _cY = 0;

char screen_width()
{
        return 80;
}
char screen_height()
{
        return 25;
}

void fill()
{
        unsigned char* video;
        unsigned char* limit = (unsigned char*) 0xB8FA0;
        video = (unsigned char*) 0xB8000;
        while (video < limit) {
                *video = ' ';
                video++;
                *video = 0x1F;
                video++;
        }
}

unsigned char* cursor (char x, char y)
{
        unsigned char* ptr = (unsigned char*) 0xB8000 + x * 0x02 +  2 * y * screen_width();
        return ptr;
}

unsigned char* lim_cursor()
{
        return (unsigned char*) SCREENLIMIT;
}

void set_curr_cursor(char x, char y)
{
        _cX = x;
        _cY = 0;
}

int is_cursor_oob(unsigned char* cursor)
{
        return cursor > lim_cursor();
}

unsigned char* curr_cursor()
{
        return cursor(_cX, _cY);
}

void nl_cursor()
{
        _cY += 1;
        _cX = 0;
}
void next_curr_cursor()
{       
        _cX += 1;
        if (_cX > screen_width()) {
                _cX = 0;
                _cY += 1;
        }
}

void update_cursor()
{
        unsigned char pos = 0xB8000 + _cX  + _cY * screen_width();
	outb(0x3D4, 0x0F);
	outb(0x3D5, (unsigned char) (pos & 0xFF));
	outb(0x3D4, 0x0E);
	outb(0x3D5, (unsigned char) ((pos >> 8) & 0xFF));
}

void print(const char* string)
{
        unsigned char* video;
   
        while( *string != 0 )
        {
                video = curr_cursor();

                if (is_cursor_oob(video) == 1) set_curr_cursor(0, 0);
                
                if (*string == '\n') {
                        nl_cursor();
                } else if (*string == '\t') {
                        next_curr_cursor();
                        next_curr_cursor();
                        next_curr_cursor();
                        next_curr_cursor();
                } else {
                        *video = *string;
                        video++;
                        *video = 0x1F;
                        string++;
                        video++;
                        next_curr_cursor();                      
                }
        }
        update_cursor();
}

void printnl(const char *string)
{
        print(string);
        nl_cursor();
        update_cursor();
}

void log_info(const char *string) 
{
        print("[INFO] ");
        printnl(string);
}