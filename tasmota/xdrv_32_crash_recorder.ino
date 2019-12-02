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

const char kIrRemoteCommands[] PROGMEM = "|" "CrashRecorder" "|" "CrashDump" ; // No prefix

void (* const StacktraceCommand[])(void) PROGMEM = { &CmndCrashRecorder, &CmndCrashDump };

static boolean stacktrace_armed = false;        // should we record the stacktrace

typedef struct CrashRecorder {
  uint32_t crash_date;
  uint32_t epc1;
  uint32_t epc2;
  uint32_t epc3;
} CrashRecorder;

// #define SAVE_CRASH_CRASH_TIME       0x00  // 4 bytes
// #define SAVE_CRASH_RESTART_REASON   0x04  // 1 byte
// #define SAVE_CRASH_EXCEPTION_CAUSE  0x05  // 1 byte
// #define SAVE_CRASH_EPC1             0x06  // 4 bytes
// #define SAVE_CRASH_EPC2             0x0A  // 4 bytes
// #define SAVE_CRASH_EPC3             0x0E  // 4 bytes
// #define SAVE_CRASH_EXCVADDR         0x12  // 4 bytes
// #define SAVE_CRASH_DEPC             0x16  // 4 bytes
// #define SAVE_CRASH_STACK_START      0x1A  // 4 bytes
// #define SAVE_CRASH_STACK_END        0x1E  // 4 bytes
// #define SAVE_CRASH_STACK_TRACE      0x22  // variable

/*********************************************************************************************\
 * CmndCrashRecorder - arm the crash recorder until next reboot
\*********************************************************************************************/

void CmndCrashRecorder(void)
{
  switch (XdrvMailbox.payload) {
  case 1:
    stacktrace_armed = true;
    ResponseCmndChar("Stacktrace enabled until next reboot.");
    break;
  default:
    stacktrace_armed = false;
    ResponseCmndChar("Stacktrace disabled.");
  }
}

/*********************************************************************************************\
 * CmndCrashDump - dump the crash history
\*********************************************************************************************/

void CmndCrashDump(void)
{
  ResponseCmndChar("");
}

/*********************************************************************************************\
 * Interface
\*********************************************************************************************/

bool Xdrv32(uint8_t function)
{
  // bool result = false;

  // if ((pin[GPIO_IRSEND] < 99) || (pin[GPIO_IRRECV] < 99)) {
  //   switch (function) {
  //     case FUNC_PRE_INIT:
  //       if (pin[GPIO_IRSEND] < 99) {
  //         IrSendInit();
  //       }
  //       if (pin[GPIO_IRRECV] < 99) {
  //         IrReceiveInit();
  //       }
  //       break;
  //     case FUNC_EVERY_50_MSECOND:
  //       if (pin[GPIO_IRRECV] < 99) {
  //         IrReceiveCheck();  // check if there's anything on IR side
  //       }
  //       irsend_active = false;  // re-enable IR reception
  //       break;
  //     case FUNC_COMMAND:
  //       if (pin[GPIO_IRSEND] < 99) {
  //         result = DecodeCommand(kIrRemoteCommands, IrRemoteCommand);
  //       }
  //       break;
  //   }
  // }
  // return result;
}

#endif // USE_CRASH_RECORDER
