/*
  xdrv_23_crash_recorder.ino - record a complete stacktrace in Flash in case of crash

  Copyright (C) 2019  Stephan Hadinger, Theo Arends, 

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

#define XDRV_32             32

const char kCrashRecorderCommands[] PROGMEM = "|" "Crash|CrashDump"; // No prefix

void (* const CrashRecorderCommand[])(void) PROGMEM = { &CmndCrash, &CmndCrashDump };

const uint32_t dump_max_len = 64;                   // dump only 64 call addresses

// typedef struct CrashRecorder_t {
//   uint64_t crash_signature = crash_sig;
//   uint32_t epc1;
//   uint32_t stack_start;
//   uint32_t stack_end;
//   uint32_t stack_dump_len;
//   uint32_t stack[];
// } CrashRecorder_t;

/**
 * Save crash information in Flash
 * This function is called automatically if ESP8266 suffers an exception
 * It should be kept quick / consise to be able to execute before hardware wdt may kick in
 */
extern "C" void custom_crash_callback(struct rst_info * rst_info, uint32_t stack, uint32_t stack_end ) {
  uint32_t addr_written = 0;      // how many addresses have we written in RTC
  uint32_t value;

  for (uint32_t i = stack; i < stack_end; i += 4) {
    value = *((uint32_t*) i);
    if ((value >= 0x40000000) && (value < 0x40300000)) {
      // valid address, we store it
      ESP.rtcUserMemoryWrite(addr_written, (uint32_t*)&value, sizeof(value));
      addr_written++;
      if (addr_written >= dump_max_len) { break; }
    }
  }
  // fill the rest of RTC with zeros
  value = 0;
  while (addr_written < dump_max_len) {
    ESP.rtcUserMemoryWrite(addr_written++, (uint32_t*)&value, sizeof(value));
  }
Serial.flush();
}

// Generate a crash to test the crash record
void CmndCrash(void)
{
  if (1 == XdrvMailbox.payload) {
    volatile uint32_t dummy;
    dummy = *((uint32_t*) 0x00000000);                // invalid address
  } else {
    ResponseCmndChar("1 to crash");
  }
}

void CrashDumpClear(void) {
  uint32_t value = 0;
  for (uint32_t i = 0; i < dump_max_len; i++) {
    ESP.rtcUserMemoryWrite(i, (uint32_t*)&value, sizeof(value));
  }
}

/*********************************************************************************************\
 * CmndCrashDump - dump the crash history
\*********************************************************************************************/

void CmndCrashDump(void)
{
  Response_P(PSTR("{\"call_chain\":["));
  for (uint32_t i = 0; i < dump_max_len; i++) {
    uint32_t value;
    ESP.rtcUserMemoryRead(i, (uint32_t*)&value, sizeof(value));
    if ((value >= 0x40000000) && (value < 0x40300000)) {
      if (i > 0) { ResponseAppend_P(PSTR(",")); }
      ResponseAppend_P(PSTR("\"%08x\""), value);
    }
  }
  ResponseAppend_P(PSTR("]}"));
}

/*********************************************************************************************\
 * Interface
\*********************************************************************************************/

bool Xdrv32(uint8_t function)
{
  if (FUNC_COMMAND == function) {
    return DecodeCommand(kCrashRecorderCommands, CrashRecorderCommand);
  } else {
    return false;
  }
}
