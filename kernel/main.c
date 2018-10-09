#include "multiboot.h"
#include "panic.h"
#include "process.h"

#include "../arch/pio.h"
#include "../arch/cpu.h"
#include "../arch/pit.h"
#include "../driver/fb.h"
#include "../driver/keyboard.h"

int kernel_main(multiboot_info_t* multiboot_data, int magic) {
    if((multiboot_data->flags & MULTIBOOT_INFO_MEM_MAP) && magic == MULTIBOOT_BOOTLOADER_MAGIC) {
        fb_write("Multiboot correct\n");
    }
    else {
        kernel_panic("PANIC: booted from a non-multiboot bootloader");
    }

    cpu_init();
    pit_init(200);
    keyboard_init();
    
    cpu_enable_interrupts();
    while(1) {
        
    }
    kernel_panic("PANIC: Attempting to exit kernel_main");
}