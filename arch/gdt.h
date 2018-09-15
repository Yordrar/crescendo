#ifndef _GDT_H_
#define _GDT_H_

void gdt_init(void);
void gdt_set_entry(int num, unsigned int base, unsigned int limit, unsigned char access);
extern void gdt_loadgdt(unsigned int, unsigned short int); // Defined in gdt_loadgdt.s

#endif // gdt.h