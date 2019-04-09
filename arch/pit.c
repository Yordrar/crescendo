#include "pit.h"
#include "interrupt.h"
#include "pio.h"
#include "cpu.h"

#include "../driver/cga.h"
#include "../kernel/process.h"

#define PIT_FREQUENCY 200

unsigned int tick = 0;

static void pit_callback(interrupt_frame_t frame) {
	if(frame.int_num == 0) {} //DELETE ME
}

void pit_init()
{
	//Register the timer callback.
	interrupt_register_handler(IRQ0, &pit_callback);

	//The value we send to the PIT is the value to divide it's input clock
	//(1193180 Hz) by to get our required frequency. Important to note is
	//that the divisor must be small enough to fit into 16-bits.
	unsigned int divisor = 1193180 / PIT_FREQUENCY;

	//Send the command byte.
	pio_write_byte(0x43, 0x36);

	//Divisor has to be sent byte-wise, so split here into upper/lower bytes.
	unsigned char low = (unsigned char)(divisor & 0xFF);
	unsigned char high = (unsigned char)((divisor>>8) & 0xFF);

	//Send the frequency divisor.
	pio_write_byte(0x40, low);
	pio_write_byte(0x40, high);
}