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

#ifndef _SONOFF_CSTRING_H_
#define _SONOFF_CSTRING_H_

#include <pgmspace.h>
#include <WString.h>

static const char PROGMEM s1[] = "%s";
static const char PROGMEM s2[] = "%s%s";
static const char PROGMEM s2u[] = "%s%u";

template <size_t CSIZE> class CString {
  public:
    CString() {}
    CString(char *cstr, size_t len) {
      s = cstr;
    }

    ~CString(void) {}

    CString & operator =(const char *cstr) {
      strncpy_P(s, cstr, strlen(s) - CSIZE - 1);
      s[CSIZE-1] = '\0';;
    }

    inline CString & operator +=(const char *cstr) {
      return concat(cstr);
    }
    // CString & operator +=(const char *cstr) {
    //   strncat_P(s, cstr, strlen(s) - CSIZE - 1);
    // }
    CString & operator +=(const __FlashStringHelper *fstr) {
      strncat_P(s, (PGM_P)fstr, strlen(s) - CSIZE - 1);
    }
    CString & operator +=(const String &str) {
      strncat(s, str.c_str(), strlen(s) - CSIZE - 1);
    }
    inline CString & operator +=(const uint32_t num) {
      return concat(num);
    }

    CString & concat(const char *cstr) {
      format_P(s2, s, cstr);
      return (*this);
    }
    CString & concat(const uint32_t num) {
      format_P(s2u, s, num);
      return (*this);
    }

    void format_P(const char* formatP, ...) {
      va_list arg;
      va_start(arg, formatP);
      vsnprintf_P(mqtt_data, sizeof(mqtt_data), formatP, arg);
      va_end(arg);
    }

    size_t len(void) {
      return strlen(s);
    }

    // String2(const char *cstr = "") : String(cstr) {}
    // String2(const String &str) : String(str) {}
    // String2(const __FlashStringHelper *str) : String(str) {}
    //
    // int indexOf(const __FlashStringHelper * str) const;
    // int indexOf(const char * str) const;
    //
    // unsigned char startsWith(const char * prefix) const;
    // unsigned char startsWith(const __FlashStringHelper * prefix) const;
    // unsigned char endsWith(const char * suffix) const;
    // unsigned char endsWith(const __FlashStringHelper * suffix) const;
    //
    // void replace(const __FlashStringHelper * find, const __FlashStringHelper * replace);
    // void replace(const __FlashStringHelper * find, __FlashStringHelper * replace);
    // void replace(const char * find, const char * replace);
    // void replace(char * find, char * replace);
    // void replace(const __FlashStringHelper * find, const String &replace);
    // void replace(const __FlashStringHelper * find, const char * replace);
    // void replace(const char * find, const __FlashStringHelper * replace);
    // void replace(const char * find, const String &replace);
    // void replace(const char * find, const String2 &replace);
    //
    // String2 & operator = (const __FlashStringHelper *pstr) {
    //   String::operator = (pstr);
    // }
  private:
    char s[CSIZE];    // allocate memory locally (ex: on the stack)
};

#endif  // _SONOFF_STRING_P_H_
