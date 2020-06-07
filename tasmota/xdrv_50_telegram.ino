/*
  xdrv_50_telegram.ino - telegram for Tasmota

  Copyright (C) 2020  Theo Arends

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

#ifdef USE_TELEGRAM
/*********************************************************************************************\
 * Telegram bot
\*********************************************************************************************/

#define XDRV_50                               50

#include "WiFiClientSecureLightBearSSL.h" 

static const uint8_t Telegram_Fingerprint[] PROGMEM = USE_TELEGRAM_FINGERPRINT;

struct {
  String message[3][6];  // amount of messages read per time  (update_id, name_id, name, lastname, chat_id, text)
  bool init = false;

} Telegram;

int Bot_mtbs = 1000; //mean time between scan messages
long Bot_lasttime;   //last time messages' scan has been done

BearSSL::WiFiClientSecure_light *telegramClient;

/**************************************************************************************************
 * function to achieve connection to api.telegram.org and send command to telegram                *
 * (Argument to pass: URL to address to Telegram)                                                 *
 **************************************************************************************************/
String TelegramConnectToTelegram(String command) {
  String mess="";
#ifdef USE_MQTT_TLS_CA_CERT
  static const uint32_t tls_rx_size = 2048;   // since Telegram CA is bigger than 1024 bytes, we need to increase rx buffer
  static const uint32_t tls_tx_size = 1024;
#else
  static const uint32_t tls_rx_size = 1024;
  static const uint32_t tls_tx_size = 1024;
#endif 

  std::unique_ptr<BearSSL::WiFiClientSecure_light>telegramClient(new BearSSL::WiFiClientSecure_light(tls_rx_size, tls_tx_size));
#ifdef USE_MQTT_TLS_CA_CERT
  telegramClient->setTrustAnchor(&GoDaddyCAG2_TA);
#else
  telegramClient->setPubKeyFingerprint(Telegram_Fingerprint, Telegram_Fingerprint, true); // check server fingerprint
#endif
  HTTPClient https;

  AddLog_P2(LOG_LEVEL_DEBUG, PSTR("TLG: Cmnd %s"), command.c_str());
  uint32_t tls_connect_time = millis();

  if (https.begin(*telegramClient, "https://api.telegram.org/" + command)) {  // HTTPS
    int httpCode = https.GET();

    // httpCode will be negative on error
    if (httpCode > 0) {
      AddLog_P2(LOG_LEVEL_INFO, PSTR(D_LOG_MQTT "TLS connected in %d ms, max ThunkStack used %d"),
        millis() - tls_connect_time, telegramClient->getMaxThunkStackUse());

      // HTTP header has been send and Server response header has been handled
      // Serial.printf("[HTTPS] GET... code: %d\n", httpCode);
      // file found at server?
      if (httpCode == HTTP_CODE_OK) {
        String payload = https.getString();
        // Serial.println("[HTTPS] Received payload telegram: ");
        mess=payload;
        // Serial.println(String("1BTC = ") + payload + "USD");
      }
    } else {
      // Serial.printf("TLS error :%d\n", telegramClient->getLastError());
      Serial.printf("[HTTPS] GET telegram... failed, error: %s\n\r", https.errorToString(httpCode).c_str());
    }
    https.end();
  } else {
    AddLog_P2(LOG_LEVEL_INFO, PSTR("TLG: TLS error :%d"), telegramClient->getLastError());
#ifndef USE_MQTT_TLS_CA_CERT
    char buf_fingerprint[64];
    ToHex_P((unsigned char *)telegramClient->getRecvPubKeyFingerprint(), 20, buf_fingerprint, sizeof(buf_fingerprint), ' ');
    AddLog_P2(LOG_LEVEL_DEBUG, PSTR(D_LOG_MQTT "Server fingerprint: %s"), buf_fingerprint);
#endif // USE_MQTT_TLS_CA_CERT
    telegramClient->stop();
  }

  return mess;
}

/***************************************************************
 * GetUpdates - function to receive all messages from telegram *
 * (Argument to pass: the last+1 message to read)             *
 ***************************************************************/
