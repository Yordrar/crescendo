bits 32

global pio_read_byte
global pio_write_byte
global pio_read_word
global pio_write_word

section .text:

pio_read_byte:
	mov     edx, [esp+4]
	in      al, dx
	ret

pio_write_byte:
	mov     eax, [esp+8]
	mov     edx, [esp+4]
	out     dx, al
	ret

pio_read_word:
	mov     edx, [esp+4]
	in      ax, dx
	ret

pio_write_word:
	mov     eax, [esp+8]
	mov     edx, [esp+4]
	out     dx, ax
	ret