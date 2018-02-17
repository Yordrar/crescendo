#include "gdt.h"

void gdt_init() {
    gdt_ptr.address = (int)&gdt;
    gdt_ptr.size = (sizeof(gdt_entry_t) * GDT_ENTRIES) - 1;

    gdt_set_entry(0, 0, 0, 0, 0); // NULL entry
    gdt_set_entry(1, 0, 0xFFFFFFFF, 0x9A, 0x2F); // Code segment
    gdt_set_entry(2, 0, 0xFFFFFFFF, 0x92, 0x2F); // Data segment

    gdt_loadgdt((unsigned int)&gdt_ptr);
}

void gdt_set_entry(int num, unsigned int base, unsigned int limit, unsigned char access, unsigned char gran) {
    gdt[num].base_low    = (base & 0xFFFF);
    gdt[num].base_middle = (base >> 16) & 0xFF;
    gdt[num].base_high   = (base >> 24) & 0xFF;

    gdt[num].limit_low   = (limit & 0xFFFF);
    gdt[num].granularity = (limit >> 16) & 0x0F;

    gdt[num].granularity |= gran & 0xF0;
    gdt[num].access      = access;
}