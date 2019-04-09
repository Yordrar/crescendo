#include "panic.h"

#include "../driver/cga.h"

void kernel_panic(const char* msg) {
	cga_write(msg);

	while(1) {
		asm volatile("cli");
		asm volatile("hlt");
	}
	
}