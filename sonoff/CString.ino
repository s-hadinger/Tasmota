
#include "CString.h"
#include "WString.h"

int TestCString(void) {
  CString<50> s;
  CString<2> t;
  String s2 = "azerty";
  int l;

  s = "azert";
  s += "yuiop";
  s += F("qsd");
  s += s2;
  s += 42;
  t += "azert";
  t += "azert";
  return s.len();
}
