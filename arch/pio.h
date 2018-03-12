#ifndef _PIO_H_
#define _PIO_H_

char pio_read_byte(unsigned short int port);
void pio_write_byte(unsigned short int port, char byte);

unsigned short int pio_read_word(unsigned short int port);
void pio_write_word(unsigned short int port, unsigned short int byte);

#endif // io.h