#ifndef _MEMORY_H_
#define _MEMORY_H_

extern kernel_virt_start;
extern kernel_virt_end;
extern kernel_phys_start;
extern kernel_phys_text_end;
extern kernel_phys_end;

#define KERNELBASE 0xC0000000
#define	PAGEDIRIDX(x) ((x) >> 22)
#define	PAGETABLEIDX(x) (((x) & 0x003FF000) >> 12)
#define PAGESIZE 0x1000

typedef struct page_table_entry {
	unsigned int present:1;
	unsigned int writeable:1;
	unsigned int user_mode:1;
	unsigned int reserved1:2;
	unsigned int accessed:1;
	unsigned int written:1;
	unsigned int reserved2:2;
	unsigned int available:3;
	unsigned int physical_frame:20;
} page_table_entry_t;

typedef struct page_table {
	__attribute__((__aligned__(4096)))
	page_table_entry_t entries[1024];
} page_table_t;

typedef struct page_directory {
	__attribute__((__aligned__(4096)))
	page_table_t* tables[1024];
} page_directory_t;

unsigned int entry_page_dir[];
__attribute__((__aligned__(4096)))
unsigned int entry_page_dir[1024] = {
	// Map VA's [0, 4MB) to PA's [0, 4MB)
	[0] = (0) | 0x83,
  	// Map VA's [KERNBASE, KERNBASE+4MB) to PA's [0, 4MB)
	[PAGEDIRIDX(KERNELBASE)] = (0) | 0x83
};

#endif