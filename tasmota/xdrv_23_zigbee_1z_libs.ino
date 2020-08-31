/*
  xdrv_23_zigbee_1z_libs.ino - zigbee support for Tasmota, JSON replacement libs

  Copyright (C) 2020  Theo Arends and Stephan Hadinger

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

#ifdef USE_ZIGBEE

/*********************************************************************************************\
 * Replacement libs for JSON to output a list of attributes
\*********************************************************************************************/

// simplified version of strcmp accepting both arguments to be in PMEM, and accepting nullptr arguments
// inspired from https://code.woboq.org/userspace/glibc/string/strcmp.c.html
int strcmp_PP(const char *p1, const char *p2) {
  if (p1 == p2) { return 0; }         // equality
  if (!p1)      { return -1; }        // first string is null
  if (!p2)      { return 1; }         // second string is null
  const unsigned char *s1 = (const unsigned char *) p1;
  const unsigned char *s2 = (const unsigned char *) p2;
  unsigned char c1, c2;
  do {
    c1 = (unsigned char) *s1++;
    c2 = (unsigned char) *s2++;
    if (c1 == '\0')
      return c1 - c2;
  }
  while (c1 == c2);
  return c1 - c2;
}

typedef struct Z_LastMessageVars {
  uint16_t    device;               // device short address
  uint16_t    groupaddr;            // group address
  uint16_t    cluster;              // cluster id
  uint8_t     endpoint;             // source endpoint
} Z_LastMessageVars;

Z_LastMessageVars gZbLastMessage;

uint16_t Z_GetLastDevice(void) { return gZbLastMessage.device; }
uint16_t Z_GetLastGroup(void) { return gZbLastMessage.groupaddr; }
uint16_t Z_GetLastCluster(void) { return gZbLastMessage.cluster; }
uint8_t  Z_GetLastEndpoint(void) { return gZbLastMessage.endpoint; }

/*********************************************************************************************\
 * Structures for device configuration
\*********************************************************************************************/

const size_t endpoints_max = 8;         // we limit to 8 endpoints


enum class Za_type : uint8_t {
  Za_none,     // empty, translates into null in JSON
  // numericals
  Za_bool,     // boolean, translates to true/false, uses uval32 to store
  Za_uint,     // unsigned 32 int, uses uval32
  Za_int,      // signed 32 int, uses ival32
  Za_float,    // float 32, uses fval
  // non-nummericals
  Za_raw,      // bytes buffer, uses bval
  Za_str       // string, uses sval
};

class Z_attribute {
public:

  // attribute key, either cluster+attribute_id or plain name
  union {
    struct {
      uint16_t cluster;
      uint16_t attr_id;
    } id;
    char * key;
  } key;
  // attribute value
  union {
    uint32_t uval32;
    int32_t  ival32;
    float    fval;
    SBuffer* bval;
    char*    sval;
  } val;
  Za_type       type;       // uint8_t in size, type of attribute, see above
  bool          key_is_str;   // is the key a string?
  bool          key_is_pmem;  // is the string in progmem, so we don't need to make a copy
  uint8_t       key_suffix; // append a suffix to key (if different from 0xFF)
  Z_attribute*  next;   // next item in the linked list

  // Constructor with all defaults
  Z_attribute():
    key{ .id = { 0x0000, 0x0000 } },
    val{ .uval32 = 0x0000 },
    type(Za_type::Za_none),
    key_is_str(false),
    key_is_pmem(false),
    key_suffix(0xFF),
    next(nullptr)
    {};
  
  // Destructor, free memory that was allocated
  ~Z_attribute() {
    freeKey();
    freeVal();
  }

  // free any allocated memoruy for values
  void freeVal(void) {
    switch (type) {
      case Za_type::Za_raw:
        if (val.bval) { delete val.bval; val.bval = nullptr; }
        break;
      case Za_type::Za_str:
        if (val.sval) { delete[] val.sval; val.sval = nullptr; }
        break;
    }
  }
  // free any allocated memoruy for keys
  void freeKey(void) {
    if (key_is_str && key.key && !key_is_pmem) { delete[] key.key; }
    key.key = nullptr;
  }

  // Setters
  void setNone(void) {
    freeVal();     // free any previously allocated memory
    val.uval32 = 0;
    type = Za_type::Za_none;
  }
  void setUInt(uint32_t _val) {
    freeVal();     // free any previously allocated memory
    val.uval32 = _val;
    type = Za_type::Za_uint;
  }
  void setBool(bool _val) {
    freeVal();     // free any previously allocated memory
    val.uval32 = _val;
    type = Za_type::Za_bool;
  }
  void setInt(int32_t _val) {
    freeVal();     // free any previously allocated memory
    val.ival32 = _val;
    type = Za_type::Za_int;
  }
  void setFloat(float _val) {
    freeVal();     // free any previously allocated memory
    val.fval = _val;
    type = Za_type::Za_float;
  }

  // set the string value
  // PMEM argument is allowed
  // string will be copied, so it can be changed later
  // nullptr is allowed and considered as empty string
  // Note: memory is allocated only if string is non-empty
  void setStr(const char * _val) {
    freeVal();     // free any previously allocated memory
    // val.sval is always nullptr after freeVal()
    if (_val) {
      size_t len = strlen_P(_val);
      if (len) {
        val.sval = new char[len+1];
        strcpy_P(val.sval, _val);
      }
    }
    type = Za_type::Za_str;
  }

  inline bool isNum(void) const { return (type >= Za_type::Za_bool) && (type <= Za_type::Za_float); }
  // get num values
  float getFloat(void) const {
    switch (type) {
      case Za_type::Za_bool:
      case Za_type::Za_uint:    return (float) val.uval32;
      case Za_type::Za_int:     return (float) val.ival32;
      case Za_type::Za_float:   return val.fval;
      default:                  return 0.0f;
    }
  }

