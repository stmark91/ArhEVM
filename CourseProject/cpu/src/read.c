#include "./../include/cpu.h"

extern int instructionPointer;
extern int readUse;

int readMcell(int pos){
  int plusFlag = 0, num = 0, ret = 0, command = 0, operand = 0, mem = 0;
  setEchoRegime();
  refreshGui(pos);
  mt_gotoXY(1, 23);
  printLine(3);
  mt_gotoXY(1, 23);
  writeChar(1,"READ: ");
  mt_gotoXY(1, 24);
  readUse = 1;
  ret = changeCell(pos);
  readUse = 0;
  restoreEchoRegime();
  return ret;
}
