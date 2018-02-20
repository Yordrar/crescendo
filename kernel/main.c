#include "multiboot.h"
#include "pio.h"
#include "gdt.h"
#include "idt.h"
#include "pit.h"
#include "../driver/tty.h"
#include "../driver/keyboard.h"

int kernel_main(multiboot_info_t* multiboot_data) {

    if((multiboot_data->flags & 0x40)) {
        tty_putchar('K');
    }

    gdt_init();
    idt_init();

    pit_init(10);

    keyboard_init();

    asm volatile("int $0x03");
    asm volatile("int $0x04");

    asm volatile("sti");

    while(1) {
        
    }
    
}