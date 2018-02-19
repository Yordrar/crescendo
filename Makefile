OBJECTS = boot.o main.o pio.o tty.o gdt.o gdt_loadgdt.o idt.o idt_loadidt.o interrupt.o interrupt_routines.o pit.o keyboard.o

CC = gcc
CFLAGS = -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector \
			-nostartfiles -nodefaultlibs -Wall -Wextra -c

LDFLAGS = -T linker.ld -melf_i386

AS = nasm
ASFLAGS = -f elf

run: iso
	qemu-system-i386 crescendo.iso
	make clean

iso: kernel.img
	grub-mkrescue -o crescendo.iso iso
	rm -rf *.o iso/kernel.img

kernel.img: $(OBJECTS)
	ld $(LDFLAGS) $(OBJECTS) -o iso/kernel.img

%.o: kernel/%.c
	$(CC) $(CFLAGS)  $< -o $@

%.o: kernel/%.s
	$(AS) $(ASFLAGS) $< -o $@

%.o: driver/%.c
	$(CC) $(CFLAGS)  $< -o $@

clean:
	rm -rf *.o iso/kernel.img crescendo.iso