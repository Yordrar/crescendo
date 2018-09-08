#include "panic.h"

#include "../driver/fb.h"

void kernel_panic(const char* msg) {
    fb_write(msg);

    while(1) {
        asm volatile("cli");
        asm volatile("hlt");
    }
    
}