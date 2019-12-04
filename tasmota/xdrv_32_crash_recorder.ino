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

#ifdef USE_CRASH_RECORDER

#define XDRV_32             32

const char kCrashRecorderCommands[] PROGMEM = "|" "CrashRecorder" "|" "CrashDump" "|" "Crash"; // No prefix

void (* const CrashRecorderCommand[])(void) PROGMEM = { &CmndCrashRecorder, &CmndCrashDump, &CmndCrash };

const uint32_t crash_bank = SETTINGS_LOCATION - CFG_ROTATES - 1;
const uint32_t crash_addr = crash_bank * SPI_FLASH_SEC_SIZE;
const uint64_t crash_sig   = 0xDEADBEEFCCAA5588L;     // arbitrary signature to check if crash was recorded
const uint64_t crash_empty = 0xFFFFFFFFFFFFFFFFL;     // all ones means the flash was correctly erased
const uint32_t dump_max_len = 1024;                   // dump only 1024 bytes of stack, i.e. 256 addresses

static boolean stacktrace_armed = false;        // should we record the stacktrace

typedef struct CrashRecorder_t {
  uint64_t crash_signature = crash_sig;
  struct rst_info info;
  uint32_t crash_date;
  uint32_t stack_start;
  uint32_t stack_end;
  uint32_t stack_dump_len;
  uint32_t stack[];
} CrashRecorder_t;

CrashRecorder_t crash_recorder;

// See: https://github.com/esp8266/Arduino/blob/master/cores/esp8266/core_esp8266_postmortem.cpp

/**
 * Save crash information in Flash
 * This function is called automatically if ESP8266 suffers an exception
 * It should be kept quick / consise to be able to execute before hardware wdt may kick in
 */
extern "C" void custom_crash_callback(struct rst_info * rst_info, uint32_t stack, uint32_t stack_end ) {
  if (!stacktrace_armed) { return; }    // exit if nothing to do

  crash_recorder.info             = *rst_info;
  crash_recorder.crash_date       = millis();
  crash_recorder.stack_start      = stack;
  crash_recorder.stack_end        = stack_end;

  uint64_t sig = 0;
  ESP.flashRead(crash_addr, (uint32_t*) &sig, sizeof(sig));

  if (crash_sig == sig) {
    return;                 // we already have a crash recorded, we leave it untouched and quit
  }
  if (crash_empty != sig) {
    // crash recorder zone is unknown content, we leave it untouched
    return;
    // if (ESP.flashEraseSector(crash_bank)) {}
  }
  // Flash has been erased, so we're good

  ESP.flashWrite(crash_addr, (uint32_t*) &crash_recorder, sizeof(crash_recorder));

  // now store the stack trace, limited to 3KB (which should be far enough)
  crash_recorder.stack_dump_len = stack_end - stack;
  if (crash_recorder.stack_dump_len > dump_max_len) { crash_recorder.stack_dump_len = dump_max_len; }

  ESP.flashWrite(crash_addr + sizeof(crash_recorder)/sizeof(crash_addr), (uint32_t*) stack, crash_recorder.stack_dump_len);
}

/*********************************************************************************************\
 * CmndCrashRecorder - arm the crash recorder until next reboot
\*********************************************************************************************/

// Input:
//  0 : disable crash recorcer
//  1 : soft enable, enable if there is not already a crash record present
//  2 : hard enable, erase any previous crash record and enable new record
//
// Output:
//  0 : Ok, disabled
//  1 : Ok, enabled
//  2 : Ok, enabled and previous record erased
// -1 : Abort, crash record already present
// -2 : Flash erase failed
// -99: Bad parameter
int32_t SetCrashRecorder(int32_t mode) {
  int32_t ret = 0;

  switch (mode) {
    case 1:
    case 2:
      {
        uint64_t sig = 0;
        ESP.flashRead(crash_addr, (uint32_t*) &sig, sizeof(sig));

        if ((crash_sig == sig) && (1 == mode)) {
          ret = -1;
          break;
        } else {
          if (crash_empty != sig) {
            // crash recorder zone is not clean
            if (ESP.flashEraseSector(crash_bank)) {
              ret = -2;
            } else {
              ret = 2;
            }
          } else {
            ret = 1;
          }
        }
      }
      break;
    case 0:
      ret = 0;
      break;
    default:
      ret = -99;
  }

  stacktrace_armed = (ret > 0) ? true : false;
  return ret;
}

