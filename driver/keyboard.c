#include "keyboard.h"
#include "tty.h"
#include "../kernel/interrupt.h"
#include "../kernel/pio.h"

void keyboard_callback(registers_t regs) {
    char c = pio_read_byte(0x60);
    if(c == 0x1E) {
        tty_putchar('A');
    }
}

void keyboard_init(void) {
    register_interrupt_handler(IRQ1, &keyboard_callback);
}