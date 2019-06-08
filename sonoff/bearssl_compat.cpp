/*
  bearssl_compat.cpp - Fix some C/C++ linkage issues with core_2_3_0

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

#include <core_version.h>

#ifdef ARDUINO_ESP8266_RELEASE_2_3_0
#include <stddef.h>
#include <stdarg.h>

extern int ets_printf_compat(const char* fmt, ...);

int ets_printf(const char* fmt, ...) {
  va_list args;
  va_start(args, fmt);
  return ets_printf_compat(fmt, args);
}

extern void *memcpy_P_compat(void *s1, const void *s2, size_t n);
extern int memcmp_P_compat(const void *s1, const void *s2, size_t n);

extern "C" {
  void *memcpy_P(void *s1, const void *s2, size_t n) {
    return memcpy_P_compat(s1, s2, n);
  }
  int memcmp_P(const void *s1, const void *s2, size_t n) {
    return memcmp_P_compat(s1, s2, n);
  }
}
#endif // ARDUINO_ESP8266_RELEASE_2_3_0