  int32_t getInt(void) const {
    switch (type) {
      case Za_type::Za_bool:
      case Za_type::Za_uint:    return (int32_t) val.uval32;
      case Za_type::Za_int:     return val.ival32;
      case Za_type::Za_float:   return (int32_t) val.fval;
      default:                  return 0;
    }
  }

  uint32_t getUInt(void) const {
    switch (type) {
      case Za_type::Za_bool:
      case Za_type::Za_uint:    return val.uval32;
      case Za_type::Za_int:     return (uint32_t) val.ival32;
      case Za_type::Za_float:   return (uint32_t) val.fval;
      default:                  return 0;
    }
  }

  bool getBool(void) const {
    switch (type) {
      case Za_type::Za_bool:
      case Za_type::Za_uint:    return val.uval32 ? true : false;
      case Za_type::Za_int:     return val.ival32 ? true : false;
      case Za_type::Za_float:   return val.fval ? true : false;
      default:                  return false;
    }
  }

  const SBuffer * getRaw(void) const {
    if (Za_type::Za_raw == type) { return val.bval; }
    return nullptr;
  }

  // always return a point to a string, if not defined then empty string.
  // Never returns nullptr
  const char * getStr(void) const {
    if (Za_type::Za_str == type) { return val.sval; }
    return "";
  }

  String toString(bool prefix_comma = false) const {
    String res("");
    if (prefix_comma) { res += ','; }
    res += '"';
    // compute the attribute name
    if (key_is_str) {
      if (key.key) { res += key.key; }
      else         { res += F("null"); }   // shouldn't happen
    } else {
      char attr_name[12];
      snprintf_P(attr_name, sizeof(attr_name), PSTR("%04X/%04X"), key.id.cluster, key.id.attr_id);
      res += attr_name;
    }
    if (0xFF != key_suffix) {
      res += key_suffix;
    }
    res += F("\":");
    // value part
    switch (type) {
    case Za_type::Za_none:
      res += "null";
      break;
    case Za_type::Za_bool:
      res += val.uval32 ? F("true") : F("false");
      break;
    case Za_type::Za_uint:
      res += val.uval32;
      break;
    case Za_type::Za_int:
      res += val.ival32;
      break;
    case Za_type::Za_float:
      res += val.fval;
      break;
    case Za_type::Za_raw:
      res += F("\"0x");
      if (val.bval) {
        size_t blen = val.bval->len();
        // print as HEX
        char hex[2*blen+1];
        ToHex_P(val.bval->getBuffer(), blen, hex, sizeof(hex));
        res += hex;
      }
      res += '"';
      break;
    case Za_type::Za_str:
      res += '"';
      if (val.sval) {
        res += EscapeJSONString(val.sval);    // escape JSON chars
      }
      res += '"';
      break;
    }

    return res;
  }

};

// Attribute list
// Contains meta-information:
// - source endpoint (is conflicting)
// - LQI (if not conflicting)
class Z_attribute_list {
public:
  Z_attribute * head;     // head of linked list
  uint8_t       src_ep;   // source endpoint, 0xFF if unknown
  uint8_t       lqi;      // linkquality, 0xFF if unknown

  Z_attribute_list():
    head(nullptr),
    src_ep(0xFF),
    lqi(0xFF)
    {};
  
  // reset object to its initial state
  // free all allocated memory
  void reset(void) {
    while (head) {
      Z_attribute * next = head->next;
      delete head;
      head = next;
    }
    // head is now nullptr
    src_ep = 0xFF;
    lqi = 0xFF;
  }

  // traverse the linked list chain and add the attribute to the end of the list
  void addToLast(Z_attribute * attr) {
    Z_attribute **curr_ptr = &head;
    while (*curr_ptr) {
      curr_ptr = &((*curr_ptr)->next);
    }
    *curr_ptr = attr;
  }

  // Add attribute to the list, given cluster and attribute id
  Z_attribute * addAttribute(uint16_t cluster, uint16_t attr_id) {
    Z_attribute * attr = new Z_attribute();

    attr->key.id.cluster = cluster;
    attr->key.id.attr_id = attr_id;
    attr->key_is_str = false;
    // add to end
    addToLast(attr);
  }

  // Add attribute to the list, given name
  Z_attribute * addAttribute(const char * name, bool pmem = false) {
    Z_attribute * attr = new Z_attribute();

    attr->key_is_str = true;
    attr->key_is_pmem = pmem;
    if (pmem) {
      attr->key.key = (char*) name;   // override type, we will not try to change it anyways
    } else {
      if (name) {
        size_t name_len = strlen_P(name);
        attr->key.key = new char[name_len+1];
        strcpy_P(attr->key.key, name);
      }
    }
    // add to end
    addToLast(attr);
  }

  // dump the entire structure as JSON, starting from head (as parameter)
  // does not start not end with a comma
  String toString(void) const {
    Z_attribute * curr = head;
    String res = "";
    bool prefix_comma = false;
    while (curr)  {
      res += curr->toString(prefix_comma);
      prefix_comma = true;
      curr = curr->next;
    }
    // add source endpoint
    if (0xFF != src_ep) {
      if (prefix_comma) { res += ','; }
      prefix_comma = true;
      res += F(",\"" D_CMND_ZIGBEE_ENDPOINT "\":");
      res += src_ep;
    }
    // add lqi
    if (0xFF != lqi) {
      if (prefix_comma) { res += ','; }
      prefix_comma = true;
      res += F(",\"" D_CMND_ZIGBEE_LINKQUALITY "\":");
      res += src_ep;
    }
    // done
    return res;
  }
};

#endif // USE_ZIGBEE
