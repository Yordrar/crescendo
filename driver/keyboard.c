#include "keyboard.h"
#include "cga.h"

#include "../arch/interrupt.h"
#include "../arch/pio.h"
#include "../arch/cpu.h"

void keyboard_callback(interrupt_frame_t regs) {
    if(regs.eax == 0) {} // DELETE ME
    char c = pio_read_byte(0x60);
    if(c == 0x1E) {
        cga_putchar('A');
    }
    if(c == 0x1F) {
        cga_clear();
    }
}

void keyboard_init(void) {
    interrupt_register_handler(IRQ1, &keyboard_callback);
}