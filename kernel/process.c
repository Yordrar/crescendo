#include "process.h"

#define MAX_NUM_PROCESS 1000

typedef enum process_state {
    READY, 
    EXECUTING, 
    BLOCKED
} process_state;

typedef struct PCB {
    int pid;
    process_state state;
    unsigned int eax, ebx, ecx, edx, edi, esi;
    unsigned int esp, ebp;
    unsigned int cs, ds, es, fs, gs, ss;
    unsigned int eip;
} PCB;

PCB process_table[MAX_NUM_PROCESS];

int process_get_state(int pid) {
    return (int)process_table[pid].pid;
}