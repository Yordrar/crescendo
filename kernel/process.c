#include "process.h"
#include "../arch/cpu.h"

#define MAX_NUM_PROCESS 1000

unsigned int current_pid = 1;

typedef struct process {
	int pid;
	process_state state;
	cpu_frame_t cpu_frame;
} process;

process process_table[MAX_NUM_PROCESS] = {0};


void process_init() {

}

void process_create(unsigned int entrypoint) {
	process_table[current_pid].pid = current_pid;
	current_pid++;
	process_table[current_pid].state = READY;
	process_table[current_pid].cpu_frame.eip = entrypoint;
}

process_state process_get_state(int pid) {
	return process_table[pid].state;
}