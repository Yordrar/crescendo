bits 32
section .text

%macro ISR_NOERRCODE 1  ; define a macro, taking one parameter
  global isr%1          ; %1 accesses the first parameter.
  isr%1:
    cli
    push dword 0
    push dword %1
    jmp interrupt_common
%endmacro

%macro ISR_ERRCODE 1
  global isr%1
  isr%1:
    cli
    push dword %1
    jmp interrupt_common
%endmacro

ISR_NOERRCODE 0
ISR_NOERRCODE 1
ISR_NOERRCODE 2
ISR_NOERRCODE 3
ISR_NOERRCODE 4
ISR_NOERRCODE 5
ISR_NOERRCODE 6
ISR_NOERRCODE 7
ISR_ERRCODE 8
ISR_NOERRCODE 9
ISR_ERRCODE 10
ISR_ERRCODE 11
ISR_ERRCODE 12
ISR_ERRCODE 13
ISR_ERRCODE 14
ISR_NOERRCODE 15
ISR_NOERRCODE 16
ISR_ERRCODE 17
ISR_NOERRCODE 18
ISR_NOERRCODE 19
ISR_NOERRCODE 20
ISR_NOERRCODE 21
ISR_NOERRCODE 22
ISR_NOERRCODE 23
ISR_NOERRCODE 24
ISR_NOERRCODE 25
ISR_NOERRCODE 26
ISR_NOERRCODE 27
ISR_NOERRCODE 28
ISR_NOERRCODE 29
ISR_NOERRCODE 30
ISR_NOERRCODE 31

%macro IRQ 2
  global irq%1
  irq%1:
    cli
    push dword 0
    push dword %2
    jmp interrupt_common
%endmacro

IRQ 0, 32
IRQ 1, 33
IRQ 2, 34
IRQ 3, 35
IRQ 4, 36
IRQ 5, 37
IRQ 6, 38
IRQ 7, 39
IRQ 8, 40
IRQ 9, 41
IRQ 10, 42
IRQ 11, 43
IRQ 12, 44
IRQ 13, 45
IRQ 14, 46

extern interrupt_handler

interrupt_common:
  pusha         ; Pushes edi,esi,ebp,esp,ebx,edx,ecx,eax

  mov ax, ds    ; Lower 16-bits of eax = ds.
  push eax      ; save the data segment descriptor

  mov ax, 0x10  ; load the kernel data segment descriptor
  mov ds, ax
  mov es, ax
  mov fs, ax
  mov gs, ax

  call interrupt_handler

  pop eax       ; reload the original data segment descriptor
  mov ds, ax
  mov es, ax
  mov fs, ax
  mov gs, ax

  popa          ; Pops edi,esi,ebp,esp,ebx,edx,ecx,eax
  add esp, 8    ; Cleans up the pushed error code and pushed ISR number
  sti
  iret          ; restores the old cpu state

global interrupt_routines
section .data
interrupt_routines:
  dd isr0
  dd isr1
  dd isr2
  dd isr3
  dd isr4
  dd isr5
  dd isr6
  dd isr7
  dd isr8
  dd isr9
  dd isr10
  dd isr11
  dd isr12
  dd isr13
  dd isr14
  dd isr15
  dd isr16
  dd isr17
  dd isr18
  dd isr19
  dd isr20
  dd isr21
  dd isr22
  dd isr23
  dd isr24
  dd isr25
  dd isr26
  dd isr27
  dd isr28
  dd isr29
  dd isr30
  dd isr31
  dd irq0
  dd irq1
  dd irq2
  dd irq3
  dd irq4
  dd irq5
  dd irq6
  dd irq7
  dd irq8
  dd irq9
  dd irq10
  dd irq11
  dd irq12
  dd irq13
  dd irq14