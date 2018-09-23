global idt_loadidt
bits 32

idt_loadidt:
    mov eax, [esp+4]

    lidt [eax]

    ret