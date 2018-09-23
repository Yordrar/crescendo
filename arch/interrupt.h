#ifndef _INTERRUPT_H_
#define _INTERRUPT_H_

#include "cpu.h"

#define IRQ0 32
#define IRQ1 33
#define IRQ2 34
#define IRQ3 35
#define IRQ4 36
#define IRQ5 37
#define IRQ6 38
#define IRQ7 39
#define IRQ8 40
#define IRQ9 41
#define IRQ10 42
#define IRQ11 43
#define IRQ12 44
#define IRQ13 45
#define IRQ14 46
#define IRQ15 47

typedef struct interrupt_frame {
    unsigned int ds; // Data segment selector, pushed by interrupt_common
    unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax; // Pushed by pusha in interrupt_common
    unsigned int int_num, error_code; // Interrupt number and error code, pushed in some isr
    unsigned int eip, cs, eflags, user_esp, ss; // Pushed by the processor automatically
} interrupt_frame_t;

void interrupt_handler(interrupt_frame_t regs); // The interrupt handler

// Enables registration of callbacks for interrupts or IRQs
// For IRQs, we use the #defines above as the first parameter
typedef void (*isr_t)(interrupt_frame_t);
void register_interrupt_handler(unsigned char n, isr_t handler);

// Entry points of each interrupt, they push the interrupt number
// and call interrupt_common which saves the registers and calls
// interrupt_handler which does the handling of each interrupt
extern unsigned int interrupt_routines[];

#endif // interrupt.h