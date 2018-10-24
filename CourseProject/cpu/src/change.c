#include "./../include/cpu.h"

extern int accumulator;
extern int instructionPointer;
extern int SCANPRINTRADIX;
static struct sigaction act[5];
static struct sigaction old[5];
static sigset_t set;
static struct sigaction newalarm;
static struct sigaction oldalarm;
static sigset_t setalrm;
static struct termios originalTerm;
static int echoIgn = 0;
static int alarmIgn = 0;
extern int readUse;
static struct itimerval val;
static struct itimerval oval;

void frequencyGenerator (int status){
  if (status == START) {
    val.it_interval.tv_sec = TIMESLEEPSEC;
    val.it_interval.tv_usec = MKR(TIMESLEEPUSEC);
    val.it_value.tv_sec = TIMESLEEPSEC;
    val.it_value.tv_usec = MKR(TIMESLEEPUSEC);
    setitimer(TIMER, &val, &oval);
  } else if (status == STOP ) setitimer(TIMER, NULL, NULL);
}

void setSignals(){
  for (int i = 0; i < 5; i++) {
    memset(&(act[i]), 0, sizeof(act[i]));
    memset(&(old[i]), 0, sizeof(old[i]));
  }
  sigemptyset(&set);
  sigaddset(&set, SIGUSR1);
  sigaddset(&set, SIGALRM);
  act[0].sa_handler = timerHand;
  act[0].sa_mask = set;

  sigemptyset(&set);
  sigaddset(&set, SIGUSR1);
  act[1].sa_handler = ursignalHand;
  act[1].sa_mask = set;

  sigemptyset(&set);
  sigaddset(&set, SIGUSR1);
  sigaddset(&set, SIGUSR2);
  act[2].sa_handler = ursignalHand2;
  act[2].sa_mask = set;

  sigemptyset(&set);
  sigaddset(&set, SIGUSR1);
  sigaddset(&set, SIGWINCH);
  act[3].sa_handler = windHand;
  act[3].sa_mask = set;

  sigemptyset(&set);
  sigaddset(&set, SIGUSR1);
  sigaddset(&set, SIGTERM);
  act[4].sa_handler = killHand;
  act[4].sa_mask = set;

  //signal(SIGALRM, timerHand);
  //signal(SIGUSR1, ursignalHand1);
  //signal(SIGUSR2, ursignalHand2);
  //signal(SIGWINCH, windHand);
  //signal(SIGTERM, killHand);
  sigaction(SIGALRM, &(act[0]), &(old[0]));
  sigaction(SIGUSR1, &(act[1]), &(old[1]));
  sigaction(SIGUSR2, &(act[2]), &(old[2]));
  sigaction(SIGWINCH, &(act[3]), &(old[3]));
  sigaction(SIGTERM, &(act[4]), &(old[4]));
}

void signalsRestore(){
  sigemptyset(&set);
  sigaction(SIGALRM, &(old[0]), 0);
  sigaction(SIGUSR1, &(old[1]), 0);
  sigaction(SIGUSR2, &(old[2]), 0);
  sigaction(SIGWINCH, &(old[3]), 0);
  sigaction(SIGTERM, &(old[4]), 0);
}

void setIgnoreAlarm(){
  if (alarmIgn == 0) {
    newalarm.sa_handler = SIG_IGN;
    sigaction(SIGALRM, &(newalarm), &(oldalarm));
    alarmIgn = 1;
 } else return;
}

void restoreIgnoreAlarm(){
  if (alarmIgn == 1) {
    sigaction(SIGALRM, &(oldalarm), 0);
    alarmIgn = 0;
  } else return;
}

void setEchoRegime(){
  if (echoIgn == 0) {
    while (tcgetattr(STDIN_FILENO, &originalTerm) != 0);
    rk_mytermregime(0, 0, 1, 1, 1);
    echoIgn = 1;
  } else return;
}

void restoreEchoRegime(){
  if (echoIgn == 1) {
    while (tcsetattr(STDIN_FILENO, TCSANOW, &originalTerm) != 0);
    echoIgn = 0;
  } else return;
}

