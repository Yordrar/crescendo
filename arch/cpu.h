#ifndef _CPU_H_
#define _CPU_H_

typedef struct cpu_context {
    unsigned int eax, ebx, ecx, edx, edi, esi;
    unsigned int esp, ebp;
    unsigned int cs, ds, es, fs, gs, ss;
    unsigned int eip;
} cpu_context;

#endif // cpu.h