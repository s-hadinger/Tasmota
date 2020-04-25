/*
  support_json.ino - wifi support for Tasmota

  Copyright (C) 2020  Theo Arends & Stephan Hadinger

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

/*********************************************************************************************\
 * Find attribute in JSON object as case-insensitive
\*********************************************************************************************/

// Get a JSON attribute, with case insensitive key search
// Warning, returns a null object if not found. Don't dereference it if it's null
//
// Param:
// - json: JsonObject to find the attribute, the object is const and unchanged
// - needle: attribute to find, case insensitive, can be in PROGMEM
// Returns:
// - JsonVariant object passed by reference as const. You need to excplicitly copy any value (char* for ex)
const JsonVariant &getJsonCaseInsensitive(const JsonObject &json, const char *needle) {
  // key can be in PROGMEM
  if ((nullptr == &json) || (nullptr == needle) || (0 == pgm_read_byte(needle))) {
    return *(JsonVariant*)nullptr;
  }

  for (JsonObject::const_iterator it=json.begin(); it!=json.end(); ++it) {
    const char *key = it->key;
    const JsonVariant &value = it->value;

    if (0 == strcasecmp_P(key, needle)) {
      return value;
    }
  }
  // if not found
  return *(JsonVariant*)nullptr;
}

// Similar as above.
// Get the string value of a JSON attribute, with case insensitive key search
//
// Param:
// - json: JsonObject to find the attribute, the object is const and unchanged
// - needle: attribute to find, case insensitive, can be in PROGMEM
// Returns:
// - pointer to 'const char*' of the string. Do an explicit copy of the string if you need a long term copy.
//   nullptr if not found.
const char * getJsonCaseInsensitiveConstCharNull(const JsonObject &json, const char *needle) {
  const JsonVariant &val = getJsonCaseInsensitive(json, needle);
  if (&val) {
    const char *val_cs = val.as<const char*>();
    if (strlen(val_cs)) {
      return val_cs;
    }
  }
  return nullptr;
}

/*********************************************************************************************\
 * Find attribute in JSON object starting with a string, as case-insensitive
\*********************************************************************************************/

// Get a JSON attribute, with case insensitive key search
// Warning, returns a null object if not found. Don't dereference it if it's null.
// Returns the first match in order of JSON in case of possible multiple matches
//
// Param:
// - json: JsonObject to find the attribute, the object is const and unchanged
// - needle: attribute 'starts with' to find, case insensitive, can be in PROGMEM
// Returns:
// - JsonVariant object passed by reference as const. You need to excplicitly copy any value (char* for ex)
JsonVariant &startsWithJsonCaseInsensitive(const JsonObject &json, const char *needle) {
  // key can be in PROGMEM
  if ((nullptr == &json) || (nullptr == needle) || (0 == pgm_read_byte(needle))) {
    return *(JsonVariant*)nullptr;
  }

  String needle_s(needle);
  needle_s.toLowerCase();

  for (auto kv : json) {
    String key_s(kv.key);
    key_s.toLowerCase();
    JsonVariant &value = kv.value;

    if (key_s.startsWith(needle_s)) {
      return value;
    }
  }
  // if not found
  return *(JsonVariant*)nullptr;
}

/*********************************************************************************************\
 * Parse attributes
\*********************************************************************************************/

// Convert JsonVariant to uint32_t
// Supports either number of hex in the form '0x00000000'
uint32_t jsonToUInt(const JsonVariant &val) {
  // if the string starts with 0x, it is considered Hex, otherwise it is an int
  if (val.is<unsigned int>()) {
    return val.as<unsigned int>();
  } else {
    if (val.is<const char*>()) {
      String sval = val.as<String>();
      return strtoull(sval.c_str(), nullptr, 0);
    }
  }
  return 0;   // couldn't parse anything
}
