#include "memory.h"

#include <driver/cga.h>

void memory_init() {
	alloc_mem_end = &kernel_virt_end;
}

void* memory_kalloc() {
	void* mem = alloc_mem_end;
	alloc_mem_end += PAGESIZE;
	return mem;
}