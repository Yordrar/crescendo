# Crescendo - 32-bit toy kernel
This is a simple 32-bit toy kernel for the Intel x86 architecture that I am developing for self-learning purposes.

Currently it just sets up a simple environment, the gdt, the idt and irqs and enters an infinite loop. A lot of code is very dirty and before adding new functionalities I want to tidy it up.

# How to try it
Clone this repo in your machine and execute `make` for building and automatically running the kernel (qemu emulator is needed for this, if you use another one feel free to change the Makefile). If you want just the iso image, execute `make iso`.
