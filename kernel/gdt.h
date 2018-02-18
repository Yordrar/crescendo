#ifndef _GDT_H_
#define _GDT_H_

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

void gdt_init(void);
void gdt_set_entry(int num, unsigned int base, unsigned int limit, unsigned char access, unsigned char gran);
extern void gdt_loadgdt(unsigned int); // Defined in gdt_loadgdt.s

#endif // gdt.h