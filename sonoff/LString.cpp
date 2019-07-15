
#include <Arduino.h>
#include "LString.h"


LString & LString::toLowerCase(void) {
  for(char *p = _ls->s; *p; p++) {
    *p = tolower(*p);
  }
  return *this;
}


int32_t LString::lastIndexOf(const char * s2, size_t fromIndex) const {
  size_t s2_len = strlen_P(s2);
  size_t my_len = len();
  if (s2_len == 0 || my_len == 0 || s2_len > my_len) return -1;
  if (fromIndex >= my_len) fromIndex = my_len - 1;

  int found = -1;
  for(char *p = _ls->s; p <= _ls->s + fromIndex; p++) {
    p = strstr_P(p, s2);
    if (!p) break;
    if ((unsigned int) (p - _ls->s) <= fromIndex) found = p - _ls->s;
  }
  return found;
}

LString & LString::replace(const char * find, const char * replace) {
  size_t find_len = strlen_P(find);
  size_t replace_len = strlen_P(replace);
  size_t my_len = len();

  if (my_len == 0 || find_len == 0) return *this;

  int32_t diff = replace_len - find_len;
  char *readFrom = _ls->s;
  char *foundAt;
  if (diff == 0) {    // don't change the overall size
    while ((foundAt = strstr_P(readFrom, find)) != NULL) {
      memmove(foundAt, replace, replace_len);
      readFrom = foundAt + replace_len;
    }
  } else if (diff < 0) {  // replacing with a shorter string
    char * writeTo = _ls->s;
    while ((foundAt = strstr_P(readFrom, find)) != NULL) {
      size_t n = foundAt - readFrom;
      memmove(writeTo, readFrom, n);
      writeTo += n;
      memmove(writeTo, replace, replace_len);
      writeTo += replace_len;
      readFrom = foundAt + find_len;
      setLen(len() + diff);
    }
    memmove(writeTo, readFrom, strlen(readFrom)+1);
  } else {
    size_t size = len(); // compute size needed for result
    while ((foundAt = strstr_P(readFrom, find)) != NULL) {
      readFrom = foundAt + find_len;
      size += diff;
    }
    if (size == len()) return *this;
    if (size > _ls->size) return *this; // XXX: tell user!
    size_t index = len() - 1;
    while (index >= 0 && (index = lastIndexOf(find, index)) >= 0) {
      readFrom = _ls->s + index + find_len;
      memmove(readFrom + diff, readFrom, len() - (readFrom - _ls->s));
      int32_t newLen = len() + diff;
      memmove(_ls->s + index, replace, replace_len);
      index--;
    }
  }
  return *this;
}