void TelegramGetUpdates(String offset) {
  Serial.println("GET Update Messages ");

  String _token = SettingsText(SET_TELEGRAMTOKEN);

  String command="bot" + _token + "/getUpdates?offset=" + offset;
  String mess = TelegramConnectToTelegram(command);       //recieve reply from telegram.org
  // parsing of reply from Telegram into separate received messages
  int i=0;                //messages received counter
  if (mess != ""  && (WiFi.status() == WL_CONNECTED)) {

    Serial.print("Sent Update request messages up to : ");
    Serial.println(offset);

    String a="";
    int ch_count=0;
    String c;
    for (int n=1; n<mess.length()+1; n++) {   //Search for each message start
      ch_count++;
      c = mess.substring(n-1,n);

    //Serial.print(c);

      a=a+c;
      if (ch_count>8) {
        if (a.substring(ch_count-9)=="update_id")  {
          if (i>1) { break; }
          Telegram.message[i][0] = a.substring(0, ch_count-11);
          a = a.substring(ch_count-11);
          i++;
          ch_count = 11;
        }
      }
    }
    if (1 == i) {
      Telegram.message[i][0] = a.substring(0, ch_count);   //Assign of parsed message into message matrix if only 1 message)
    }
    if (i > 1) { i= i -1; }
  }
  //check result of parsing process
  if (mess == "") {
    Serial.println("failed to update");
    return;
  }
  if (0 == i) {
    Serial.println("no new messages");
    Serial.println();
    Telegram.message[0][0] = "0";
  } else {
    Telegram.message[0][0] = String(i);   //returns how many messages are in the array

//Serial.println();

    for (int b=1; b<i+1; b++) {
      Serial.println(Telegram.message[b][0]);
    }
    Serial.println();
//    analizeMessages();
  }
}

void TelegramInit(void) {
  if (strlen(SettingsText(SET_TELEGRAMTOKEN))) {
	  Telegram.message[0][0]="0";   // number of received messages
	  Telegram.message[1][0]="";
    Telegram.message[0][1]="0";  // code of last read Message
    Telegram.init = true;

    AddLog_P2(LOG_LEVEL_DEBUG, PSTR("TLG: Started"));
  }
}

bool telegram_busy = false;

void TelegramLoop(void) {
  if (!global_state.wifi_down) {
    if (!Telegram.init) {
      TelegramInit();
    } else {
      if (!telegram_busy && (millis() > Bot_lasttime + Bot_mtbs))  {
        telegram_busy = true;

        TelegramGetUpdates(Telegram.message[0][1]);   // launch API GetUpdates up to xxx message
//        for (int i = 1; i < Telegram.message[0][0].toInt() + 1; i++)      {
//          TelegramSendMessage(Telegram.message[i][4], Telegram.message[i][5], "");
//        }
        Telegram.message[0][0] = "";   // All messages have been replied - reset new messages

        telegram_busy = false;
        Bot_lasttime = millis();
      }
    }
  }
}

/*********************************************************************************************\
 * Commands
\*********************************************************************************************/

#define D_CMND_TELEGRAMSEND "Send"
#define D_CMND_TELEGRAMTOKEN "Token"

const char kTelegramCommands[] PROGMEM = "Telegram|"  // No prefix
  D_CMND_TELEGRAMTOKEN "|" D_CMND_TELEGRAMSEND;

void (* const TelegramCommand[])(void) PROGMEM = {
  &CmndTelegramToken, &CmndTelegramSend };

void CmndTelegramToken(void) {
  if (XdrvMailbox.data_len > 0) {
    SettingsUpdateText(SET_TELEGRAMTOKEN, ('"' == XdrvMailbox.data[0]) ? "" : XdrvMailbox.data);
  }
  ResponseCmndChar(SettingsText(SET_TELEGRAMTOKEN));
}

void CmndTelegramSend(void) {

  ResponseCmndNumber(1);
}

/*********************************************************************************************\
 * Interface
\*********************************************************************************************/

bool Xdrv50(uint8_t function)
{
  bool result = false;

  switch (function) {
    case FUNC_EVERY_SECOND:
      TelegramLoop();
      break;
    case FUNC_COMMAND:
      result = DecodeCommand(kTelegramCommands, TelegramCommand);
      break;
  }
  return result;
}
#endif  // USE_TELEGRAM
