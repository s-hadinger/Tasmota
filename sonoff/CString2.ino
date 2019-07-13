

//
//
// template <size_t CSIZE> class CString2 : public CString0 {
// public:
//   size_t getSize(void) { return CSIZE; }
//   char *getChar(void) { return _s; }
//
//   CString2 & operator =(const char *cstr) {
//     strncpy_P(_s, cstr, strlen(_s) - CSIZE - 1);
//     _s[CSIZE-1] = '\0';;
//   }
//
// public:
//   CString2() { _size = CSIZE; }
//
// private:
//   char _s[CSIZE];
// };
//
// int TestCString2(void) {
//   CString2<32> s;
//   return s.getSize();
// }
//
// int TestCString22(class CString0 &s1) {
//   CString0 s;
//   return s1.getSize();
// }
//
// CString0 getTestId(void) {
//   CString2<2>  s;
//   s = "azer";
//
//   return s;
// }
//
// template <size_t CSIZE> void getTestId5(CString2<CSIZE> &s) {
//   s = "azert";
// }
//
// char* TestCString50(void) {
//   CString0     s50;
//   CString2<2> s55;
//
//   char *c1 = s50.getChar();
//   char *c2 = s55.getChar();
//
//   int l = strlen(c1) + strlen(c2);
//
//   CString0 s00 = getTestId();
//   getTestId5(s55);
//
//   return s00.getChar();
// }
