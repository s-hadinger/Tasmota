/********************************************************************
 * Tasmota LVGL ctypes mapping
 *******************************************************************/
#include "be_constobj.h"

#ifdef USE_ENERGY_SENSOR

/********************************************************************
 * Generated code, don't edit
 *******************************************************************/

enum {
    ctypes_i32    = 14,
    ctypes_i16    = 12,
    ctypes_i8     = 11,
    ctypes_u32    =  4,
    ctypes_u16    =  2,
    ctypes_u8     =  1,

    // big endian
    ctypes_be_i32 = -14,
    ctypes_be_i16 = -12,
    ctypes_be_i8  = -11,
    ctypes_be_u32 =  -4,
    ctypes_be_u16 =  -2,
    ctypes_be_u8  =  -1,

    ctypes_bf     = 0,    //bif-field
};

typedef struct be_ctypes_structure_item_t {
    const char * name;
    uint16_t  offset_bytes;
    uint8_t   offset_bits : 3;
    uint8_t   len_bits : 5;
    int8_t    type : 5;
    uint8_t   mapping : 3;
} be_ctypes_structure_item_t;

typedef struct be_ctypes_structure_t {
    uint16_t  size_bytes;       /* size in bytes */
    uint16_t  size_elt;         /* number of elements */
    const char **instance_mapping;  /* array of instance class names for automatic instanciation of class */
    const be_ctypes_structure_item_t * items;
} be_ctypes_structure_t;

typedef struct be_ctypes_class_t {
    const char * name;
    const be_ctypes_structure_t * definitions;
} be_ctypes_class_t;

typedef struct be_ctypes_classes_t {
    uint16_t  size;
    const char **instance_mapping;  /* array of instance class names for automatic instanciation of class */
    const be_ctypes_class_t * classes;
} be_ctypes_classes_t;

BE_EXPORT_VARIABLE extern const bclass be_class_ctypes;

void ctypes_register_class(bvm *vm, const bclass * ctypes_class, const be_ctypes_structure_t * definitions) {
    be_pushntvclass(vm, ctypes_class);
    be_setglobal(vm, str(ctypes_class->name));
    be_pop(vm, 1);
}

const char * be_ctypes_instance_mappings[];    /* forward definition */

// Define a sub-class of ctypes with only one member which points to the ctypes defintion
#define be_define_ctypes_class(_c_name, _def, _super, _name)                \
  be_local_class(_c_name,                                                   \
      0,                                                                    \
      _super,                                                               \
      be_nested_map(1,                                                      \
      ( (struct bmapnode*) &(const bmapnode[]) {                            \
          { be_nested_key("_def", 1985022181, 4, -1), be_const_comptr(_def) },\
      })),                                                                  \
      (be_nested_const_str(_name, 0, sizeof(_name)-1))                      \
  )

/********************************************************************/

const be_ctypes_structure_t be_energy_struct = {
  146,  /* size in bytes */
  62,  /* number of elements */
  be_ctypes_instance_mappings,
  (const be_ctypes_structure_item_t[62]) {
    { "active_power", 24, 0, 0, 14, 0 },
    { "active_power2", 28, 0, 0, 14, 0 },
    { "active_power3", 32, 0, 0, 14, 0 },
    { "command_code", 113, 0, 0, 1, 0 },
    { "current", 12, 0, 0, 14, 0 },
    { "current2", 16, 0, 0, 14, 0 },
    { "current3", 20, 0, 0, 14, 0 },
    { "current_available", 118, 5, 1, 0, 0 },
    { "daily", 88, 0, 0, 14, 0 },
    { "data_valid", 114, 0, 0, 1, 0 },
    { "data_valid2", 115, 0, 0, 1, 0 },
    { "data_valid3", 116, 0, 0, 1, 0 },
    { "export_active", 72, 0, 0, 14, 0 },
    { "export_active2", 76, 0, 0, 14, 0 },
    { "export_active3", 80, 0, 0, 14, 0 },
    { "fifth_second", 112, 0, 0, 1, 0 },
    { "frequency", 60, 0, 0, 14, 0 },
    { "frequency2", 64, 0, 0, 14, 0 },
    { "frequency3", 68, 0, 0, 14, 0 },
    { "frequency_common", 118, 1, 1, 0, 0 },
    { "kWhtoday", 104, 0, 0, 4, 0 },
    { "kWhtoday_delta", 96, 0, 0, 4, 0 },
    { "kWhtoday_offset", 100, 0, 0, 4, 0 },
    { "kWhtoday_offset_init", 118, 3, 1, 0, 0 },
    { "max_current_flag", 138, 5, 1, 0, 0 },
    { "max_energy_state", 145, 0, 0, 1, 0 },
    { "max_power_flag", 138, 1, 1, 0, 0 },
    { "max_voltage_flag", 138, 3, 1, 0, 0 },
    { "min_current_flag", 138, 4, 1, 0, 0 },
    { "min_power_flag", 138, 0, 1, 0, 0 },
    { "min_voltage_flag", 138, 2, 1, 0, 0 },
    { "mplh_counter", 140, 0, 0, 2, 0 },
    { "mplr_counter", 144, 0, 0, 1, 0 },
    { "mplw_counter", 142, 0, 0, 2, 0 },
    { "period", 108, 0, 0, 4, 0 },
    { "phase_count", 117, 0, 0, 1, 0 },
    { "power_factor", 48, 0, 0, 14, 0 },
    { "power_factor2", 52, 0, 0, 14, 0 },
    { "power_factor3", 56, 0, 0, 14, 0 },
    { "power_history_0", 119, 0, 0, 2, 0 },
    { "power_history_02", 121, 0, 0, 2, 0 },
    { "power_history_03", 123, 0, 0, 2, 0 },
    { "power_history_1", 125, 0, 0, 2, 0 },
    { "power_history_12", 127, 0, 0, 2, 0 },
    { "power_history_13", 129, 0, 0, 2, 0 },
    { "power_history_2", 131, 0, 0, 2, 0 },
    { "power_history_22", 133, 0, 0, 2, 0 },
    { "power_history_23", 135, 0, 0, 2, 0 },
    { "power_on", 118, 7, 1, 0, 0 },
    { "power_steady_counter", 137, 0, 0, 1, 0 },
    { "reactive_power", 36, 0, 0, 14, 0 },
    { "reactive_power2", 40, 0, 0, 14, 0 },
    { "reactive_power3", 44, 0, 0, 14, 0 },
    { "start_energy", 84, 0, 0, 14, 0 },
    { "total", 92, 0, 0, 14, 0 },
    { "type_dc", 118, 6, 1, 0, 0 },
    { "use_overtemp", 118, 2, 1, 0, 0 },
    { "voltage", 0, 0, 0, 14, 0 },
    { "voltage2", 4, 0, 0, 14, 0 },
    { "voltage3", 8, 0, 0, 14, 0 },
    { "voltage_available", 118, 4, 1, 0, 0 },
    { "voltage_common", 118, 0, 1, 0, 0 },
}};

const char * be_ctypes_instance_mappings[] = {
  NULL
};

static be_define_ctypes_class(energy_struct, &be_energy_struct, &be_class_ctypes, "energy_struct");

void be_load_ctypes_definitions_lib(bvm *vm) {
  ctypes_register_class(vm, &be_class_energy_struct, &be_energy_struct);
}
/********************************************************************/

#endif // USE_ENERGY_SENSOR