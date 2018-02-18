global boot
extern kernel_main
bits 32

MAGIC_NUMBER equ 0x1BADB002
FLAGS        equ 0x00
CHECKSUM     equ -MAGIC_NUMBER

section .text:
align 4
    dd MAGIC_NUMBER
    dd FLAGS
    dd CHECKSUM

boot:
    mov esp, kernel_stack + 8192

    push ebx
    jmp kernel_main

    hlt

section .bss:
align 4
kernel_stack:
    resb 8192