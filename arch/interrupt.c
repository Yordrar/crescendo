#include "interrupt.h"
#include "cpu.h"
#include "pio.h"

#include "../driver/cga.h"

isr_t interrupt_handlers[256] = {0};

void interrupt_register_handler(unsigned char n, isr_t handler) {
  interrupt_handlers[n] = handler;
}

void interrupt_generic_handler(interrupt_frame_t frame) {
	if (interrupt_handlers[frame.int_num] != 0) {
		isr_t handler = interrupt_handlers[frame.int_num];
		handler(frame);
	}
	else {
		cga_write("unhandled interrupt received");
		cga_print_num(frame.int_num);
	}
	if(frame.int_num > 31) {
		// Send an EOI (end of interrupt) signal to the PICs
		
		// If this interrupt involved the slave
		if (frame.int_num >= 40) {
			// Send reset signal to slave
			pio_write_byte(0xA0, 0x20);
		}
		// Send reset signal to master
		pio_write_byte(0x20, 0x20);
	}
}