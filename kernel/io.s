global io_read
global io_write

section .text:

io_read:
    mov     edx, [esp+4]
    in      al, dx
    ret

io_write:
    mov     eax, [esp+8]
    mov     edx, [esp+4]
    out     dx, al
    ret