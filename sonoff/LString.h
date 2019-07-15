

#ifndef _SONOFF_LSTRING_H_
#define _SONOFF_LSTRING_H_

#include <pgmspace.h>
#include <WString.h>

static const char PROGMEM s1[] = "%s";
static const char PROGMEM s2[] = "%s%s";
static const char PROGMEM s2u[] = "%s%u";

typedef struct lstr {
  uint16_t size;
  char s[];
} lstr;

class LString {
public:
  LString(size_t size) {
    //_ls = (lstr*)malloc(size+2);
    _ls = (lstr*) new char[size+2];
    *((uint32_t*)_ls) = size;
  }

  LString(size_t size, const char *fmt, ...) {
    va_list arg;
    va_start(arg, fmt);
    _ls = (lstr*) new char[size+2];
    *((uint32_t*)_ls) = size;
    vsnprintf_P(_ls->s, size, fmt, arg);
  }

  size_t getSize(void) { return _ls->size; }
  char *getChar(void) { return _ls->s; }

  inline ~LString(void) {
    delete[] _ls;
  }

  LString & operator =(const char *cstr) {
    strncpy_P(_ls->s, cstr, strlen(_ls->s) - _ls->size - 1);
    _ls->s[_ls->size-1] = '\0';
  }

  inline size_t len(void) const {
    return strlen(_ls->s);
  }

  int32_t lastIndexOf(const char * s2, size_t fromIndex) const ;

  void setLen(size_t len) {
    if (len < _ls->size) {
      _ls->s[len] = '\0';
    }
  }

  inline LString & operator +=(const char *cstr) {
    return concat(cstr);
  }
  // CString & operator +=(const char *cstr) {
  //   strncat_P(_s, cstr, strlen(_s) - CSIZE - 1);
  // }
  LString & operator +=(const __FlashStringHelper *fstr) {
    strncat_P(_ls->s, (PGM_P)fstr, strlen(_ls->s) - _ls->size - 1);
  }
  LString & operator +=(const String &str) {
    strncat(_ls->s, str.c_str(), strlen(_ls->s) - _ls->size - 1);
  }
  LString & operator +=(const LString lstr) {
    snprintf_P(_ls->s, _ls->size, s2, _ls->s, lstr._ls->s);
    //strncat(_ls->s, lstr._ls->s, strlen(_ls->s) - _ls->size - 1);
  }
  LString & operator +=(const uint32_t num) {
    return concat(num);
  }

  LString & concat(const char *cstr) {
    snprintf_P(_ls->s, _ls->size, s2, _ls->s, cstr);
    return (*this);
  }

  LString & concat(const uint32_t num) {
    snprintf_P(_ls->s, _ls->size, s2u, _ls->s, num);
    return (*this);
  }

  LString & format(const char *fmt, ...) {
    va_list arg;
    va_start(arg, fmt);
    vsnprintf_P(_ls->s, _ls->size, fmt, arg);
    return (*this);
  }

  LString & toLowerCase(void);
  /*explicit*/ operator char*() const { return _ls->s; }

  LString & replace(const char * find, const char * replace);

  const char * c_str(void) { return _ls->s; }

private:
  lstr * _ls;

};


#endif  // _SONOFF_LTRING_P_H_
