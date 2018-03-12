#include "multiboot.h"
#include "../arch/pio.h"
#include "../arch/gdt.h"
#include "../arch/idt.h"
#include "../arch/pit.h"
#include "../driver/tty.h"
#include "../driver/keyboard.h"

void kernel_main(multiboot_info_t* multiboot_data, int magic) {

    if(multiboot_data->flags & 0x40 || magic == 0x2BADB002) {
        tty_putchar('K');
    }

    gdt_init();
    idt_init();

    pit_init(1000);

    keyboard_init();

    __asm__ __volatile__("sti");

    while(1) {
        
    }
    
}