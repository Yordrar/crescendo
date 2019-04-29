#include <kernel/multiboot.h>
#include <kernel/panic.h>
#include <kernel/process.h>
#include <kernel/memory.h>

#include <arch/pio.h>
#include <arch/cpu.h>
#include <arch/pit.h>
#include <driver/cga.h>
#include <driver/keyboard.h>

void kernel_main(multiboot_info_t* multiboot_data, int magic) {
	if(magic == MULTIBOOT_BOOTLOADER_MAGIC && (multiboot_data->flags & MULTIBOOT_INFO_MEM_MAP)) {
		cga_write("Multiboot correct\n");
	}
	else {
		kernel_panic("PANIC: Booted from a non-multiboot bootloader or no memory map is available");
	}

	memory_init();
	cpu_init();
	pit_init();
	keyboard_init();
	
	cpu_enable_interrupts();
	
	kernel_panic("PANIC: Attempting to exit kernel_main");
}