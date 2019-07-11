
class LString getLStringTest(void) {
  LString s(10);
  s = "aaa";
  s += s.len();
  return s;
}

int TestLString(void) {
  LString s(10);
  s = "aazz";
  LString s2 = getLStringTest();

  s += "azerty";
  s += 2;
  s += "azerty";
  s += 4;
  s += s2;

  return s.len();
}
