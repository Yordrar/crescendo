#include "gdt.h"
#include "../driver/fb.h"

#define GDT_ENTRIES 5

//Levels of access for the segments
#define GDT_ACCESS_PRIVILEGE_KERNEL 0x90
#define GDT_ACCESS_PRIVILEGE_USER 0xF0
#define GDT_ACCESS_EXECUTABLE 0x08
#define GDT_ACCESS_READABLE 0x02
#define GDT_ACCESS_WRITABLE 0x02

#define GDT_FLAGS 0xC //Always pages of 4 KiB and 32-bit mode

struct gdt_entry {
	unsigned short int limit_low; // The lower 16 bits of the limit.
	unsigned short int base_low;  // The lower 16 bits of the base.
	unsigned char  base_middle;   // The next 8 bits of the base.
	unsigned char  access;        // Access flags, determine which ring this segment can be used.
	unsigned char  flags;         // Granularity flags, Also has the higher 4 bits of the limit
	unsigned char  base_high;     // The last 8 bits of the base.
} __attribute__((packed));
typedef struct gdt_entry gdt_entry_t;

gdt_entry_t gdt[GDT_ENTRIES];

static inline void
lgdt(gdt_entry_t *p, int size)
{
  volatile unsigned short pd[3];

  pd[0] = size-1;
  pd[1] = (unsigned int)p;
  pd[2] = (unsigned int)p >> 16;

  asm volatile("lgdt (%0)" : : "r" (pd));
}

void gdt_init() {
    gdt_set_entry(0, 0, 0, 0); // NULL entry
    gdt_set_entry(1, 0, 0xFFFFFFFF, GDT_ACCESS_PRIVILEGE_KERNEL|
                                    GDT_ACCESS_EXECUTABLE|
                                    GDT_ACCESS_READABLE); // Kernel code segment

    gdt_set_entry(2, 0, 0xFFFFFFFF, GDT_ACCESS_PRIVILEGE_KERNEL|
                                    GDT_ACCESS_WRITABLE); // Kernel data segment

    lgdt((unsigned int)gdt, sizeof(gdt));
}

void gdt_set_entry(int num, unsigned int base, unsigned int limit, unsigned char access) {
    gdt[num].base_low    = (base & 0xFFFF);
    gdt[num].base_middle = (base >> 16) & 0xFF;
    gdt[num].base_high   = (base >> 24) & 0xFF;

    gdt[num].limit_low  = (limit & 0xFFFF);
    gdt[num].flags      = (limit >> 16) & 0x0F;

    gdt[num].flags |= 0xC0;
    gdt[num].access = access;
}