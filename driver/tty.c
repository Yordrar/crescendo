#include "tty.h"
#include "../kernel/pio.h"

#define FB_IOPORT_COMMAND 0x03D4
#define FB_IOPORT_DATA 0x03D5

#define FB_CURSOR_POS_COMMAND_HIGHBYTE 14
#define FB_CURSOR_POS_COMMAND_LOWBYTE 15

char* fb_memory = (char*)0x0B8000; // 80 x 25, so it ends at 0x0B8FA0
unsigned short int fb_cursor_pos = 0;
char fb_current_color = 0x07; // First 4 bytes is BG and second 4 bytes is FG (big endian)

void tty_putchar(unsigned char c) {
    fb_memory[2 * fb_cursor_pos] = c;
    fb_memory[2 * fb_cursor_pos + 1] = fb_current_color;

    fb_cursor_pos++;

    pio_write_byte(FB_IOPORT_COMMAND, FB_CURSOR_POS_COMMAND_HIGHBYTE);
    pio_write_byte(FB_IOPORT_DATA, fb_cursor_pos >> 8);
    pio_write_byte(FB_IOPORT_COMMAND, FB_CURSOR_POS_COMMAND_LOWBYTE);
    pio_write_byte(FB_IOPORT_DATA, fb_cursor_pos & 0x00FF);
}