// Generate a crash to test the crash record
void CmndCrash(void)
{
  volatile uint32_t dummy;

  switch (XdrvMailbox.payload) {
    case 1:
      dummy = *((uint32_t*) (((uint8_t*) &dummy)+1));   // unaligned access of 32 bits
      break;
    default:
    case -99:
      dummy = *((uint32_t*) 0x00000000);                // invalid address
      break;
  }
}


void CmndCrashRecorder(void)
{
  int32_t mode, ret;

  switch (XdrvMailbox.payload) {
    case -99:
      mode = 1;
      break;
    case 1:
      mode = 2;
      break;
    default:
      mode = 0;
  }

  ret = SetCrashRecorder(XdrvMailbox.payload);
  const char *msg;

  switch (ret) {
    case 0:
      msg = "Crash_recorder disabled.";
      break;
    case 1:
      msg = "Crash_recorder enabled until next reboot.";
      break;
    case 2:
      msg = "Crash_recorder erased and enabled until next reboot.";
      break;
    case -1:
      msg = "Abort: crash record already present, use 1 to erase.";
      break;
    case -2:
      msg = "Error: unable to clear Flash crash dump area.";
      break;
    default:
      msg = "";
  }
  ResponseCmndChar(msg);
}

/*********************************************************************************************\
 * CmndCrashDump - dump the crash history
\*********************************************************************************************/

void CmndCrashDump(void)
{
  CrashRecorder_t dump;

  ESP.flashRead(crash_addr, (uint32_t*) &dump, sizeof(dump));
  if (crash_sig == dump.crash_signature) {
    Response_P(PSTR("{\"reason\":%d,\"exccause\":%d,"
                    "\"epc1\":\"0x%04x\",\"epc2\":\"0x%04x\",\"epc3\":\"0x%04x\","
                    "\"excvaddr\":\"0x%04x\",\"depc\":\"0x%04x\","
                    "\"stack_start\":\"0x%04x\",\"stack_end\":\"0x%04x\","
                    "\"date_millis\":%d,"
                    "}"),
                    dump.info.reason, dump.info.exccause,
                    dump.info.epc1, dump.info.epc2, dump.info.epc3,
                    dump.info.excvaddr, dump.info.depc,
                    dump.stack_start, dump.stack_end,
                    dump.crash_date
                    );
    MqttPublishPrefixTopic_P(RESULT_OR_TELE, PSTR("crashdump"));
    XdrvRulesProcess();

    uint32_t stack_len  = dump.stack_dump_len <= dump_max_len ? dump.stack_dump_len : dump_max_len; // we will limit to 2k

    uint8_t dump_stack[stack_len];

    ESP.flashRead(crash_addr + sizeof(crash_recorder)/sizeof(crash_addr), (uint32_t*) dump_stack, stack_len);

    uint32_t dumped = 0;
    Response_P(PSTR("{\"call_chain\":\""));
    for (uint32_t i = 0; i < stack_len; i+=4) {
      uint32_t value = *((uint32_t*) (&dump_stack[i]));

      if (dumped > 0) {
        ResponseAppend_P(PSTR(" "));
      }
      ResponseAppend_P(PSTR("%04x"), value);
      dumped++;
      if (dumped >= 64) { break; }
    }
    ResponseAppend_P("\"}");
    MqttPublishPrefixTopic_P(RESULT_OR_TELE, PSTR("crashdump"));
    XdrvRulesProcess();
  } else {
    ResponseCmndChar("No crash dump found");
  }
}

/*********************************************************************************************\
 * Interface
\*********************************************************************************************/

bool Xdrv32(uint8_t function)
{
  bool result = false;

  switch (function) {
    case FUNC_COMMAND:
      result = DecodeCommand(kCrashRecorderCommands, CrashRecorderCommand);
      break;
  }
  return result;
}

#endif // USE_CRASH_RECORDER
