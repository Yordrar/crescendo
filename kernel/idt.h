#ifndef _IDT_H_
#define _IDT_H_

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

idt_entry_t idt[IDT_ENTRIES];
lidt_struct_t idt_ptr;

void idt_init(void);
void idt_set_entry(unsigned char num, unsigned int base, unsigned short int selector, unsigned char flags);
void idt_loadidt(unsigned int idt_ptr); // Defined in idt_loadidt.s

#endif // idt.h