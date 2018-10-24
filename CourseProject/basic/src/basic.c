#include "./../include/basic.h"

static var alfabet[26];
static memMap map[SIZE_BUFFER];
static int collision   = 0;
static int indexmap    = 0;
static int begin       = 0;
static int end         = 99;
static int tmp         = -1;
static int tmp1        = 0;
static int flagrepeatjump = 0;
static int indexjmp    = 0;
static int flagend     = 0;
static int celljmp     = 0;
static char readc[11]  = "   READ   \n";
static char writec[12] = "   WRITE   \n";
static char jmpc[11]   = "   JUMP   \n";
static char jneg[11]   = "   JNEG   \n";
static char jns[10]    = "   JNS   \n";
static char haltc[11]  = "   HALT   \n";
static char load[11]   = "   LOAD   \n";
static char store[12]  = "   STORE   \n";
static char add[10]    = "   ADD   \n";
static char mul[10]    = "   MUL   \n";
static char divide[13] = "   DIVIDE   \n";
static char sub[10]    = "   SUB   \n";
static char jz[9]      = "   JZ   \n";

int prior(char c) {      
    switch(c) {
        case '(': return 1;
        case '+': case '-': return 2;
        case '*': case '/': return 3;
        default: return 0;
    }
}
void convert(char *str, char *out) {
  int was_op = 0, np = 0, i;    
  int iin = 0, j = 0;
  struct tLEC *p;
  head = malloc(sizeof(struct tLEC));
  head = NULL;
  for(i = 0; i < strlen(str); i++){
    if (((str[i]>= 'A') && (str[i]<='Z'))||((str[i]>= '0')&&(str[i]<= '9'))) {
      out[j] = str[i];
      j++;
      was_op = 0; 
      continue;
    }
    switch (str[i]) {
      case '(': {
        p = malloc(sizeof(struct tLEC));
        p->dt=str[i];
        p->next=head;
        head=p; 
        ++np; 
        was_op = 0;
        break;
       }
      case '*': case '/': case '+': case '-':{
        if(!was_op) { 
          was_op = 1;
          p=head;
          while(p!=NULL) {
            if (prior(str[i]) <= prior(p->dt)){
              out[j] = p->dt;
              j++;
              p=p->next;
            }
            else break;
          }
          head=p;
          p = calloc(1, sizeof(struct tLEC));
          p->dt=str[i];
          p->next=head;
          head=p;
        }
        break;
      }
      case ')':{
        if(!was_op) {
          p=head;
          while(p->dt!= '(' && np>0) {
            out[j] = p->dt;
            j++;
            p=p->next;
          }
          p=p->next;
        }
        head=p;
        --np;
        break;
      }
      case ' ': break;
    }
  }
  p=head;
  while(p!=NULL){
    out[j] = p->dt;
    j++;
    p=p->next;
  }
  out[j]='\0';
}

int keywordCode(char *str){
  if (strcmp(str, "REM") == 0) {
    return KEYW_REM;
  } else if (strcmp(str, "INPUT") == 0) {
    return KEYW_INPUT;
  } else if (strcmp(str, "OUTPUT") == 0) {
    return KEYW_OUTPUT;
  } else if (strcmp(str, "GOTO") == 0) {
    return KEYW_GOTO;
  } else if (strcmp(str, "IF") == 0) {
    return KEYW_IF;
  } else if (strcmp(str, "LET") == 0) {
    return KEYW_LET;
  } else if ((strcmp(str, "END") == 0) || (strcmp(str, "END\n") == 0)) {
    return KEYW_END;
  } else {
    return KEYW_E;
  }
}

