#ifndef _INTERRUPT_H_
#define _INTERRUPT_H_

typedef struct registers {
    unsigned int ds; // Data segment selector, pushed by interrupt_common
    unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax; // Pushed by pusha in interrupt_common.
    unsigned int int_num, error_code; // Interrupt number and error code, pushed in some isr
    unsigned int eip, cs, eflags, user_esp, ss; // Pushed by the processor automatically.
} registers_t;

void interrupt_handler(registers_t regs); // The interrupt handler

// Entry points of each interrupt, they push the interrupt number
// and call interrupt_common which saves the registers and calls
// interrupt_handler which does the handling of each interrupt
extern void isr0(void);
extern void isr1(void);
extern void isr2(void);
extern void isr3(void);
extern void isr4(void);
extern void isr5(void);
extern void isr6(void);
extern void isr7(void);
extern void isr8(void);
extern void isr9(void);
extern void isr10(void);
extern void isr11(void);
extern void isr12(void);
extern void isr13(void);
extern void isr14(void);
extern void isr15(void);
extern void isr16(void);
extern void isr17(void);
extern void isr18(void);
extern void isr19(void);
extern void isr20(void);
extern void isr21(void);
extern void isr22(void);
extern void isr23(void);
extern void isr24(void);
extern void isr25(void);
extern void isr26(void);
extern void isr27(void);
extern void isr28(void);
extern void isr29(void);
extern void isr30(void);
extern void isr31(void);

#endif // interrupt.h