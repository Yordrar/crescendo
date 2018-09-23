#include "keyboard.h"
#include "fb.h"

#include "../arch/interrupt.h"
#include "../arch/pio.h"
#include "../arch/cpu.h"

void keyboard_callback(interrupt_frame_t regs) {
    if(regs.eax == 0) {} // DELETE ME
    char c = pio_read_byte(0x60);
    if(c == 0x1E) {
        fb_putchar('A');
    }
    if(c == 0x1F) {
        fb_clear();
    }
}

void keyboard_init(void) {
    register_interrupt_handler(IRQ1, &keyboard_callback);
}