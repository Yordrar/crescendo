#include "idt.h"
#include "interrupt.h"
#include "pio.h"

#define IDT_ENTRIES 256

struct lidt_struct {
    unsigned short int size;
    unsigned int address;
}__attribute__((packed));
typedef struct lidt_struct lidt_struct_t;

struct idt_entry {
    unsigned short int base_low;  // The lower 16 bits of the address to jump to.
    unsigned short int selector;  // Kernel segment selector.
    unsigned char  always_zero;   // This must always be zero.
    unsigned char  flags;         // More flags. See documentation.
    unsigned short int base_high; // The upper 16 bits of the address to jump to.
} __attribute__((packed));
typedef struct idt_entry idt_entry_t;

idt_entry_t idt[IDT_ENTRIES] = {0};
lidt_struct_t idt_ptr;

void idt_init(void) {
    idt_ptr.address = (unsigned int)idt;
    idt_ptr.size = sizeof(idt) - 1;

    // Remap the irq table.
    pio_write_byte(0x20, 0x11);
    pio_write_byte(0xA0, 0x11);
    pio_write_byte(0x21, 0x20);
    pio_write_byte(0xA1, 0x28);
    pio_write_byte(0x21, 0x04);
    pio_write_byte(0xA1, 0x02);
    pio_write_byte(0x21, 0x01);
    pio_write_byte(0xA1, 0x01);
    pio_write_byte(0x21, 0x0);
    pio_write_byte(0xA1, 0x0);

    for(int i = 0; i < 47; i++) {
        idt_set_entry(i, (unsigned int)interrupt_routines[i], 0x08, 0x8E);
    }
    for(int i = 47; i < 256; i++) {
        idt_set_entry(i, 0, 0, 0);
    }

    idt_loadidt((unsigned int)&idt_ptr);
}

void idt_set_entry(unsigned char num, unsigned int base, unsigned short int selector, unsigned char flags){
    idt[num].base_low  = base & 0xFFFF;
    idt[num].base_high = (base >> 16) & 0xFFFF;

    idt[num].selector    = selector;
    idt[num].always_zero = 0;
    // We must uncomment the OR below when we get to using user-mode.
    // It sets the interrupt gate's privilege level to 3.
    idt[num].flags = flags /* | 0x60 */;
}