extern kernel_main
extern entry_page_dir
bits 32

MULTIBOOT_MAGIC_NUMBER equ 0x1BADB002 ; Header for grub to recognize the kernel
MULTIBOOT_FLAGS        equ 0x00000000 ; Optional flags for grub
MULTIBOOT_CHECKSUM     equ -(MULTIBOOT_MAGIC_NUMBER + MULTIBOOT_FLAGS) ; Checksum for grub

KERNEL_STACK_SIZE equ 4096

section .text
align 4
	dd MULTIBOOT_MAGIC_NUMBER
	dd MULTIBOOT_FLAGS
	dd MULTIBOOT_CHECKSUM

global _start
_start:
	cli	;Disable hardware interrupts

	;DIRTY
	mov ecx, cr4
	or	ecx, 0x10 ;Enable PSE
	mov	cr4, ecx

	mov ecx, entry_page_dir - 0xC0000000
	mov	cr3, ecx

	mov	ecx, cr0
	or	ecx, 0x80010000
	mov cr0, ecx
	;DIRTY
	
	mov esp, kernel_stack ;Make space for the stack
	add esp, KERNEL_STACK_SIZE
	mov ebp, esp

	push eax ;Push the magic number provided by grub to the stack to pass it as an argument of kernel_main
	push ebx ;Push multiboot information
	call kernel_main

	;Halt the cpu if kernel_main returns
	cli
	hlt

;Create uninitialized space for the stack
section .bss
align 4
kernel_stack:
	resb KERNEL_STACK_SIZE