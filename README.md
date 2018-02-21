# Crescendo - 32-bit toy kernel
This is a simple 32-bit toy kernel for the Intel x86 architecture that I am developing for self-learning purposes.

Currently it just sets up a simple environment, the gdt, the idt and irqs and enters an infinite loop. A lot of code is very dirty and I want to tidy it up before adding new functionalities.

# How to try it
## Precompiled iso image
In the `build` directory you can find a precompiled iso image, you can emulate this image using qemu or bochs, or burn it to a CD or USB and run it on real hardware (I tested booting only on an old laptop I had lying around, don't know if it'll work on every hardware out there).

## Compiling from source
(A Linux environment and Make are needed for this)
Clone this repo in your machine and execute `make` for building and automatically running the kernel (qemu emulator is needed for this, if you use another one feel free to change the Makefile), this will use your currently installed grub as a bootloader. If you just want the iso image, execute `make iso`. To clean the workspace after building, execute `make clean`.
