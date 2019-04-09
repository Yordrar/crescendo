#ifndef _PROCESS_H_
#define _PROCESS_H_

typedef enum process_state {
	EMPTY_PROCESS,
	READY, 
	EXECUTING, 
	BLOCKED
} process_state;

void process_create(unsigned int entrypoint);
process_state process_get_state(int pid);

#endif // process.h