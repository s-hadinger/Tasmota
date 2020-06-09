/*
  xdrv_51_fft.ino - FFT

  Copyright (C) 2020 Stephan Hadinger

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

#ifdef USE_FFT

#define XDRV_51              51

#include "kiss_fftr.h"

// const char kFFTCommands[] PROGMEM = "|" D_CMND_THERMOSTATMODESET "|" D_CMND_CLIMATEMODESET "|" 
//   D_CMND_TEMPFROSTPROTECTSET "|" D_CMND_CONTROLLERMODESET "|" D_CMND_INPUTSWITCHSET "|" D_CMND_INPUTSWITCHUSE "|" 
//   D_CMND_OUTPUTRELAYSET "|" D_CMND_TIMEALLOWRAMPUPSET "|" D_CMND_TEMPFORMATSET "|" D_CMND_TEMPMEASUREDSET "|" 
//   D_CMND_TEMPTARGETSET "|" D_CMND_TEMPMEASUREDGRDREAD "|" D_CMND_SENSORINPUTSET "|" D_CMND_STATEEMERGENCYSET "|" 
//   D_CMND_TIMEMANUALTOAUTOSET "|" D_CMND_PROPBANDSET "|" D_CMND_TIMERESETSET "|" D_CMND_TIMEPICYCLESET "|" 
// #ifdef USE_PI_AUTOTUNING
//   D_CMND_TEMPANTIWINDUPRESETSET "|" D_CMND_TEMPHYSTSET "|" D_CMND_PERFLEVELAUTOTUNE "|" D_CMND_TIMEMAXACTIONSET "|" 
// #else
//   D_CMND_TEMPANTIWINDUPRESETSET "|" D_CMND_TEMPHYSTSET "|" D_CMND_TIMEMAXACTIONSET "|" 
// #endif // USE_PI_AUTOTUNING
//   D_CMND_TIMEMINACTIONSET "|" D_CMND_TIMEMINTURNOFFACTIONSET "|" D_CMND_TEMPRUPDELTINSET "|" D_CMND_TEMPRUPDELTOUTSET "|" 
//   D_CMND_TIMERAMPUPMAXSET "|" D_CMND_TIMERAMPUPCYCLESET "|" D_CMND_TEMPRAMPUPPIACCERRSET "|" D_CMND_TIMEPIPROPORTREAD "|" 
//   D_CMND_TIMEPIINTEGRREAD "|" D_CMND_TIMESENSLOSTSET "|" D_CMND_DIAGNOSTICMODESET "|" D_CMND_CTRDUTYCYCLEREAD "|" 
//   D_CMND_ENABLEOUTPUTSET;

// void (* const ThermostatCommand[])(void) PROGMEM = {
//   &CmndThermostatModeSet, &CmndClimateModeSet, &CmndTempFrostProtectSet, &CmndControllerModeSet, &CmndInputSwitchSet, 
//   &CmndInputSwitchUse, &CmndOutputRelaySet, &CmndTimeAllowRampupSet, &CmndTempFormatSet, &CmndTempMeasuredSet, 
//   &CmndTempTargetSet, &CmndTempMeasuredGrdRead, &CmndSensorInputSet, &CmndStateEmergencySet, &CmndTimeManualToAutoSet, 
//   &CmndPropBandSet, &CmndTimeResetSet, &CmndTimePiCycleSet, &CmndTempAntiWindupResetSet, &CmndTempHystSet, 
// #ifdef USE_PI_AUTOTUNING
//   &CmndPerfLevelAutotune, &CmndTimeMaxActionSet, &CmndTimeMinActionSet, &CmndTimeMinTurnoffActionSet, &CmndTempRupDeltInSet, 
// #else
//   &CmndTimeMaxActionSet, &CmndTimeMinActionSet, &CmndTimeMinTurnoffActionSet, &CmndTempRupDeltInSet, 
// #endif // USE_PI_AUTOTUNING
//   &CmndTempRupDeltOutSet, &CmndTimeRampupMaxSet, &CmndTimeRampupCycleSet, &CmndTempRampupPiAccErrSet, 
//   &CmndTimePiProportRead, &CmndTimePiIntegrRead, &CmndTimeSensLostSet, &CmndDiagnosticModeSet, &CmndCtrDutyCycleRead,
//   &CmndEnableOutputSet };

/*********************************************************************************************\
 * Interface
\*********************************************************************************************/

bool Xdrv51(uint8_t function)
{
  bool result = false;

  switch (function) {
    case FUNC_INIT:
      {
        kiss_fftr_cfg mycfg = kiss_fftr_alloc(1024,0,NULL,NULL);
      }
      break;
    case FUNC_LOOP:
      break;
    case FUNC_SERIAL:
      break;
    case FUNC_EVERY_SECOND:
      break;
    case FUNC_COMMAND:
    //   result = DecodeCommand(kThermostatCommands, ThermostatCommand);
      break;
  }
  return result;
}

#endif // USE_FFT
