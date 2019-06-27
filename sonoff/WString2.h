/*
  WString2 - Post header file for Sonoff-Tasmota

  Copyright (C) 2019  Theo Arends

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef _SONOFF_STRING2_H_
#define _SONOFF_STRING2_H_

#define PSTR2(str) PSTR_INTERNAL_1(str, __COUNTER__)
#define PSTR_INTERNAL_1(str, num) PSTR_INTERNAL_2(str, num)

#define PSTR_INTERNAL_2(str, num) \
  (__extension__({ \
    PGM_P ptr;  \
    asm volatile \
    ( \
      ".pushsection .irom.text, \"aSM\", @progbits, 1" "\n\t" \
      ".align	4"                                       "\n\t" \
      "PSTR_" #num ": .string " #str                            "\n\t" \
      ".popsection"                                      "\n\t" \
    ); \
    asm volatile \
    ( \
      ".literal .PSTR%=, PSTR_" #num                                "\n\t" \
      "l32r %0, .PSTR%="                             "\n\t" \
      : "=r" (ptr) \
    ); \
    ptr; \
  }))

#define PSTR2_working(str) \
  (__extension__({ \
    PGM_P ptr;  \
    asm volatile \
    ( \
      ".pushsection .irom.text, \"aSM\", @progbits, 1" "\n\t" \
      ".align	4"                                       "\n\t" \
      ".PSTR%=: .string " #str                            "\n\t" \
      ".popsection"                                      "\n\t" \
      ".literal .PSTR2%=, .PSTR%="                               "\n\t" \
      "l32r %0, .PSTR2%="                             "\n\t" \
      : "=r" (ptr) \
    ); \
    ptr; \
  }))

#define F2(string_literal) (FPSTR(PSTR2(string_literal)))

// This is a super class of String used to reduce code size when using replace()
// and indexOf() with strings and PMEM strings
// The regular String class converts inline all arguments to String objects
// adding a lot of redundant code
class String2 : public String {
  public:
    String2(const char *cstr = "") : String(cstr) {}
    String2(const String &str) : String(str) {}
    String2(const __FlashStringHelper *str) : String(str) {}

    int indexOf(const __FlashStringHelper * str) const;
    int indexOf(const char * str) const;

    unsigned char startsWith(const char * prefix) const;
    unsigned char startsWith(const __FlashStringHelper * prefix) const;
    unsigned char endsWith(const char * suffix) const;
    unsigned char endsWith(const __FlashStringHelper * suffix) const;

    void replace(const __FlashStringHelper * find, const __FlashStringHelper * replace);
    void replace(const __FlashStringHelper * find, __FlashStringHelper * replace);
    void replace(const char * find, const char * replace);
    void replace(char * find, char * replace);
    void replace(const __FlashStringHelper * find, const String &replace);
    void replace(const __FlashStringHelper * find, const char * replace);
    void replace(const char * find, const __FlashStringHelper * replace);
    void replace(const char * find, const String &replace);
    void replace(const char * find, const String2 &replace);

    String2 & operator = (const __FlashStringHelper *pstr) {
      String::operator = (pstr);
    }
};

#endif  // _SONOFF_STRING_P_H_
