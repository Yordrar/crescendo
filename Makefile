CSOURCES = $(wildcard */*.c)
ASMSOURCES = $(wildcard */*.s)

OBJECTS = $(patsubst %.c, %.o, $(CSOURCES)) $(patsubst %.s, %.o, $(ASMSOURCES))

CC = gcc
CFLAGS = -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector \
			-nostartfiles -nodefaultlibs -Wall -Wextra -c

LDFLAGS = -T linker.ld -melf_i386

AS = nasm
ASFLAGS = -f elf

.PHONY: run obj clean

run: build/crescendo.iso
	qemu-system-i386 build/crescendo.iso

build/crescendo.iso: iso/kernel.img
	mkdir -p iso/boot
	mkdir -p iso/boot/grub
	touch iso/boot/grub/grub.cfg
	printf "set timeout=10 \nset default=0 \n\nmenuentry "Crescendo" { \n\tmultiboot /kernel.img \n\tboot \n}" > iso/boot/grub/grub.cfg
	grub-mkrescue -o build/crescendo.iso iso

iso/kernel.img: $(OBJECTS)
	mkdir -p iso
	ld $(LDFLAGS) $(OBJECTS) -o iso/kernel.img

%.o: %.c
	$(CC) $(CFLAGS) $< -o $@

%.o: %.s
	$(AS) $(ASFLAGS) $< -o $@

clean:
	rm -rf $(OBJECTS) iso