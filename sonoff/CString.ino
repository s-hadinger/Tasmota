
#include "CString.h"
#include "WString.h"

int Test2(CString<50> &s) {
  s += "aaa";
}

int TestCString(void) {
  CString<50> s;
  CString<48> s2;
  CString<2> t;
  String ss = "azerty";
  int l;

  s = "azert";
  s += "yuiop";
  s += F("qsd");
  s += ss;
  s += 42;
  s2 = "azert";
  s2 += "yuiop";
  s2 += F("qsd");
  s2 += ss;
  s2 += 42;
  t += "azert";
  t += "azert";
  return s.len();
}
