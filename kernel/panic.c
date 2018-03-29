#include "panic.h"

#include "../driver/tty.h"

void kernel_panic(const char* msg) {
    tty_write(msg);

    while(1) {
        asm volatile("cli");
        asm volatile("hlt");
    }
    
}