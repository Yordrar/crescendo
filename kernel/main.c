#include "multiboot.h"
#include "pio.h"
#include "gdt.h"
#include "idt.h"
#include "../driver/tty.h"

int kernel_main(multiboot_info_t* multiboot_data) {

    if((multiboot_data->flags & 0x40)) {
        tty_putchar('K');
    }

    gdt_init();
    idt_init();

    asm volatile("int $0x3");
    asm volatile("int $0x4");

    while(1) {
        for(int i = 0; i < 20000000; i++) {}

        tty_putchar('A');
    }
    
}