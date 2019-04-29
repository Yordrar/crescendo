#ifndef _MEMORY_H_
#define _MEMORY_H_

extern int kernel_virt_start;
extern int kernel_virt_end;
extern int kernel_phys_start;
extern int kernel_phys_text_end;
extern int kernel_phys_end;

#define KERNELBASE 0xC0000000
#define PAGESIZE 0x1000
#define PAGEROUNDDOWN(x) (((x)) & ~(PAGESIZE-1))
#define PAGEROUNDUP(sz)  (((sz)+PAGESIZE-1) & ~(PAGESIZE-1))
#define V2P(a) (((unsigned int) (a)) - KERNELBASE)
#define P2V(a) ((void*)(((char*) (a)) + KERNELBASE))

char* alloc_mem_end;

void memory_init(void);
void* memory_kalloc(void);

#endif