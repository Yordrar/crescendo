#include "cga.h"
#include "../arch/pio.h"

#define cga_PORT_COMMAND 0x03D4
#define cga_PORT_DATA 0x03D5

#define cga_CURSOR_POS_COMMAND_HIGHBYTE 14
#define cga_CURSOR_POS_COMMAND_LOWBYTE 15

char* cga_memory = (char*)0x0B8000; // 80 x 25, so it ends at 0x0B8FA0
unsigned short int cga_cursor_pos = 0;
char cga_current_color = 0x07; // First 4 bytes is BG and second 4 bytes is FG (big endian)

void cga_update_cursor_pos() {
	pio_write_byte(cga_PORT_COMMAND, cga_CURSOR_POS_COMMAND_HIGHBYTE);
	pio_write_byte(cga_PORT_DATA, cga_cursor_pos >> 8);
	pio_write_byte(cga_PORT_COMMAND, cga_CURSOR_POS_COMMAND_LOWBYTE);
	pio_write_byte(cga_PORT_DATA, cga_cursor_pos & 0x00FF);
}

void cga_newline() {
	cga_cursor_pos++;
	while(cga_cursor_pos % 80 != 0) {
		cga_cursor_pos++;
	}
	cga_update_cursor_pos();
}

void cga_putchar(unsigned char c) {
	if(c == '\n') {
		cga_newline();
		return;
	}
	cga_memory[2 * cga_cursor_pos] = c;
	cga_memory[2 * cga_cursor_pos + 1] = cga_current_color;

	cga_cursor_pos++;

	cga_update_cursor_pos();
}

void cga_clear(void) {
	for(int i = 0; i < 80*25; i++) {
		cga_memory[2 * i] = 0;
		cga_memory[2 * i + 1] = 0;
	}
	cga_cursor_pos = 0;
	cga_update_cursor_pos();
}

void cga_write(const char* msg) {
	for(int i = 0; msg[i] != '\0'; i++) {
		cga_putchar(msg[i]);
	}
}

void cga_print_num(unsigned int num) {
	cga_write("0x");
	char num_str[8] = {0};
	for(int i = 1; i <= 8; i++) {
		switch(num & 0xF) {
			case 0:
				num_str[8-i] = '0';
				break;
			case 1:
				num_str[8-i] = '1';
				break;
			case 2:
				num_str[8-i] = '2';
				break;
			case 3:
				num_str[8-i] = '3';
				break;
			case 4:
				num_str[8-i] = '4';
				break;
			case 5:
				num_str[8-i] = '5';
				break;
			case 6:
				num_str[8-i] = '6';
				break;
			case 7:
				num_str[8-i] = '7';
				break;
			case 8:
				num_str[8-i] = '8';
				break;
			case 9:
				num_str[8-i] = '9';
				break;
			case 0xA:
				num_str[8-i] = 'A';
				break;
			case 0xB:
				num_str[8-i] = 'B';
				break;
			case 0xC:
				num_str[8-i] = 'C';
				break;
			case 0xD:
				num_str[8-i] = 'D';
				break;
			case 0xE:
				num_str[8-i] = 'E';
				break;
			case 0xF:
				num_str[8-i] = 'F';
				break;
		}
		num >>= 4;
	}
	cga_write(num_str);
	cga_putchar('\n');
}