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

// This is a super class of String used to reduce code size when using replace()
// and indexOf() with strings and PMEM strings
// The regular String class converts inline all arguments to String objects
// adding a lot of redundant code
class String2 : public String {
  public:
    String2(const char *cstr = "") : String(cstr) {}
    String2(const String &str) : String(str) {}
    String2(const __FlashStringHelper *str) : String(str) {}

    int indexOf(const __FlashStringHelper * str) const {
      return String::indexOf(String(str));
    }
    int indexOf(const char * str) const {
      return String::indexOf(String(str));
    }

    unsigned char startsWith(const char * prefix) const {
      return String::startsWith(prefix);
    }
    unsigned char startsWith(const __FlashStringHelper * prefix) const {
      return String::startsWith(prefix);
    }
    unsigned char endsWith(const char * suffix) const {
      return String::endsWith(suffix);
    }
    unsigned char endsWith(const __FlashStringHelper * suffix) const {
      return String::endsWith(suffix);
    }

    void replace(const __FlashStringHelper * find, const __FlashStringHelper * replace) {
      String::replace(String(find), String(replace));
    }
    void replace(const char * find, const char * replace) {
      String::replace(String(find), String(replace));
    }
    void replace(const __FlashStringHelper * find, const String &replace) {
      String::replace(String(find), replace);
    }
    void replace(const __FlashStringHelper * find, const char * replace) {
      String::replace(String(find), String(replace));
    }
    void replace(const char * find, const String &replace) {
      String::replace(String(find), replace);
    }

    String2 & operator = (const __FlashStringHelper *pstr) {
      String::operator = (pstr);
    }
};

#endif  // _SONOFF_STRING_P_H_
