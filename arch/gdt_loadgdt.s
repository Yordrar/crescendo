global gdt_loadgdt
bits 32

gdt_loadgdt:
    mov eax, [esp+4]

    lgdt [eax]

    ; Change the segment registers
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax

    ; To change the segment register cs, we need to do a far jump
    jmp 0x08:loadgdt_return

loadgdt_return:
    ret