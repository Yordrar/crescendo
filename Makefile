CSOURCES = $(wildcard */*.c)
ASMSOURCES = $(wildcard arch/*.s)

OBJECTS = kernel/boot.o $(patsubst %.s, %.o, $(ASMSOURCES)) $(patsubst %.c, %.o, $(CSOURCES))

CC = gcc
CFLAGS = -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector \
-nostartfiles -nodefaultlibs -Wall -Wextra -lgcc -c

LD = ld
LDFLAGS = -T linker.ld -melf_i386

AS = nasm
ASFLAGS = -f elf

.PHONY: run clean

run: build/crescendo.iso
	qemu-system-i386 -d guest_errors build/crescendo.iso
	make clean

build/crescendo.iso: crescendo.img
	rm -rf build/crescendo.iso
	grub-mkrescue -o build/crescendo.iso iso

crescendo.img: $(OBJECTS)
	mkdir -p iso/boot/grub
	touch iso/boot/grub/grub.cfg
	printf "set timeout=10 \nset default=0 \n\nmenuentry \"Crescendo\" { \n\tmultiboot /crescendo.img \n\tboot \n}" > iso/boot/grub/grub.cfg
	$(LD) $(LDFLAGS) $(OBJECTS) -o iso/crescendo.img

%.o: %.c
	$(CC) $(CFLAGS) $< -o $@

%.o: %.s
	$(AS) $(ASFLAGS) $< -o $@

clean:
	rm -rf $(OBJECTS) iso
