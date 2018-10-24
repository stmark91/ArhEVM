#ifndef READ_KEY_H
#define READ_KEY_H

#include "./../../simpleComputer/include/sc_register.h"
#include "./../../simpleComputer/include/sc_command.h"
#include "./../../simpleComputer/include/sc_memory.h"
#include "./../../bc/include/bc.h"
#include "./../../consoleSC/include/term.h"

#include <termios.h>
#include <string.h>

enum keys {
  KEY_l = 0,
  KEY_s,
  KEY_r,
  KEY_t,
  KEY_i,
  KEY_x,
  KEY_d,
  KEY_c,
  KEY_q,
  KEY_f5,
  KEY_f6,
  KEY_up,
  KEY_down,
  KEY_left,
  KEY_right,
  KEY_enter,
  KEY_esc,
  KEY_other
};

int rk_readkey(enum keys *key);
int rk_mytermsave(void);
int rk_mytermrestore(void);
int rk_mytermregime(int regime, int vtime, int vmin, int echo, int sigint);

#endif