int changeCell(int pos){
  setEchoRegime();
  int plusFlag = 0, num = 0, command = 0, operand = 0, mem = 0;
  if (readUse == 0) {
    setIgnoreAlarm();
    refreshGui(pos);
    mt_gotoXY(1, 23);
    printLine(2);
    mt_gotoXY(1, 23);
    writeChar(1, "Enter num: ");
  }
  if (scanNum(&plusFlag, &num) != 0) {
    writeChar(2, "Not a number!");
    if (readUse == 0) restoreIgnoreAlarm();
    restoreEchoRegime();
    return -1;
  }
  if ((num >= 0) & (num < 0x8000)) {
    if (plusFlag) {
      command = (num >> 8) & 0x7F;
      if (num & 0x80) {
        writeChar(2, "Operand is 7 bit wide ( <= 7F). ");
        if (readUse == 0) restoreIgnoreAlarm();
        restoreEchoRegime();
        return -1;
      }
      operand = num & 0x7F;
      if (sc_commandEncode(command, operand, &mem) != 0) {
        writeChar(2, "Wrong command. Aborted. ");
        if (readUse == 0) restoreIgnoreAlarm();
        restoreEchoRegime();
        return -1;
      }
    } else {
      if (num >= 0x4000) {
        writeChar(1, "This number must be < 0x4000");
        if (readUse == 0) restoreIgnoreAlarm();
        restoreEchoRegime();
        return -1;
      }
      mem = num | 0x4000;
    }
    if(sc_memorySet(pos, mem) != 0) {
      if (readUse == 0) restoreIgnoreAlarm();
      restoreEchoRegime();
      return -1;
    }
  } else {
    writeChar(2, "Memory cell is 15 bit wide");
    if (readUse == 0) restoreIgnoreAlarm();
    restoreEchoRegime();
    return -1;
  }
  if (readUse == 0) restoreIgnoreAlarm();
  restoreEchoRegime();
  return 0;
}

int changeAccumulator(int pos){
  int plusFlag = 0, num = 0;
  setIgnoreAlarm();
  setEchoRegime();
  refreshGui(pos);
  mt_gotoXY(1, 23);
  printLine(2);
  mt_gotoXY(1, 23);
  writeChar(1, "Change Accum: ");
  if (scanNum(&plusFlag, &num) != 0) {
    writeChar(2, "Not a number!");
    restoreEchoRegime();
    restoreIgnoreAlarm();
    return -1;
  }
  if ((num >= 0) & (num < 0x4000)) {
    accumulator = num;
  } else {
    writeChar(2, "Accumutalor is 15 bit wide");
    restoreEchoRegime();
    restoreIgnoreAlarm();
    return -1;
  }
  restoreEchoRegime();
  restoreIgnoreAlarm();
  return 0;
}

int changeInstructionPointer(int pos){
  int plusFlag = 0, num = 0;
  setIgnoreAlarm();
  setEchoRegime();
  refreshGui(pos);
  mt_gotoXY(1, 23);
  printLine(2);
  mt_gotoXY(1, 23);
  writeChar(1, "Change Pointer: ");
  if (scanNum(&plusFlag, &num) != 0) {
    writeChar(2, "Not a number!");
    restoreEchoRegime();
    restoreIgnoreAlarm();
    return -1;
  }
  if ((num >= 0) & (num < sizeRAM)) {
    instructionPointer = num;
  } else {
    writeChar(2, "Instruction Pointer range: from 0 to 99 (0x63)");
    restoreEchoRegime();
    restoreIgnoreAlarm();
    return -1;
  }
  restoreEchoRegime();
  restoreIgnoreAlarm();
  return 0;
}

int scanNum(int *plusFlag, int *n){
  char buffer[SIZE_BUFFER] = {0};
  int pos = 0, i = 0;
  setIgnoreAlarm();
  setEchoRegime();
  do {
    read(0, &buffer[i++], 1);
  } while (buffer[i - 1] != '\n');
  buffer[i - 1] = '\0';
  if (buffer[0] == '+') {
    pos = 1;
    *plusFlag = 1;
  } else {
     pos = 0;
    *plusFlag = 0;
  }
  if (sreadInt(buffer + pos, n, SCANPRINTRADIX) != 1) {
    restoreEchoRegime();
    restoreIgnoreAlarm();
    return -1;
  }
  restoreEchoRegime();
  restoreIgnoreAlarm();
  return 0;
}

