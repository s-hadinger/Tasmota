#
# ctype buidings for Tasmota Energy driver
#
# To generate C bindings, do:
# > compile("energy_ctypes.be","file")()
#
# and copy/paste output in C format
#
import ctypes

ctypes.print_types()

float = ctypes.i32
uint8 = ctypes.u8
uint16 = ctypes.u16
uint32 = ctypes.u32
int32 = ctypes.i32
bool = ctypes.bf_1

energy_struct = [
    [float, "voltage"],
    [float, "voltage2"],
    [float, "voltage3"],
    [float, "current"],
    [float, "current2"],
    [float, "current3"],
    [float, "active_power"],
    [float, "active_power2"],
    [float, "active_power3"],
    [float, "reactive_power"],
    [float, "reactive_power2"],
    [float, "reactive_power3"],
    [float, "power_factor"],
    [float, "power_factor2"],
    [float, "power_factor3"],
    [float, "frequency"],
    [float, "frequency2"],
    [float, "frequency3"],
# relocate SDM630_IMPORT and SDM72_IMPEXP
    [float, "export_active"],
    [float, "export_active2"],
    [float, "export_active3"],

    [float, "start_energy"],
    [float, "daily"],
    [float, "total"],

    [uint32, "kWhtoday_delta"],
    [uint32, "kWhtoday_offset"],
    [uint32, "kWhtoday"],
    [uint32, "period"],

    [uint8, "fifth_second"],
    [uint8, "command_code"],
    [uint8, "data_valid"],
    [uint8, "data_valid2"],
    [uint8, "data_valid3"],

    [uint8, "phase_count"],

    [bool, "voltage_common"],
    [bool, "frequency_common"],
    [bool, "use_overtemp"],
    [bool, "kWhtoday_offset_init"],

    [bool, "voltage_available"],
    [bool, "current_available"],

    [bool, "type_dc"],
    [bool, "power_on"],
# #ifdef USE_ENERGY_MARGIN_DETECTION
    [uint16, "power_history_0"],
    [uint16, "power_history_02"],
    [uint16, "power_history_03"],
    [uint16, "power_history_1"],
    [uint16, "power_history_12"],
    [uint16, "power_history_13"],
    [uint16, "power_history_2"],
    [uint16, "power_history_22"],
    [uint16, "power_history_23"],

    [uint8, "power_steady_counter"],

    [bool, "min_power_flag"],
    [bool, "max_power_flag"],
    [bool, "min_voltage_flag"],
    [bool, "max_voltage_flag"],
    [bool, "min_current_flag"],
    [bool, "max_current_flag"],
    
# #ifdef USE_ENERGY_POWER_LIMIT
    [uint16, "mplh_counter"],
    [uint16, "mplw_counter"],
    [uint8, "mplr_counter"],
    [uint8, "max_energy_state"],
]
energy_struct = ctypes.structure(energy_struct, "energy_struct")

# struct ENERGY {
#   float voltage[ENERGY_MAX_PHASES];             // 123.1 V
#   float current[ENERGY_MAX_PHASES];             // 123.123 A
#   float active_power[ENERGY_MAX_PHASES];        // 123.1 W
#   float apparent_power[ENERGY_MAX_PHASES];      // 123.1 VA
#   float reactive_power[ENERGY_MAX_PHASES];      // 123.1 VAr
#   float power_factor[ENERGY_MAX_PHASES];        // 0.12
#   float frequency[ENERGY_MAX_PHASES];           // 123.1 Hz
# #if defined(SDM630_IMPORT) || defined(SDM72_IMPEXP)
#   float import_active[ENERGY_MAX_PHASES];       // 123.123 kWh
# #endif  // SDM630_IMPORT || SDM72_IMPEXP
#   float export_active[ENERGY_MAX_PHASES];       // 123.123 kWh

#   float start_energy;                           // 12345.12345 kWh total previous
#   float daily;                                  // 123.123 kWh
#   float total;                                  // 12345.12345 kWh total energy

#   unsigned long kWhtoday_delta;                 // 1212312345 Wh 10^-5 (deca micro Watt hours) - Overflows to Energy.kWhtoday (HLW and CSE only)
#   unsigned long kWhtoday_offset;                // 12312312 Wh * 10^-2 (deca milli Watt hours) - 5764 = 0.05764 kWh = 0.058 kWh = Energy.daily
#   unsigned long kWhtoday;                       // 12312312 Wh * 10^-2 (deca milli Watt hours) - 5764 = 0.05764 kWh = 0.058 kWh = Energy.daily
#   unsigned long period;                         // 12312312 Wh * 10^-2 (deca milli Watt hours) - 5764 = 0.05764 kWh = 0.058 kWh = Energy.daily

#   uint8_t fifth_second;
#   uint8_t command_code;
#   uint8_t data_valid[ENERGY_MAX_PHASES];

#   uint8_t phase_count;                          // Number of phases active
#   bool voltage_common;                          // Use single voltage
#   bool frequency_common;                        // Use single frequency
#   bool use_overtemp;                            // Use global temperature as overtemp trigger on internal energy monitor hardware
#   bool kWhtoday_offset_init;

#   bool voltage_available;                       // Enable if voltage is measured
#   bool current_available;                       // Enable if current is measured

#   bool type_dc;
#   bool power_on;

# #ifdef USE_ENERGY_MARGIN_DETECTION
#   uint16_t power_history[ENERGY_MAX_PHASES][3];
#   uint8_t power_steady_counter;                 // Allow for power on stabilization
#   bool min_power_flag;
#   bool max_power_flag;
#   bool min_voltage_flag;
#   bool max_voltage_flag;
#   bool min_current_flag;
#   bool max_current_flag;

# #ifdef USE_ENERGY_POWER_LIMIT
#   uint16_t mplh_counter;
#   uint16_t mplw_counter;
#   uint8_t mplr_counter;
#   uint8_t max_energy_state;
# #endif  // USE_ENERGY_POWER_LIMIT
# #endif  // USE_ENERGY_MARGIN_DETECTION
# } Energy;

#
ctypes.print_classes()
