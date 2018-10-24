#include "./../include/mainHeader.h"

extern int accumulator;
extern int instructionPointer;
extern int writeUsed;
extern int writeValue;
extern int bigChars[];
extern int SCANPRINTRADIX;
extern int position;
extern int cursorX;
extern int cursorY;

struct itimerval val, oval;

int main(int argc, char** argv){
  sc_memoryInit();
  sc_regInit();
  setSignals();
  rk_mytermsave();
  sc_regSet(FLAG_INTERRUPT, 1);
  int position = 0, fd = 0, cn = 0, tmp = 0, exit = 0, refreshFlg = 0, regis = 0, regisProg = 0;
  enum keys key  = KEY_other;
  if ((fd = open("bigchars.bin", O_RDONLY)) == -1) {
    writeChar(2,"Cannot open ascibig\n");
    return -1;
  }
  bc_bigcharread(fd, bigChars, 17, &cn);
  close(fd);
  mt_clrscr();
  refreshGuiSt(position);
  while (!exit) {
    if (!refreshFlg) {
      refreshGui(position);
      refreshFlg = 1;
    }
    rk_readkey(&key);
    sc_regGet(FLAG_INTERRUPT, &regisProg);
    if(regisProg) {
      switch (key) {
        case KEY_up:
          if (cursorY != 0) cursorY--;
            else cursorY = 9;
          refreshFlg = 0;
          key  = KEY_other;
        break;
        case KEY_down:
          cursorY = (cursorY + 1) % 10;
          refreshFlg = 0;
          key  = KEY_other;
        break;
        case KEY_left:
          if (cursorX != 0) cursorX--;
            else cursorX = 9;
          refreshFlg = 0;
          key  = KEY_other;
        break;
        case KEY_right:
          cursorX = (cursorX + 1) % 10;
          refreshFlg = 0;
          key  = KEY_other;
        break;
        case KEY_f5:
          refreshFlg = changeAccumulator(position);
          key  = KEY_other;
        break;
        case KEY_f6:
          refreshFlg = changeInstructionPointer(position);
          key  = KEY_other;
        break;
        case KEY_enter:
          refreshFlg = changeCell(position);
          key  = KEY_other;
        break;
        case KEY_t:
          CU();
          refreshGui(instructionPointer);
          position = instructionPointer;
          cursorX = instructionPointer / 10;
          cursorY = instructionPointer % 10;
          key  = KEY_other;
        break;
        case KEY_s:
          memorySave(position);
          refreshFlg = 1;
          key  = KEY_other;
        break;
        case KEY_l:
          memoryLoad(position);
          refreshFlg = 1;
          key  = KEY_other;
        break;
        case KEY_i:
          raise(SIGUSR1);
          refreshFlg = 0;
          cursorX = 0;
          cursorY = 0;
          key  = KEY_other;
        break;
        case KEY_q:
          exit = 1;
          key  = KEY_other;
        break;
      }
    }
    if (key == KEY_c) {
      position = instructionPointer;
      cursorX = instructionPointer / 10;
      cursorY = instructionPointer % 10;
      refreshFlg = 0;
      raise(SIGUSR2);
      key  = KEY_other;
    } else if (key == KEY_esc) {
      raise(SIGTERM);
      key  = KEY_other;
    } else if (key == KEY_r) {
      key = KEY_other;
      sc_regGet(FLAG_INTERRUPT, &regis);
      if (regis) {
        sc_regInit();
        frequencyGenerator(START);
        position = instructionPointer;
        cursorX = instructionPointer / 10;
        cursorY = instructionPointer % 10;
        refreshFlg = 0;
        continue;
      } else {
        frequencyGenerator(STOP);
        sc_regSet(FLAG_INTERRUPT, 1);
        position = instructionPointer;
        cursorX = instructionPointer / 10 ;
        cursorY = instructionPointer % 10;
        refreshFlg = 0;
        continue;
	    }
    }
    position = cursorY + cursorX * 10;
  }
  frequencyGenerator(STOP);
  rk_mytermrestore();
  signalsRestore();
  system("rm -f termsettings");
  return 0;
}
