#include "gdt.h"
#include "../driver/fb.h"

#define GDT_ENTRIES 5

struct lgdt_struct {
    unsigned short int size;
    unsigned int address;
}__attribute__((packed));
typedef struct lgdt_struct lgdt_struct_t;

struct gdt_entry {
   unsigned short int limit_low;       // The lower 16 bits of the limit.
   unsigned short int base_low;        // The lower 16 bits of the base.
   unsigned char  base_middle;         // The next 8 bits of the base.
   unsigned char  access;              // Access flags, determine which ring this segment can be used.
   unsigned char  granularity;         // 0 if limit is in 1 byte blocks, 1 if 4Kib blocks
   unsigned char  base_high;           // The last 8 bits of the base.
} __attribute__((packed));
typedef struct gdt_entry gdt_entry_t;

gdt_entry_t gdt[GDT_ENTRIES];
lgdt_struct_t gdt_ptr;

void gdt_init() {
    gdt_ptr.address = (unsigned int)&gdt;
    gdt_ptr.size = (sizeof(gdt_entry_t) * GDT_ENTRIES) - 1;

    gdt_set_entry(0, 0, 0, 0, 0); // NULL entry
    gdt_set_entry(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); // Code segment
    gdt_set_entry(2, 0, 0xFFFFFFFF, 0x92, 0xCF); // Data segment

    gdt_loadgdt((unsigned int)&gdt_ptr);
}

void gdt_set_entry(int num, unsigned int base, unsigned int limit, unsigned char access, unsigned char gran) {
    gdt[num].base_low    = (base & 0xFFFF);
    gdt[num].base_middle = (base >> 16) & 0xFF;
    gdt[num].base_high   = (base >> 24) & 0xFF;

    gdt[num].limit_low   = (limit & 0xFFFF);
    gdt[num].granularity = (limit >> 16) & 0x0F;

    gdt[num].granularity |= (gran & 0xF0);
    gdt[num].access      = access;
}