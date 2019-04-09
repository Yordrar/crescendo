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
	asm volatile("pushfl;"
				 "popl %0;" : "=r"(eflags) : : "memory");
	return eflags;
}

static inline void cpu_disable_interrupts(void) {
	asm volatile("cli");
}

static inline void cpu_enable_interrupts(void) {
	asm volatile("sti");
}

void cpu_enable_paging(void);

#endif // cpu.h