int basicTrans(int argc, char *argv[]){
  int input = 0, output = 0, readcount;
  char buffer[SIZE_BUFFER] = {0};
  int i = 0, addres = 5, value = 0;
  char *ptr= NULL;
  int ret = 0, BR = 0;
  tmp = -1;
  tmp1 = 0;
  begin = 0;
  end = 99;
  collision = 0;
  indexmap = 0;
  celljmp = 0;
  flagend = 0;
  flagrepeatjump= 0;

  if ((input = open(argv[2], O_RDONLY)) == -1) return 1;
  if ((output = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, 0666)) == -1) return 1;
  for (i = 0; i < 26; i++) {
    alfabet[i].variable = 0;
    alfabet[i].name[0] = 'A' + i;
    alfabet[i].name[1] = '\0';
  }
  for (i = 0; i < SIZE_BUFFER; i++) {
    map[i].real = -1;
    map[i].expect = -1;
  }
  i = 0;
  do {
    readcount = read(input, &buffer[i], sizeof(char));
    if (readcount == 0) break;
    if (buffer[i] == TOKENSYMB) {
      if (buffer[i - 1] == TOKENSYMB) {
        continue;
      }
    }
    if (buffer[i] == ' ') {
      if (buffer[i - 1] == ' ') {
        continue;
      }
    }
    if (buffer[i] == '\n' | (buffer[i] == EOF) ) {
      if (buffer[i] == EOF) {
        BR = 1;
      }
      buffer[i] = '\0';
      ret = parsingLineB(buffer, output);
      BR = ret;
      if (BR == 1) break;
      if (BR == 2) return 1;
      i = -1;
    }
    i++;
  } while (1);
  close(input);
  printf("\n\n\n");
  /*for(i = 0; i < indexmap; i++){
    printf("%d       %d\n", map[i].real, map[i].expect);
  }*/
  close(output);
  if ((output = open(argv[1], O_RDONLY, 0666)) == -1) return 1;
  char c[4096];
  i = 0;
  do {
    readcount = read(output, &c[i++], 1);
  } while (readcount > 0);
  close(output);
  if ((output = open(argv[1], O_WRONLY | O_TRUNC, 0666)) == -1) return 1;
  int j, e, cl = -1;
  for (j = 0; j < i; j++){
    if (0 <= c[j] - '!' && c[j] - '!' <= 9) {
      cl = (c[j] - '!') * 10 + (c[j+1] - '!');
      break;
    }
  }
  for (e = 0; e < indexmap; ++e)
    if (map[e].expect == cl){
     cl = map[e].real;
      break;
    }
  c[j] = cl / 10 + '0';
  c[j + 1] = cl % 10 + '0';
  e = 0;
  while (e < i) {
    write(output,&c[e++],1);
  }
  close(output);
  /*for(i = 0; i < indexmap; i++){
    printf("%d       %d\n", map[i].real, map[i].expect);
  }*/
  //for(j = 0; j < 10000000000; j++);
  return 0;
}

