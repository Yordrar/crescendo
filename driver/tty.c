#include "tty.h"
#include "../kernel/io.h"

#define FB_IOPORT_COMMAND 0x3D4
#define FB_IOPORT_DATA 0x3D5

#define FB_CURSOR_POS_COMMAND_HIGHBYTE 14
#define FB_CURSOR_POS_COMMAND_LOWBYTE 15

char* fb_memory = (char*)0xB8000;
unsigned short int fb_cursor_pos = 0;
char fb_current_color = 0x07; // First 4 bytes is BG and second 4 bytes is FG

void tty_write(unsigned char c) {
    fb_memory[fb_cursor_pos] = c;
    fb_memory[fb_cursor_pos + 1] = fb_current_color;

    fb_cursor_pos++;

    io_write(FB_IOPORT_COMMAND, FB_CURSOR_POS_COMMAND_HIGHBYTE);
    io_write(FB_IOPORT_DATA, fb_cursor_pos >> 8);
    io_write(FB_IOPORT_COMMAND, FB_CURSOR_POS_COMMAND_LOWBYTE);
    io_write(FB_IOPORT_DATA, fb_cursor_pos & 0x00FF);
}