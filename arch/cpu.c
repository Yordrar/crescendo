#include "cpu.h"
#include "interrupt.h"
#include "pio.h"
#include <kernel/panic.h>
#include <kernel/memory.h>
#include <driver/cga.h>

///// GDT /////
#define GDT_ENTRIES 5

//Levels of access for the segments
#define GDT_ACCESS_PRIVILEGE_KERNEL 0x90
#define GDT_ACCESS_PRIVILEGE_USER 0xF0
#define GDT_ACCESS_EXECUTABLE 0x08
#define GDT_ACCESS_READABLE 0x02
#define GDT_ACCESS_WRITABLE 0x02

struct lgdt_struct {
	unsigned short int size;
	unsigned int address;
}__attribute__((packed));
typedef struct lgdt_struct lgdt_struct_t;

struct gdt_entry {
   unsigned short int limit_low;// The lower 16 bits of the limit.
   unsigned short int base_low; // The lower 16 bits of the base.
   unsigned char  base_middle;  // The next 8 bits of the base.
   unsigned char  access;       // Access flags, determine which ring this segment can be used.
   unsigned char  flags;		// 0 if limit is in 1 byte blocks, 1 if 4Kib blocks
   unsigned char  base_high;    // The last 8 bits of the base.
} __attribute__((packed));
typedef struct gdt_entry gdt_entry_t;

gdt_entry_t gdt[GDT_ENTRIES];
lgdt_struct_t gdt_ptr;

extern void gdt_loadgdt(unsigned int); // Defined in gdt_loadgdt.s

void gdt_set_entry(int num, unsigned int base, unsigned int limit, unsigned char access) {
	gdt[num].base_low    = (base & 0xFFFF);
	gdt[num].base_middle = (base >> 16) & 0xFF;
	gdt[num].base_high   = (base >> 24) & 0xFF;

	gdt[num].limit_low   = (limit & 0xFFFF);
	gdt[num].flags = (limit >> 16) & 0x0F;

	gdt[num].flags |= 0xC0;
	gdt[num].access      = access;
}

void gdt_init() {
	gdt_ptr.address = (unsigned int)&gdt;
	gdt_ptr.size = (sizeof(gdt_entry_t) * GDT_ENTRIES) - 1;

	gdt_set_entry(0, 0, 0, 0); // NULL entry
	gdt_set_entry(1, 0, 0xFFFFFFFF, GDT_ACCESS_PRIVILEGE_KERNEL |
									GDT_ACCESS_EXECUTABLE |
									GDT_ACCESS_READABLE); // Kernel code segment

	gdt_set_entry(2, 0, 0xFFFFFFFF, GDT_ACCESS_PRIVILEGE_KERNEL |
									GDT_ACCESS_WRITABLE); // Kernel data segment

	gdt_loadgdt((unsigned int)&gdt_ptr);
}





///// IDT /////
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

extern void idt_loadidt(unsigned int); // Defined in idt_loadidt.s

void idt_set_entry(unsigned char num, unsigned int base, unsigned short int selector, unsigned char flags){
	idt[num].base_low  = base & 0xFFFF;
	idt[num].base_high = (base >> 16) & 0xFFFF;

	idt[num].selector    = selector;
	idt[num].always_zero = 0;
	// We must uncomment the OR below when we get to using user-mode.
	// It sets the interrupt gate's privilege level to 3.
	idt[num].flags = flags /* | 0x60 */;
}

void idt_init(void) {
	idt_ptr.address = (unsigned int)&idt;
	idt_ptr.size = (sizeof(idt_entry_t) * IDT_ENTRIES) - 1;

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
		idt_set_entry(i, interrupt_routines[i], 0x08, 0x8E);
	}

	idt_loadidt((unsigned int)&idt_ptr);
}



///// CPU /////

void cpu_init(void) {
	gdt_init();
	idt_init();
}