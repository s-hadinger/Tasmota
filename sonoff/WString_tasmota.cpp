/*
 */

#include "WString_tasmota.h"

#ifdef String_class_tasmota_h   // if we have a Tasmota specific header


int String::indexOf(const __FlashStringHelper * str) const {
  return String::indexOf(String(str));
}
int String::indexOf(const char * str) const {
  return String::indexOf(String(str));
}

unsigned char String::startsWith(const char * prefix) const {
  return String::startsWith(prefix);
}
unsigned char String::startsWith(const __FlashStringHelper * prefix) const {
  return String::startsWith(prefix);
}
unsigned char String::endsWith(const char * suffix) const {
  return String::endsWith(suffix);
}
unsigned char String::endsWith(const __FlashStringHelper * suffix) const {
  return String::endsWith(suffix);
}

void String::replace(const __FlashStringHelper * find, const __FlashStringHelper * replace) {
  String::replace(String(find), String(replace));
}
void String::replace(const char * find, const char * replace) {
  String::replace(String(find), String(replace));
}
void String::replace(const __FlashStringHelper * find, const String &replace) {
  String::replace(String(find), replace);
}
void String::replace(const __FlashStringHelper * find, const char * replace) {
  String::replace(String(find), String(replace));
}
void String::replace(const char * find, const String &replace) {
  String::replace(String(find), replace);
}


#endif  // String_class_tasmota_h
