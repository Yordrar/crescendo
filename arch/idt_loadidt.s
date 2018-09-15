global idt_loadidt
bits 32

idt_loadidt:
    mov eax, [esp+8]

    lidt [eax]

    ret