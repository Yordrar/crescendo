#include "interrupt.h"
#include "../driver/tty.h"
#include "pio.h"

isr_t interrupt_handlers[256];

void register_interrupt_handler(unsigned char n, isr_t handler)
{
  interrupt_handlers[n] = handler;
}

void interrupt_handler(registers_t regs) {
    if(regs.int_num == 1000) {} // DELETE ME
    tty_putchar('P');
}

void irq_handler(registers_t regs) {
    if (interrupt_handlers[regs.int_num] != 0) {
        isr_t handler = interrupt_handlers[regs.int_num];
        handler(regs);
    }
    // Send an EOI (end of interrupt) signal to the PICs.
    // If this interrupt involved the slave.
    if (regs.int_num >= 40) {
        // Send reset signal to slave.
        pio_write_byte(0xA0, 0x20);
    }
    // Send reset signal to master. (As well as slave, if necessary).
    pio_write_byte(0x20, 0x20);
}