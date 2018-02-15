global boot
extern main

MAGIC_NUMBER equ 0x1BADB002
FLAGS        equ 0x0
CHECKSUM     equ -MAGIC_NUMBER

section .text:
align 4
    dd MAGIC_NUMBER
    dd FLAGS
    dd CHECKSUM

boot:
    mov esp, kernel_stack + 4096

    jmp main

    hlt

section .bss:
align 4
kernel_stack:
    resb 4096