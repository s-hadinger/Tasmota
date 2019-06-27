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

#include "WString.h"
#include "WString2.h"
// This is a super class of String used to reduce code size when using replace()
// and indexOf() with strings and PMEM strings
// The regular String class converts inline all arguments to String objects
// adding a lot of redundant code

int String2::indexOf(const __FlashStringHelper * str) const {
  return String::indexOf(String(str));
}
int String2::indexOf(const char * str) const {
  return String::indexOf(String(str));
}

unsigned char String2::startsWith(const char * prefix) const {
  return String::startsWith(prefix);
}
unsigned char String2::startsWith(const __FlashStringHelper * prefix) const {
  return String::startsWith(prefix);
}
unsigned char String2::endsWith(const char * suffix) const {
  return String::endsWith(suffix);
}
unsigned char String2::endsWith(const __FlashStringHelper * suffix) const {
  return String::endsWith(suffix);
}

void String2::replace(const __FlashStringHelper * find, const __FlashStringHelper * replace) {
  String::replace(String(find), String(replace));
}
void String2::replace(const char * find, const char * replace) {
  String::replace(String(find), String(replace));
}
void String2::replace(char * find, char * replace) {
  String::replace(String(find), String(replace));
}
void String2::replace(const __FlashStringHelper * find, const String &replace) {
  String::replace(String(find), replace);
}
void String2::replace(const __FlashStringHelper * find, const char * replace) {
  String::replace(String(find), String(replace));
}
void String2::replace(const char * find, const __FlashStringHelper * replace) {
  String::replace(String(find), String(replace));
}
void String2::replace(const char * find, const String &replace) {
  String::replace(String(find), replace);
}
void String2::replace(const char * find, const String2 &replace) {
  String::replace(String(find), replace);
}
