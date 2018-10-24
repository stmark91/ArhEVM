#include "./../include/cpu.h"

extern int accumulator;
extern int instructionPointer;

void CU(){
  int command, operand, mem;
  if (instructionPointer >= sizeRAM) {
    sc_regSet(FLAG_OUTMEM, 1);
    sc_regSet(FLAG_INTERRUPT, 1);
    refreshGui(instructionPointer);
    instructionPointer = 0;
    return;
  }
  sc_memoryGet(instructionPointer, &mem);
  if (!(sc_commandDecode(mem, &command, &operand)
      == 0)) {
    sc_regSet(FLAG_COMMAND, 1);
    sc_regSet(FLAG_INTERRUPT, 1);
    return;
  }
  if ((operand < 0) | (operand >= sizeRAM)) {
    sc_regSet(FLAG_COMMAND, 1);
    sc_regSet(FLAG_INTERRUPT, 1);
    return;
  }
  if ((command >= 0x30) & (command <= 0x33) |
      (command >= 0x51) & (command <= 0x54) |
      (command >= 0x60) & (command <= 0x70) |
      (command >= 0x75) & (command <= 0x76)) {
    if (ALU(command, operand) != 0)
      sc_regSet(FLAG_INTERRUPT, 1);
  } else commandHandler(command, operand);
  instructionPointer++;
}

int ALU(int command, int operand){
  if ((operand < 0) | (operand >= sizeRAM)) {
    sc_regSet(FLAG_OUTMEM,1);
    return ERR_WRONG_ADDR;
  } else {
    if (commandHandler(command, operand) != 0) return -1;
    if ((accumulator > 0x3FFF)) {
      accumulator &= 0x3FFF;
      sc_regSet(FLAG_OVERFLOW, 1);
    } else sc_regSet(FLAG_OVERFLOW, 0);
    sc_regSet(FLAG_ODD, accumulator & 1);
    return 0;
  }
}
