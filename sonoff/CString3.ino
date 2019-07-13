
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

}

LString GetHueDeviceId2(uint8_t id)
{
  LString deviceid(30);
  deviceid.format(PSTR("%s:00:11-%d"), WiFi.macAddress().c_str(), id).toLowerCase();
  return deviceid;  // 5c:cf:7f:13:9f:3d:00:11-1
}

LString GetHueUserId2(void)
{
  LString userid(7);
  //char userid[7];
  userid.format(PSTR("%03x"), ESP.getChipId());
  return userid;
}
