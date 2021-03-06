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
	unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax; // Pushed by pusha in interrupt_common.
	unsigned int int_num, error_code; // Interrupt number and error code, pushed in some isr or irq
	unsigned int eip, cs, eflags, user_esp, ss; // Pushed by the processor automatically.
} interrupt_frame_t;

// The generic interrupt handler that calls the specific handler for each interrupt
void interrupt_generic_handler(interrupt_frame_t regs); 

//A function that handles an interrupt must be of this type
typedef void (*isr_t)(interrupt_frame_t);
//Registration of callbacks for interrupts or IRQs.
//For IRQs use the #defines above as the first parameter.
void interrupt_register_handler(unsigned char n, isr_t handler);

//Entry points of each interrupt, they push the interrupt number
//and call interrupt_common which saves the registers and calls
//interrupt_handler which does the handling of each interrupt (defined in interrupt_routines.s)
extern unsigned int interrupt_routines[];

#endif // interrupt.h