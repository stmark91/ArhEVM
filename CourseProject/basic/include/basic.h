#ifndef BASIC_H
#define BASIC_H

#include "./../../print/include/write.h"
#include "./../../cpu/include/cpu.h"
#include <malloc.h>

enum keywords {
  KEYW_REM = 1,
  KEYW_INPUT = 2,
  KEYW_OUTPUT = 3,
  KEYW_GOTO = 4,
  KEYW_IF = 5,
  KEYW_LET = 6,
  KEYW_END = 7,
  KEYW_E = -1
};

struct tLE {
    struct tLE  *next;         
    int  data;      
}*hd;

struct tLEC {
    struct tLEC  *next;         
    char  dt;      
}*head;

typedef struct varBasic {
  char name[2];
  int cell;
  int variable;
} var;

typedef struct memoryMap {
  int real;
  int expect;
} memMap;

int keywordCode(char* str);
int parsingLineB(char* str, int output);
int basicTrans(int argc, char *argv[]);
int ifoperation(int output, char* op, int let, int zn);
void convert(char *str, char *out);
int prior(char c); 

#endif