int parsingLineB(char* str, int output){
  char tmpPtr1[256];
  char* ptr    = str;
  char* tmpPtr = ptr;
  char* op     = NULL;
  char* oplet  = NULL;
  int command = 0, operand = 0, i = 0, j = 0, k = 0, q = 0, z = 0;
  int ret = 0, cmp = 0, flagJump = 0, len, sum = 0, sk = 0, lastWrite = 0;
  while (1) {
    if (tmpPtr[i] == TOKENSYMB) {
      ptr = tmpPtr + i + 1;
      tmpPtr[i] = '\0';
      break;
    } else if (tmpPtr[i] == EOF) {
      return 0;
    }
    i++;
  }
  if (!(str[0] >= '0' & str[0] <= '9')) {
    return 0;
  }
  if (tmp1 > 0)
    tmp = tmp1;
    sreadInt(tmpPtr, &tmp1, 10);
    if (tmp1 <= tmp) {
    return 2;
  }

  i = 0;
  tmpPtr = ptr;
  while (1) {
    if (tmpPtr[i] == TOKENSYMB) {
      ptr = tmpPtr + i + 1;
      tmpPtr[i] = '\0';
      break;
    }
    i++;
  }
  ret = keywordCode(tmpPtr);
  tmpPtr = ptr;

  if (ret == KEYW_IF) {
    i = 0;
    while (1) {
      if (tmpPtr[i] == TOKENSYMB) {
        ptr = tmpPtr + i + 1;
        tmpPtr[i] = '\0';
        break;
      }
      i++;
    }
    if (*tmpPtr >= 'A' & *tmpPtr <= 'Z') {
      for (i = 0; i < 26; i++) {
        if (!strcmp(alfabet[i].name, tmpPtr)) {
          if (!(alfabet[i].variable == 1)) {
            return 2;
          }
          tmpPtr = ptr;
          j = 0;
          while (1) {
            if (tmpPtr[j] == TOKENSYMB) {
              ptr = tmpPtr + j + 1;
              tmpPtr[j] = '\0';
              break;
            }
            j++;
          }
          map[indexmap].real = begin;
          map[indexmap].expect = tmp1;
          ++indexmap;
          op = tmpPtr;
          tmpPtr = ptr;
          load[0] = (begin - collision) / 10 + '0';
          load[1] = (begin++ - collision) % 10 + '0';
          load[8] = alfabet[i].cell / 10 + '0';
          load[9] = alfabet[i].cell % 10 + '0';
          write(output, load, sizeof(char) * strlen(load));
          j = 0;
          while (1) {
            if (tmpPtr[j] == TOKENSYMB) {
              ptr = tmpPtr + j + 1;
              tmpPtr[j] = '\0';
              break;
            }
            j++;
          }
          if (*tmpPtr >= 'A' & *tmpPtr <= 'Z') {
            for (j = 0; j < 26; j++) {
              if (!strcmp(alfabet[j].name, tmpPtr)) {
                tmpPtr = ptr;
                if (!(alfabet[j].variable == 1)) {
                  return 2;
                }
                sub[0] = (begin - collision) / 10 + '0';
                sub[1] = (begin++ - collision) % 10 + '0';
                sub[7] = alfabet[j].cell / 10 + '0';
                sub[8] = alfabet[j].cell % 10 + '0';
                write(output, sub, sizeof(char) * strlen(sub));
                break;
              }
            }

          } else {
            int number = atoi(tmpPtr);
            int addr = end--;
            char buf[4];
            swriteInt(buf, number, 16, 4);
            char s = (addr) / 10 + '0';
            write(output, &s, 1);
            s = (addr) % 10 + '0';
            write(output, &s, 1);
            write(output, TOKENSYMBS, 1);
            write(output, "=", 1);
            write(output, TOKENSYMBS, 1);
            write(output, buf, 4);
            write(output, "\n", 1);

            sub[0] = (begin - collision) / 10 + '0';
            sub[1] = (begin++ - collision) % 10 + '0';
            sub[7] = addr / 10 + '0';
            sub[8] = addr % 10 + '0';
            write(output, sub, sizeof(char) * strlen(sub));
          }
        }
      }
    } else {
      int number = atoi(tmpPtr);
      int addr = end--;
      char buf[4];
      swriteInt(buf, number, 16, 4);
      char s = (addr) / 10 + '0';
      write(output, &s, 1);
      s = (addr) % 10 + '0';
      write(output, &s, 1);
      write(output, TOKENSYMBS, 1);
      write(output, "=", 1);
      write(output, TOKENSYMBS, 1);
      write(output, buf, 4);
      write(output, "\n", 1);
      load[0] = (begin - collision) / 10 + '0';
      load[1] = (begin++ - collision) % 10 + '0';
      load[8] = addr / 10 + '0';
      load[9] = addr % 10 + '0';
      write(output, load, sizeof(char) * strlen(load));

      tmpPtr = ptr;
      j = 0;
      while (1) {
        if (tmpPtr[j] == TOKENSYMB) {
          ptr = tmpPtr + j + 1;
          tmpPtr[j] = '\0';
          break;
        }
        j++;
      }
      op = tmpPtr;
      tmpPtr = ptr;
      j = 0;
      while (1) {
        if (tmpPtr[j] == TOKENSYMB) {
          ptr = tmpPtr + j + 1;
          tmpPtr[j] = '\0';
          break;
        }
        j++;
      }
      if (*tmpPtr >= 'A' & *tmpPtr <= 'Z') {
        for (j = 0; j < 26; j++) {
          if (!strcmp(alfabet[j].name, tmpPtr)) {
            tmpPtr = ptr;
            if (!(alfabet[j].variable == 1)) {
              return 2;
            }
            sub[0] = (begin - collision) / 10 + '0';
            sub[1] = (begin++ - collision) % 10 + '0';
            sub[7] = alfabet[j].cell / 10 + '0';
            sub[8] = alfabet[j].cell % 10 + '0';
            write(output, sub, sizeof(char) * strlen(sub));
            break;
          }
        }
      } else {
        number = atoi(tmpPtr);
        addr = end--;
        swriteInt(buf, number, 16, 4);
        char s = (addr) / 10 + '0';
        write(output, &s, 1);
        s = (addr) % 10 + '0';
        write(output, &s, 1);
        write(output, TOKENSYMBS, 1);
        write(output, "=", 1);
        write(output, TOKENSYMBS, 1);
        write(output, buf, 4);
        write(output, "\n", 1);
        sub[0] = (begin - collision) / 10 + '0';
        sub[1] = (begin++ - collision) % 10 + '0';
        sub[7] = addr / 10 + '0';
        sub[8] = addr % 10 + '0';
        write(output, sub, sizeof(char) * strlen(sub));
      }
    }
    tmpPtr = ptr;
    j = 0;
    while (1) {
      if (tmpPtr[j] == TOKENSYMB) {
        ptr = tmpPtr + j + 1;
        tmpPtr[j] = '\0';
        break;
      }
      j++;
    }
    ret = keywordCode(tmpPtr);
    tmpPtr = ptr;
    flagJump = 1;
  }

  if (ret == KEYW_GOTO | (flagrepeatjump == 1 & flagend == 1)) {
    if (flagJump == 1) {
      flagJump = 0;
      int ret = ifoperation(output, op, 0, 0);
      if (ret == -1) {
        return -1;
      }
    }
    jmpc[0] = (begin - collision) / 10 + '0';
    jmpc[1] = (begin - collision) % 10 + '0';
    map[indexmap].real = begin;
    map[indexmap].expect = tmp1;
    ++indexmap;
    int cell = (tmpPtr[0] - '0') * 10 + (tmpPtr[1] - '0');
    for (i = 0; i < indexmap; i++) {
      if ((cell == map[i].expect)) {
        if (map[i].real == -1) {
          return 2;
        }
        cell = map[i].real;
        jmpc[8] = (cell) / 10 + '0';
        jmpc[9] = (cell) % 10 + '0';
        break;
      }
    }
    if (i == indexmap) {
    jmpc[8] = (cell) / 10 + '!';
    jmpc[9] = (cell) % 10 + '!';
    }
      ++begin;
      write(output, jmpc, sizeof(char) * strlen(jmpc));

  }

  if (ret == KEYW_REM) {
    map[indexmap].real = -1;
    map[indexmap].expect = tmp1;
    ++indexmap;
    return 0;
  } else if (ret == KEYW_INPUT) {
    if (flagJump == 1) {
      flagJump = 0;
      int ret = ifoperation(output, op, 0, 0);
      if (ret == -1) {
        return -1;
      }
    }
    for (i = 0; i < 26; i++) {
      if (!strcmp(alfabet[i].name, tmpPtr)) {
        if (end - 1 < begin) {
          return 2;
        }
        alfabet[i].cell = end--;
        if (alfabet[i].variable == 0) {
          alfabet[i].variable = 1;
        }
        map[indexmap].real = begin;
        map[indexmap].expect = tmp1;
        ++indexmap;
        readc[0] = (begin - collision) / 10 + '0';
        readc[1] = (begin++ - collision) % 10 + '0';
        readc[8] = alfabet[i].cell / 10 + '0';
        readc[9] = alfabet[i].cell % 10 + '0';
        write(output, readc, sizeof(char) * strlen(readc));
        break;
      }
    }
  } else if (ret == KEYW_OUTPUT) {
    if (flagJump == 1) {
      flagJump = 0;
      int ret = ifoperation(output, op, 0, 0);
      if (ret == -1) {
        return -1;
      }
    }
    for (i = 0; i < 26; i++) {
      if (!strcmp(alfabet[i].name, tmpPtr)) {
        tmpPtr = ptr;
        if (end - 1 < begin) {
          return 2;
        }

        if (!(alfabet[i].variable == 1)) {
          return 2;
        }
        map[indexmap].real = begin;
        map[indexmap].expect = tmp1;
        ++indexmap;
        writec[0] = (begin - collision) / 10 + '0';
        writec[1] = (begin++ - collision) % 10 + '0';
        writec[9] = alfabet[i].cell / 10 + '0';
        writec[10] = alfabet[i].cell % 10 + '0';
        write(output, writec, sizeof(char) * strlen(writec));
        break;
      }
    }
  } else if (ret == KEYW_LET) {
    len = strlen(ptr);
    for(i = 0; i < len; i++){
      if (ptr[i] == '+' || ptr[i] == '-'||
             ptr[i] == '/'|| ptr[i] == '*') sk++;
    }
    if (flagJump == 1) {
      flagJump = 0;
      int ret = ifoperation(output, op, 1, sk);
      if (ret == -1) return -1;
    }
    j = 0;
    while (1) {
      if (tmpPtr[j] == TOKENSYMB) {
        ptr = tmpPtr + j + 1;
        tmpPtr[j] = '\0';
        break;
      }
      j++;
    }
    for (k = 0; k < 26; k++) {
      if (!strcmp(alfabet[k].name, tmpPtr)) {
        tmpPtr = ptr;
        if (alfabet[k].variable == 0) {
          if (end - 1 < begin) return 2;
          alfabet[k].variable = 1;
          alfabet[k].cell = end--;
        }
        map[indexmap].real = begin;
        map[indexmap].expect = tmp1;
        ++indexmap;
        break;
      }
    }
    j = 0;
    while (1) {
      if (tmpPtr[j] == TOKENSYMB) {
        ptr = tmpPtr + j + 1;
        tmpPtr[j] = '\0';
        break;
      }
      j++;
    }
    if (!(strcmp(tmpPtr, "=") == 0)) return 2;
    convert(ptr, tmpPtr1);
    tmpPtr = ptr;
    len = strlen(tmpPtr1);
    if (sk == 0){
      if (tmpPtr1[0] >= '0' && tmpPtr1[0] <= '9'){
        int number = atoi(&tmpPtr1[0]);
        int addr = end--;
        char buf[4];
        swriteInt(buf, number, 16, 4);
        char s = (addr) / 10 + '0';
        write(output, &s, 1);
        s = (addr) % 10 + '0';
        write(output, &s, 1);
        write(output, TOKENSYMBS, 1);
        write(output, "=", 1);
        write(output, TOKENSYMBS, 1);
        write(output, buf, 4);
        write(output, "\n", 1);
        load[0] = (begin - collision) / 10 + '0';
        load[1] = (begin++ - collision) % 10 + '0';
        load[8] = addr / 10 + '0';
        load[9] = addr % 10 + '0';
        write(output, load, sizeof(char) * strlen(load));
        store[0] = (begin - collision) / 10 + '0';
        store[1] = (begin++ - collision) % 10 + '0';
        store[9] = alfabet[k].cell / 10 + '0';
        store[10] = alfabet[k].cell % 10 + '0';
        write(output, store, sizeof(char) * strlen(store));
      } else if (tmpPtr1[0] >= 'A' && tmpPtr1[0] <= 'Z'){
        for (i = 0; i < 26; i++){
          if (tmpPtr1[0] == alfabet[i].name[0]) break;
        }
        if (i == 26) return 2;
        load[0] = (begin - collision) / 10 + '0';
        load[1] = (begin++ - collision) % 10 + '0';
        load[8] = alfabet[i].cell / 10 + '0';
        load[9] = alfabet[i].cell % 10 + '0';
        write(output, load, sizeof(char) * strlen(load));
        store[0] = (begin - collision) / 10 + '0';
        store[1] = (begin++ - collision) % 10 + '0';
        store[9] = alfabet[k].cell / 10 + '0';
        store[10] = alfabet[k].cell % 10 + '0';
        write(output, store, sizeof(char) * strlen(store));
      } else return 2;
      return 0;
    }
    while(sk != 0){
      long long x, pp;
      //printf("%s\n", tmpPtr1);
     // for(pp = 0; pp < 9000000000; pp++);
      int kk = 0;
      for(i = 0; i < len; i++){
        if (tmpPtr1[i] == '+' || tmpPtr1[i] == '-' ||
               tmpPtr1[i] == '*' || tmpPtr1[i] == '/') break;
      }
      for (j = 0; j < 26; j++){
        if (alfabet[j].name[0] == tmpPtr1[i-2]){
          break;
        }
      }
      for (q = 0; q < 26; q++){
        if (alfabet[q].name[0] == tmpPtr1[i-1]){
          break;
        }
      }
      if (alfabet[j].variable == 1 && alfabet[q].variable == 1) {
        load[0] = (begin - collision) / 10 + '0';
        load[1] = (begin++ - collision) % 10 + '0';
        load[8] = alfabet[j].cell / 10 + '0';
        load[9] = alfabet[j].cell % 10 + '0';
        write(output, load, sizeof(char) * strlen(load));
        switch(tmpPtr1[i]) {
          case '+': {
            add[0] = (begin - collision) / 10 + '0';
            add[1] = (begin++ - collision) % 10 + '0';
            add[7] = alfabet[q].cell / 10 + '0';
            add[8] = alfabet[q].cell % 10 + '0';
            write(output, add, sizeof(char) * strlen(add));
            break;
          }
          case '-': {
            sub[0] = (begin - collision) / 10 + '0';
            sub[1] = (begin++ - collision) % 10 + '0';
            sub[7] = alfabet[q].cell / 10 + '0';
            sub[8] = alfabet[q].cell % 10 + '0';
            write(output, sub, sizeof(char) * strlen(sub));
            break;
          }
          case '*': {
            mul[0] = (begin - collision) / 10 + '0';
            mul[1] = (begin++ - collision) % 10 + '0';
            mul[7] = alfabet[q].cell / 10 + '0';
            mul[8] = alfabet[q].cell % 10 + '0';
            write(output, mul, sizeof(char) * strlen(mul));
            break;
          }
          case '/': {
            divide[0] = (begin - collision) / 10 + '0';
            divide[1] = (begin++ - collision) % 10 + '0';
            divide[10] = alfabet[q].cell / 10 + '0';
            divide[11] = alfabet[q].cell % 10 + '0';
            write(output, divide, sizeof(char) * strlen(divide));
            break;
          }
        }
        for (z = 25; z > 0; z--) {
          if (alfabet[z].variable == 0) {
            if (end - 1 < begin) return 2;
            alfabet[z].variable = 1;
            alfabet[z].cell = end--;
            map[indexmap].real = begin;
            map[indexmap].expect = tmp1;
            ++indexmap;
            break;
          }
        }
        store[0] = (begin - collision) / 10 + '0';
        store[1] = (begin++ - collision) % 10 + '0';
        store[9] = alfabet[z].cell / 10 + '0';
        store[10] = alfabet[z].cell % 10 + '0';
        lastWrite = z;
        write(output, store, sizeof(char) * strlen(store));
        tmpPtr1[i] = alfabet[z].name[0];
        tmpPtr1[i-1] = '!';
        tmpPtr1[i-2] = '!';
        len = strlen(tmpPtr1);
        for(int p = 0; p < 10; p++)
          for(j = 0; j < len; j++){
            if(tmpPtr1[j] == '!'){
              len--;
              for(kk = j; kk < len; kk++){
                tmpPtr1[kk] = tmpPtr1[kk+1]; 
              }
              tmpPtr1[kk] = '\0';
            }
          }
      sk--;
      }else if (!(alfabet[j].variable == 1) && alfabet[q].variable == 1){
        int number = atoi(&tmpPtr1[i-2]);
        int addr = end--;
        char buf[4];
        swriteInt(buf, number, 16, 4);
        char s = (addr) / 10 + '0';
        write(output, &s, 1);
        s = (addr) % 10 + '0';
        write(output, &s, 1);
        write(output, TOKENSYMBS, 1);
        write(output, "=", 1);
        write(output, TOKENSYMBS, 1);
        write(output, buf, 4);
        write(output, "\n", 1);
        load[0] = (begin - collision) / 10 + '0';
        load[1] = (begin++ - collision) % 10 + '0';
        load[8] = addr / 10 + '0';
        load[9] = addr % 10 + '0';
        write(output, load, sizeof(char) * strlen(load));
        switch(tmpPtr1[i]) {
          case '+': {
            add[0] = (begin - collision) / 10 + '0';
            add[1] = (begin++ - collision) % 10 + '0';
            add[7] = alfabet[q].cell / 10 + '0';
            add[8] = alfabet[q].cell % 10 + '0';
            write(output, add, sizeof(char) * strlen(add));
            break;
          }
          case '-': {
            sub[0] = (begin - collision) / 10 + '0';
            sub[1] = (begin++ - collision) % 10 + '0';
            sub[7] = alfabet[q].cell / 10 + '0';
            sub[8] = alfabet[q].cell % 10 + '0';
            write(output, sub, sizeof(char) * strlen(sub));
            break;
          }
          case '*': {
            mul[0] = (begin - collision) / 10 + '0';
            mul[1] = (begin++ - collision) % 10 + '0';
            mul[7] = alfabet[q].cell / 10 + '0';
            mul[8] = alfabet[q].cell % 10 + '0';
            write(output, mul, sizeof(char) * strlen(mul));
            break;
          }
          case '/': {
            divide[0] = (begin - collision) / 10 + '0';
            divide[1] = (begin++ - collision) % 10 + '0';
            divide[10] = alfabet[q].cell / 10 + '0';
            divide[11] = alfabet[q].cell % 10 + '0';
            write(output, divide, sizeof(char) * strlen(divide));
            break;
          }
        }
        for (z = 25; z > 0; z--) {
          if (alfabet[z].variable == 0) {
            if (end - 1 < begin) return 2;
            alfabet[z].variable = 1;
            alfabet[z].cell = end--;
            map[indexmap].real = begin;
            map[indexmap].expect = tmp1;
            ++indexmap;
            break;
          }
        }
        store[0] = (begin - collision) / 10 + '0';
        store[1] = (begin++ - collision) % 10 + '0';
        store[9] = alfabet[z].cell / 10 + '0';
        store[10] = alfabet[z].cell % 10 + '0';
        lastWrite = z;
        write(output, store, sizeof(char) * strlen(store));
        tmpPtr1[i] = alfabet[z].name[0];
        tmpPtr1[i-1] = '!';
        tmpPtr1[i-2] = '!';
        len = strlen(tmpPtr1);
        for(int p = 0; p < 10; p++)
          for(j = 0; j < len; j++){
            if(tmpPtr1[j] == '!'){
              len--;
              for(kk = j; kk < len; kk++){
                tmpPtr1[kk] = tmpPtr1[kk+1]; 
              }
              tmpPtr1[kk] = '\0';
            }
          }
      sk--; 
      }else if (!(alfabet[q].variable == 1) && alfabet[j].variable == 1){
        load[0] = (begin - collision) / 10 + '0';
        load[1] = (begin++ - collision) % 10 + '0';
        load[8] = alfabet[j].cell / 10 + '0';
        load[9] = alfabet[j].cell % 10 + '0';
        write(output, load, sizeof(char) * strlen(load));
        int number = atoi(&tmpPtr1[i-1]);
        int addr = end--;
        char buf[4];
        swriteInt(buf, number, 16, 4);
        char s = (addr) / 10 + '0';
        write(output, &s, 1);
        s = (addr) % 10 + '0';
        write(output, &s, 1);
        write(output, TOKENSYMBS, 1);
        write(output, "=", 1);
        write(output, TOKENSYMBS, 1);
        write(output, buf, 4);
        write(output, "\n", 1);
        write(output, load, sizeof(char) * strlen(load));
        switch(tmpPtr1[i]) {
          case '+': {
            add[0] = (begin - collision) / 10 + '0';
            add[1] = (begin++ - collision) % 10 + '0';
            add[7] = addr / 10 + '0';
            add[8] = addr % 10 + '0';
            write(output, add, sizeof(char) * strlen(add));
            break;
          }
          case '-': {
            sub[0] = (begin - collision) / 10 + '0';
            sub[1] = (begin++ - collision) % 10 + '0';
            sub[7] = addr / 10 + '0';
            sub[8] = addr % 10 + '0';
            write(output, sub, sizeof(char) * strlen(sub));
            break;
          }
          case '*': {
            mul[0] = (begin - collision) / 10 + '0';
            mul[1] = (begin++ - collision) % 10 + '0';
            mul[7] = addr / 10 + '0';
            mul[8] = addr % 10 + '0';
            write(output, mul, sizeof(char) * strlen(mul));
            break;
          }
          case '/': {
            divide[0] = (begin - collision) / 10 + '0';
            divide[1] = (begin++ - collision) % 10 + '0';
            divide[10] = addr / 10 + '0';
            divide[11] = addr % 10 + '0';
            write(output, divide, sizeof(char) * strlen(divide));
            break;
          }
        }
        for (z = 25; z > 0; z--) {
          if (alfabet[z].variable == 0) {
            if (end - 1 < begin) return 2;
            alfabet[z].variable = 1;
            alfabet[z].cell = end--;
            map[indexmap].real = begin;
            map[indexmap].expect = tmp1;
            ++indexmap;
            break;
          }
        }
        store[0] = (begin - collision) / 10 + '0';
        store[1] = (begin++ - collision) % 10 + '0';
        store[9] = alfabet[z].cell / 10 + '0';
        store[10] = alfabet[z].cell % 10 + '0';
        lastWrite = z;
        write(output, store, sizeof(char) * strlen(store));
        tmpPtr1[i] = alfabet[z].name[0];
        tmpPtr1[i-1] = '!';
        tmpPtr1[i-2] = '!';
        len = strlen(tmpPtr1);
        for(int p = 0; p < 10; p++)
          for(j = 0; j < len; j++){
            if(tmpPtr1[j] == '!'){
              len--;
              for(kk = j; kk < len; kk++){
                tmpPtr1[kk] = tmpPtr1[kk+1]; 
              }
              tmpPtr1[kk] = '\0';
            }
          }
        sk--;
      } else {
          char l = tmpPtr1[i-2];
          int number = atoi(&l);
          int addr = end--;
          char buf[4];
          swriteInt(buf, number, 16, 4);
          char s = (addr) / 10 + '0';
          write(output, &s, 1);
          s = (addr) % 10 + '0';
          write(output, &s, 1);
          write(output, TOKENSYMBS, 1);
          write(output, "=", 1);
          write(output, TOKENSYMBS, 1);
          write(output, buf, 4);
          write(output, "\n", 1);
          load[0] = (begin - collision) / 10 + '0';
          load[1] = (begin++ - collision) % 10 + '0';
          load[8] = addr / 10 + '0';
          load[9] = addr % 10 + '0';
          write(output, load, sizeof(char) * strlen(load));
          char ll = tmpPtr1[i-1];
          number = atoi(&ll);
          addr = end--;
          swriteInt(buf, number, 16, 4);
          s = (addr) / 10 + '0';
          write(output, &s, 1);
          s = (addr) % 10 + '0';
          write(output, &s, 1);
          write(output, TOKENSYMBS, 1);
          write(output, "=", 1);
          write(output, TOKENSYMBS, 1);
          write(output, buf, 4);
          write(output, "\n", 1);
          switch(tmpPtr1[i]) {
            case '+': {
              add[0] = (begin - collision) / 10 + '0';
              add[1] = (begin++ - collision) % 10 + '0';
              add[7] = addr / 10 + '0';
              add[8] = addr % 10 + '0';
              write(output, add, sizeof(char) * strlen(add));
              break;
            }
            case '-': {
              sub[0] = (begin - collision) / 10 + '0';
              sub[1] = (begin++ - collision) % 10 + '0';
              sub[7] = addr / 10 + '0';
              sub[8] = addr % 10 + '0';
              write(output, sub, sizeof(char) * strlen(sub));
              break;
            }
            case '*': {
              mul[0] = (begin - collision) / 10 + '0';
              mul[1] = (begin++ - collision) % 10 + '0';
              mul[7] = addr / 10 + '0';
              mul[8] = addr % 10 + '0';
              write(output, mul, sizeof(char) * strlen(mul));
              break;
            }
            case '/': {
              divide[0] = (begin - collision) / 10 + '0';
              divide[1] = (begin++ - collision) % 10 + '0';
              divide[10] = addr / 10 + '0';
              divide[11] = addr % 10 + '0';
              write(output, divide, sizeof(char) * strlen(divide));
              break;
            }
          }
          for (z = 25; z > 0; z--) {
            if (alfabet[z].variable == 0) {
              if (end - 1 < begin) return 2;
              alfabet[z].variable = 1;
              alfabet[z].cell = end--;
              map[indexmap].real = begin;
              map[indexmap].expect = tmp1;
              ++indexmap;
              break;
            }
          }
          store[0] = (begin - collision) / 10 + '0';
          store[1] = (begin++ - collision) % 10 + '0';
          store[9] = alfabet[z].cell / 10 + '0';
          store[10] = alfabet[z].cell % 10 + '0';
          lastWrite = z;
          write(output, store, sizeof(char) * strlen(store));
          tmpPtr1[i] = alfabet[z].name[0];
          tmpPtr1[i-1] = '!';
          tmpPtr1[i-2] = '!';
          len = strlen(tmpPtr1);
          for(int p=0; p < 10; p++)
            for(j = 0; j < len; j++){
              if(tmpPtr1[j] == '!'){
                len--;
                for(kk = j; kk < len; kk++){
                  tmpPtr1[kk] = tmpPtr1[kk+1]; 
                }
                tmpPtr1[kk] = '\0';
              }
            }
          sk--;
      }
    }
    load[0] = (begin - collision) / 10 + '0';
    load[1] = (begin++ - collision) % 10 + '0';
    load[8] = alfabet[lastWrite].cell / 10 + '0';
    load[9] = alfabet[lastWrite].cell % 10 + '0';
    write(output, load, sizeof(char) * strlen(load));
    store[0] = (begin - collision) / 10 + '0';
    store[1] = (begin++ - collision) % 10 + '0';
    store[9] = alfabet[k].cell / 10 + '0';
    store[10] = alfabet[k].cell % 10 + '0';
    write(output, store, sizeof(char) * strlen(store));    
    if (k == 26) return 2;
  } else if (ret == KEYW_END) {
    flagend = 1;
    if (flagJump == 1) {
      flagJump = 0;
      int ret = ifoperation(output, op, 0, 0);
      if (ret == -1) {
        return -1;
      }
    }
    map[indexmap].real = begin;
    map[indexmap].expect = tmp1;
    ++indexmap;
    haltc[0] = (begin - collision) / 10 + '0';
    haltc[1] = (begin++ - collision) % 10 + '0';
    haltc[8] = '0';
    haltc[9] = '0';
    write(output, haltc, sizeof(char) * strlen(haltc));
    return 0;
  } else if (ret == KEYW_E) {
    return 0;
  }
  return 0;
}

