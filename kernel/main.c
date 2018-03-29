#include "multiboot.h"
#include "panic.h"

#include "../arch/pio.h"
#include "../arch/gdt.h"
#include "../arch/idt.h"
#include "../arch/pit.h"
#include "../driver/tty.h"
#include "../driver/keyboard.h"

int kernel_main(multiboot_info_t* multiboot_data, int magic) {

    if((multiboot_data->flags & MULTIBOOT_INFO_MEM_MAP) && magic == MULTIBOOT_BOOTLOADER_MAGIC) {
        tty_putchar('K');
    }

    gdt_init();
    idt_init();

    pit_init(1000);

    keyboard_init();

    asm volatile("sti");

    while(1) {
        
    }
    
}