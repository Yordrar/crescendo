#ifndef _IDT_H_
#define _IDT_H_

void idt_init(void);
void idt_set_entry(unsigned char num, unsigned int base, unsigned short int selector, unsigned char flags);
void idt_loadidt(unsigned int idt_ptr); // Defined in idt_loadidt.s

#endif // idt.h