int ifoperation(int output, char* op, int let, int zn){
  if (let == 0) {
    if (!strcmp(op, ">")) {
      jz[0] = (begin - collision) / 10 + '0';
      jz[1] = (begin - collision) % 10 + '0';
      jz[6] = (begin + 3) / 10 + '0';
      jz[7] = (begin++ + 3) % 10 + '0';
      write(output, jz, sizeof(char) * strlen(jz));
      jneg[0] = (begin - collision) / 10 + '0';
      jneg[1] = (begin - collision) % 10 + '0';
      jneg[8] = (begin + 2) / 10 + '0';
      jneg[9] = (begin++ + 2) % 10 + '0';
      write(output, jneg, sizeof(char) * strlen(jneg));
      return 0;
    } else if (!strcmp(op, "<")) {
      jns[0] = (begin - collision) / 10 + '0';
      jns[1] = (begin - collision) % 10 + '0';
      jns[7] = (begin + 3) / 10 + '0';
      jns[8] = (begin++ + 3) % 10 + '0';
      write(output, jns, sizeof(char) * strlen(jns));
      jz[0] = (begin - collision) / 10 + '0';
      jz[1] = (begin - collision) % 10 + '0';
      jz[6] = (begin + 2) / 10 + '0';
      jz[7] = (begin++ + 2) % 10 + '0';
      write(output, jz, sizeof(char) * strlen(jz));
      return 0;
    } else if (!strcmp(op, "=")) {
      jneg[0] = (begin - collision) / 10 + '0';
      jneg[1] = (begin - collision) % 10 + '0';
      jneg[8] = (begin + 3) / 10 + '0';
      jneg[9] = (begin++ + 3) % 10 + '0';
      write(output, jneg, sizeof(char) * strlen(jneg));
      jns[0] = (begin - collision) / 10 + '0';
      jns[1] = (begin - collision) % 10 + '0';
      jns[7] = (begin + 2) / 10 + '0';
      jns[8] = (begin++ + 2) % 10 + '0';
      write(output, jns, sizeof(char) * strlen(jns));
      return 0;
    } else {
      return 1;
    }
  } else if (let == 1) {
      if (!strcmp(op, ">")) {
        jz[0] = (begin - collision) / 10 + '0';
        jz[1] = (begin - collision) % 10 + '0';
        jz[6] = (begin + (3 * zn + 4)) / 10 + '0';
        jz[7] = (begin++ + (3 * zn + 4)) % 10 + '0';
        write(output, jz, sizeof(char) * strlen(jz));
        jneg[0] = (begin - collision) / 10 + '0';
        jneg[1] = (begin - collision) % 10 + '0';
        jneg[8] = (begin + (3 * zn + 3)) / 10 + '0';
        jneg[9] = (begin++ + (3 * zn + 3)) % 10 + '0';
        write(output, jneg, sizeof(char) * strlen(jneg));
        return 0;
      } else if (!strcmp(op, "<")) {
        jns[0] = (begin - collision) / 10 + '0';
        jns[1] = (begin - collision) % 10 + '0';
        jns[7] = (begin + (3 * zn + 4)) / 10 + '0';
        jns[8] = (begin++ + (3 * zn + 4)) % 10 + '0';
        write(output, jns, sizeof(char) * strlen(jns));
        jz[0] = (begin - collision) / 10 + '0';
        jz[1] = (begin - collision) % 10 + '0';
        jz[6] = (begin + (3 * zn + 3)) / 10 + '0';
        jz[7] = (begin++ + (3 * zn + 3)) % 10 + '0';
        write(output, jz, sizeof(char) * strlen(jz));
        return 0;
      } else if (!strcmp(op, "=")) {
        jneg[0] = (begin - collision) / 10 + '0';
        jneg[1] = (begin - collision) % 10 + '0';
        jneg[8] = (begin + (3 * zn + 4)) / 10 + '0';
        jneg[9] = (begin++ + (3 * zn + 4)) % 10 + '0';
        write(output, jneg, sizeof(char) * strlen(jneg));
        jns[0] = (begin - collision) / 10 + '0';
        jns[1] = (begin - collision) % 10 + '0';
        jns[7] = (begin + (3 * zn + 3)) / 10 + '0';
        jns[8] = (begin++ + (3 * zn + 3)) % 10 + '0';
        write(output, jns, sizeof(char) * strlen(jns));
        return 0;
      } else {
        return 1;
      }
  }
}
