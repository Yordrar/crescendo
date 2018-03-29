#ifndef _CPU_H_
#define _CPU_H_

typedef struct interrupt_frame {
    unsigned int ds; // Data segment selector, pushed by interrupt_common
    unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax; // Pushed by pusha in interrupt_common.
    unsigned int int_num, error_code; // Interrupt number and error code, pushed in some isr
    unsigned int eip, cs, eflags, user_esp, ss; // Pushed by the processor automatically.
} interrupt_frame_t;

#endif // cpu.h