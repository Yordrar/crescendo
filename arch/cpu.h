#ifndef _CPU_H_
#define _CPU_H_

typedef struct cpu_frame {
	unsigned int eax, ebx, ecx, edx, edi, esi;
	unsigned int esp, ebp;
	unsigned int cs, ds, es, fs, gs, ss;
	unsigned int eip;
	unsigned int eflags;
} cpu_frame_t;

void cpu_init(void);

static inline unsigned int cpu_get_eflags(void) {
	unsigned int eflags;
	asm volatile("pushfl; popl %0" : "=r" (eflags) : : "memory");
	return eflags;
}

static inline void cpu_disable_interrupts(void) {
	asm volatile("cli");
}

static inline void cpu_enable_interrupts(void) {
	asm volatile("sti");
}

///// GDT /////
void gdt_init(void);
void gdt_set_entry(int num, unsigned int base, unsigned int limit, unsigned char access);
extern void gdt_loadgdt(unsigned int); // Defined in gdt_loadgdt.s

///// IDT /////
void idt_init(void);
void idt_set_entry(unsigned char num, unsigned int base, unsigned short int selector, unsigned char flags);
void idt_loadidt(unsigned int); // Defined in idt_loadidt.s

#endif // cpu.h