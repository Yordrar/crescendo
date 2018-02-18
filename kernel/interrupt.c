#include "interrupt.h"
#include "../driver/tty.h"

void interrupt_handler(registers_t regs) {
    if(regs.int_num == 1000) {} // DELETE ME
    tty_putchar('P');
}