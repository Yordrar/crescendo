global boot
extern kernel_main
bits 32

KERNEL_STACK_SIZE equ 4096

MULTIBOOT_MAGIC_NUMBER equ 0x1BADB002 ; Header for grub to recognize the kernel
MULTIBOOT_FLAGS        equ 0x00000000 ; Optional flags for grub
MULTIBOOT_CHECKSUM     equ -(MULTIBOOT_MAGIC_NUMBER + MULTIBOOT_FLAGS) ; Checksum for grub

section .text:
align 4
    dd MULTIBOOT_MAGIC_NUMBER
    dd MULTIBOOT_FLAGS
    dd MULTIBOOT_CHECKSUM

boot:
    cli ; Disable hardware interrupts

    mov esp, kernel_stack + KERNEL_STACK_SIZE ; Make space for the stack

    push eax ; Push magic number from grub
    push ebx ; Push multiboot information to the stack to pass it as an argument of kernel_main
    jmp kernel_main

    ; Halt the cpu if kernel_main returns. If we disable interrupts and halt
    ; the cpu, it will hang forever
    cli
    hlt

; Create uninitialized space for the stack
section .bss:
align 4
kernel_stack:
    resb KERNEL_STACK_SIZE