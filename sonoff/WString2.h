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

#define FPSTR2(pstr_pointer) (reinterpret_cast<const __FlashStringHelper *>(pstr_pointer))
#define PROGMEM2 __attribute__((section( "\".irom.text." __FILE__ "\"")))

#define PSTR2(str) \
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

#define F2(string_literal) (FPSTR2(PSTR2(string_literal)))

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
