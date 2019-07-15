
#include <pgmspace.h>
#include <LString.h>

class LString getLStringTest(void) {
  LString s(10);
  s = "aaa";
  s += s.len();
  return s;
}

int TestLString(void) {
  LString s(10);
  s = "aazz";
  LString s2 = getLStringTest();

  s += "azerty";
  s += 2;
  s += "azerty";
  s += 4;
  s += s2;

  return s.len();
}

void TestCString(void) {
  LString deviceid = GetHueDeviceId2(255);
  LString userid = GetHueUserId2();
  Serial.printf("%s - %s\n", deviceid.c_str(), userid.c_str());
}

LString GetHueDeviceId2(uint8_t id)
{   // 5c:cf:7f:13:9f:3d:00:11-1
  LString deviceid(30, PSTR("%s:00:11-%d"), WiFi.macAddress().c_str(), id);
  deviceid.toLowerCase();
  return deviceid;
}

LString GetHueUserId2(void)
{
  LString userid(7, PSTR("%03x"), ESP.getChipId());
  return userid;
}

String HueSerialnumber2(void)
{
  String serial = WiFi.macAddress();
  serial.replace(":", "");
  serial.toLowerCase();
  return serial;  // 5ccf7f139f3d
}

LString HueUuid2(void)
{
  LString uuid(40, PSTR("f6543a06-da50-11ba-8d8f-%s"), HueSerialnumber2().c_str());
  return uuid;  // f6543a06-da50-11ba-8d8f-5ccf7f139f3d
}
