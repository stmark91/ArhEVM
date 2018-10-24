#ifndef SC_REGISTER_H
#define SC_REGISTER_H

#include "./sc.h"

int sc_regInit(void);
int sc_regSet(int sc_register, int value);
int sc_regGet(int sc_register, int* value);

#endif
