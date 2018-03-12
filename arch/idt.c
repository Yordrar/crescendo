#include "idt.h"
#include "interrupt.h"
#include "pio.h"

void memset(unsigned char* dest, unsigned char val, unsigned int len) {
    unsigned char *temp = (unsigned char*)dest;
    for ( ; len != 0; len--) *temp++ = val;
}

void idt_init(void) {
    idt_ptr.address = (unsigned int)&idt;
    idt_ptr.size = (sizeof(idt_entry_t) * IDT_ENTRIES) - 1;

    memset((unsigned char*)&idt, 0, sizeof(idt_entry_t)*256);

    idt_set_entry(0, (unsigned int)isr0, 0x08, 0x8E);
    idt_set_entry(1, (unsigned int)isr1, 0x08, 0x8E);
    idt_set_entry(2, (unsigned int)isr2, 0x08, 0x8E);
    idt_set_entry(3, (unsigned int)isr3, 0x08, 0x8E);
    idt_set_entry(4, (unsigned int)isr4, 0x08, 0x8E);
    idt_set_entry(5, (unsigned int)isr5, 0x08, 0x8E);
    idt_set_entry(6, (unsigned int)isr6, 0x08, 0x8E);
    idt_set_entry(7, (unsigned int)isr7, 0x08, 0x8E);
    idt_set_entry(8, (unsigned int)isr8, 0x08, 0x8E);
    idt_set_entry(9, (unsigned int)isr9, 0x08, 0x8E);
    idt_set_entry(10, (unsigned int)isr10, 0x08, 0x8E);
    idt_set_entry(11, (unsigned int)isr11, 0x08, 0x8E);
    idt_set_entry(12, (unsigned int)isr12, 0x08, 0x8E);
    idt_set_entry(13, (unsigned int)isr13, 0x08, 0x8E);
    idt_set_entry(14, (unsigned int)isr14, 0x08, 0x8E);
    idt_set_entry(15, (unsigned int)isr15, 0x08, 0x8E);
    idt_set_entry(16, (unsigned int)isr16, 0x08, 0x8E);
    idt_set_entry(17, (unsigned int)isr17, 0x08, 0x8E);
    idt_set_entry(18, (unsigned int)isr18, 0x08, 0x8E);
    idt_set_entry(19, (unsigned int)isr19, 0x08, 0x8E);
    idt_set_entry(20, (unsigned int)isr20, 0x08, 0x8E);
    idt_set_entry(21, (unsigned int)isr21, 0x08, 0x8E);
    idt_set_entry(22, (unsigned int)isr22, 0x08, 0x8E);
    idt_set_entry(23, (unsigned int)isr23, 0x08, 0x8E);
    idt_set_entry(24, (unsigned int)isr24, 0x08, 0x8E);
    idt_set_entry(25, (unsigned int)isr25, 0x08, 0x8E);
    idt_set_entry(26, (unsigned int)isr26, 0x08, 0x8E);
    idt_set_entry(27, (unsigned int)isr27, 0x08, 0x8E);
    idt_set_entry(28, (unsigned int)isr28, 0x08, 0x8E);
    idt_set_entry(29, (unsigned int)isr29, 0x08, 0x8E);
    idt_set_entry(30, (unsigned int)isr30, 0x08, 0x8E);
    idt_set_entry(31, (unsigned int)isr31, 0x08, 0x8E);

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

    idt_set_entry(32, (unsigned int)irq0, 0x08, 0x8E);
    idt_set_entry(33, (unsigned int)irq1, 0x08, 0x8E);
    idt_set_entry(34, (unsigned int)irq2, 0x08, 0x8E);
    idt_set_entry(35, (unsigned int)irq3, 0x08, 0x8E);
    idt_set_entry(36, (unsigned int)irq4, 0x08, 0x8E);
    idt_set_entry(37, (unsigned int)irq5, 0x08, 0x8E);
    idt_set_entry(38, (unsigned int)irq6, 0x08, 0x8E);
    idt_set_entry(39, (unsigned int)irq7, 0x08, 0x8E);
    idt_set_entry(40, (unsigned int)irq8, 0x08, 0x8E);
    idt_set_entry(41, (unsigned int)irq9, 0x08, 0x8E);
    idt_set_entry(42, (unsigned int)irq10, 0x08, 0x8E);
    idt_set_entry(43, (unsigned int)irq11, 0x08, 0x8E);
    idt_set_entry(44, (unsigned int)irq12, 0x08, 0x8E);
    idt_set_entry(45, (unsigned int)irq13, 0x08, 0x8E);
    idt_set_entry(46, (unsigned int)irq14, 0x08, 0x8E);

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