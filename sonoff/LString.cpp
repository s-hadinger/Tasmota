
#include <Arduino.h>
#include "LString.h"


void LString::toLowerCase(void) {
  for(char *p = _ls->s; *p; p++) {
    *p = tolower(*p);
  }
}