int memorySave(int position){
  char filename[SIZE_BUFFER] = {0};
  int i = 0;
  setIgnoreAlarm();
  setEchoRegime();
  refreshGui(position);
  mt_gotoXY(1, 23);
  printLine(2);
  mt_gotoXY(1, 23);
  writeChar(1, "Enter save file name: ");
  do {
    read(0, &filename[i++], 1);
  } while (filename[i - 1] != '\n');
  filename[i - 1] = '\0';
  if (sc_memorySave(filename) == 0) {
    refreshGui(position);
    writeChar(1,"File successfully saved.\n");
    restoreEchoRegime();
    restoreIgnoreAlarm();
    return 0;
  } else {
    writeChar(1,"Cannot save file: ");
    writeChar(1, filename);
    writeChar(1,"\n");
    restoreEchoRegime();
    restoreIgnoreAlarm();
    return -1;
  }
  restoreEchoRegime();
  restoreIgnoreAlarm();
  return 0;
}

int memoryLoad(int position){
  char filename[SIZE_BUFFER] = {0};
  int i = 0, err = 0;
  setIgnoreAlarm();
  setEchoRegime();
  refreshGui(position);
  mt_gotoXY(1, 23);
  printLine(2);
  mt_gotoXY(1, 23);
  writeChar(1, "Enter load file name: ");
  do {
    read(0, &filename[i++], 1);
  } while (filename[i - 1] != '\n');
  filename[i - 1] = '\0';
  char* ptr1 = strrchr(filename, '.');
  if (ptr1 != NULL) {
    if (strcmp(ptr1, ".sa") == 0) {
      char* ptr = NULL;
      int size = strlen(filename);
      ptr = malloc(sizeof(char) * size);
      for (i = 0; i < size; i++) ptr[i] = filename[i];
      ptr1[1] = 'o';
      ptr1[2] = '\0';
      char* args[3];
      args[0] = NULL;
      args[1] = filename;
      args[2] = ptr;
      if (asmTrans(3, args) == 1) err = 1;  /* 0, file.o file.sa */
      free(ptr);
    } else if (strcmp(ptr1, ".sb") == 0) {
      char src[SIZE_BUFFER];
      char dest[SIZE_BUFFER];
      strcpy(src, filename); /* file.sb */
      strcpy(dest, filename);
      char* ptr = strchr(dest, '.');
      ptr[1] = 's';
      ptr[2] = 'a';
      ptr[3] = '\0';
      char *argp[3] = {NULL, dest, src};
      if (basicTrans(3, argp) == 1) { /* 0, file.sa file.sb */
        err = 1;
      } else {
        ptr = strchr(src, '.');
        ptr[1] = 's';
        ptr[2] = 'a';
        ptr[3] = '\0';
        ptr = strchr(dest, '.');
        ptr[1] = 'o';
        ptr[2] = '\0';
        argp[1] = dest;
        argp[2] = src;
        if (asmTrans(3, argp) == 1) {
          err = 1;  /* 0, file.o file.sa */
        } else {
          ptr = strchr(filename, '.');
          ptr[1] = 'o';
          ptr[2] = '\0';
        }
      }
    }
  }

  if (!err) {
    if (sc_memoryLoad(filename) == 0) {
      refreshGui(position);
      writeChar(1, "File successfully loaded\n");
      restoreEchoRegime();
      restoreIgnoreAlarm();
      return 0;
    } else {
      writeChar(1,"Cannot load file: ");
      writeChar(1, filename);
      writeChar(1,"\n");
      restoreEchoRegime();
      restoreIgnoreAlarm();
      return -1;
    }
  } else if (err) {
    writeChar(1,"Cannot load file: ");
    writeChar(1, filename);
    writeChar(1,"\n");
    restoreEchoRegime();
    restoreIgnoreAlarm();
    return -1;
  }
  restoreEchoRegime();
  restoreIgnoreAlarm();
  return 0;
}
