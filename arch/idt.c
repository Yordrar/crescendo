#include "idt.h"
#include "interrupt.h"
#include "pio.h"

#define IDT_ENTRIES 256

struct idt_entry {
    unsigned short int base_low;  //The lower 16 bits of the address to jump to.
    unsigned short int selector;  //Kernel segment selector.
    unsigned char  always_zero;   //This must always be zero.
    unsigned char  flags;         //Flags. See documentation.
    unsigned short int base_high; //The upper 16 bits of the address to jump to.
} __attribute__((packed));
typedef struct idt_entry idt_entry_t;

idt_entry_t idt[IDT_ENTRIES] = {0};

static inline void
lidt(idt_entry_t *p, int size)
{
  volatile unsigned short int pd[3];

  pd[0] = size-1;
  pd[1] = (unsigned int)p;
  pd[2] = (unsigned int)p >> 16;

  asm volatile("lidt (%0)" : : "r" (pd));
}

void idt_init(void) {
    // Remap the irq table of the PICs
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

    for(int i = 0; i < 48; i++) {
        idt_set_entry(i, interrupt_routines[i], 0x08, 0x8E);
    }

    lidt((unsigned int)idt, sizeof(idt));
}

void idt_set_entry(unsigned char num, unsigned int base, unsigned short int selector, unsigned char flags){
    idt[num].base_low  = base & 0xFFFF;
    idt[num].base_high = (base >> 16) & 0xFFFF;

    idt[num].selector    = selector;
    idt[num].always_zero = 0;
    idt[num].flags = flags;
}