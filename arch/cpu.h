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
    asm volatile("pushfl; popl %0" : "=r" (eflags));
    return eflags;
}

static inline void cli(void) {
    asm volatile("cli");
}

static inline void sti(void) {
    asm volatile("sti");
}

#endif // cpu.h