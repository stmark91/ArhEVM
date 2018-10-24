#ifndef SC_MEMORY_H
#define SC_MEMORY_H

#include "./sc.h"

int sc_memoryInit(void);
int sc_memorySet(int addres, int value);
int sc_memoryGet(int addres, int* value);
volatile int sc_memorySave(char* filename);
volatile int sc_memoryLoad(char* filename);

#endif
