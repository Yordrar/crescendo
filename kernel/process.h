#ifndef _PROCESS_H_
#define _PROCESS_H_

void process_create(unsigned int entrypoint);
int process_get_state(int pid);

#endif // process.h