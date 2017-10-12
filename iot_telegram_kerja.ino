#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include "iot_rahasia.h"

// Initialize Wifi connection to the router
char ssid[] = WIFI_SSID;
char password[] = WIFI_PSWD; 

// Initialize Telegram BOT
const char* bot_nama = BOT_NAMA;
#define BOTtoken BOT_TOKEN 

WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);

int Bot_mtbs = 1000;
long Bot_lasttime;
bool Start = false;

const int saklar1 = 16;
const int saklar2 = 14;
const int saklar3 = 12;
const int saklar4 = 13;

int saklar1_status = 0;
int saklar2_status = 0;
int saklar3_status = 0;
int saklar4_status = 0;

void handleNewMessages(int numNewMessages) {
  Serial.println("handleNewMessages");
  Serial.println(String(numNewMessages));

  for (int i=0; i<numNewMessages; i++) {
    String chat_id = String(bot.messages[i].chat_id);
    String text = bot.messages[i].text;

    String from_name = bot.messages[i].from_name;
    if (from_name == "") from_name = "Guest";

    // ---- membuat variabel untuk saklar on ----

    String saklar1_on1 = "/kerja_lampu_on";
    String saklar1_on2 = saklar1_on1;
    saklar1_on2 += "@";
    saklar1_on2 += bot_nama;
    String saklar1_on3 = "lampu kerja telah dihidupkan...";

    String saklar2_on1 = "/kerja_kipas_on";
    String saklar2_on2 = saklar2_on1;
    saklar2_on2 += "@";
    saklar2_on2 += bot_nama;
    String saklar2_on3 = "kipas kerja telah dihidupkan...";

    String saklar3_on1 = "/kerja_saklar1_on";
    String saklar3_on2 = saklar3_on1;
    saklar3_on2 += "@";
    saklar3_on2 += bot_nama;
    String saklar3_on3 = "saklar kerja 1 telah dihidupkan...";

    String saklar4_on1 = "/kerja_saklar2_on";
    String saklar4_on2 = saklar4_on1;
    saklar4_on2 += "@";
    saklar4_on2 += bot_nama;
    String saklar4_on3 = "saklar kerja 2 telah dihidupkan...";

    if (text == saklar1_on1 or text == saklar1_on2) {
      digitalWrite(saklar1, HIGH);
      saklar1_status = 1;
      bot.sendMessage(chat_id, saklar1_on3, "");
    }

    if (text == saklar2_on1 or text == saklar2_on2) {
      digitalWrite(saklar2, HIGH);
      saklar2_status = 1;
      bot.sendMessage(chat_id, saklar2_on3, "");
    }

    if (text == saklar3_on1 or text == saklar3_on2) {
      digitalWrite(saklar3, HIGH);
      saklar3_status = 1;
      bot.sendMessage(chat_id, saklar3_on3, "");
    }

    if (text == saklar4_on1 or text == saklar4_on2) {
      digitalWrite(saklar4, HIGH);
      saklar4_status = 1;
      bot.sendMessage(chat_id, saklar4_on3, "");
    }

    // ---- membuat variabel untuk saklar off ----

    String saklar1_off1 = "/kerja_lampu_off";
    String saklar1_off2 = saklar1_off1;
    saklar1_off2 += "@";
    saklar1_off2 += bot_nama;
    String saklar1_off3 = "lampu kerja telah dimatikan...";

    String saklar2_off1 = "/kerja_kipas_off";
    String saklar2_off2 = saklar2_off1;
    saklar2_off2 += "@";
    saklar2_off2 += bot_nama;
    String saklar2_off3 = "kipas kerja telah dimatikan...";

    String saklar3_off1 = "/kerja_saklar1_off";
    String saklar3_off2 = saklar3_off1;
    saklar3_off2 += "@";
    saklar3_off2 += bot_nama;
    String saklar3_off3 = "saklar kerja 1 telah dimatikan...";

    String saklar4_off1 = "/kerja_saklar2_off";
    String saklar4_off2 = saklar4_off1;
    saklar4_off2 += "@";
    saklar4_off2 += bot_nama;
    String saklar4_off3 = "saklar kerja 2 telah dimatikan...";
    
    if (text == saklar1_off1 or text == saklar1_off2) {
      saklar1_status = 0;
      digitalWrite(saklar1, LOW);
      bot.sendMessage(chat_id, saklar1_off3, "");
    }

    if (text == saklar2_off1 or text == saklar2_off2) {
      saklar2_status = 0;
      digitalWrite(saklar2, LOW);
      bot.sendMessage(chat_id, saklar2_off3, "");
    }

    if (text == saklar3_off1 or text == saklar3_off2) {
      saklar3_status = 0;
      digitalWrite(saklar3, LOW);
      bot.sendMessage(chat_id, saklar3_off3, "");
    }

    if (text == saklar4_off1 or text == saklar4_off2) {
      saklar4_status = 0;
      digitalWrite(saklar4, LOW);
      bot.sendMessage(chat_id, saklar4_off3, "");
    }

    // ---- membuat variabel untuk status saklar ----

    String saklar_status1 = "/status";
    String saklar_status2 = saklar_status1;
    saklar_status2 += "@";
    saklar_status2 += bot_nama;
    
    if (text == saklar_status1 or text == saklar_status2) {
      
      String saklar1_status1 = "";
      if(saklar1_status){
        saklar1_status1 = "Posisi lampu kerja: hidup \n";
      } else {
        saklar1_status1 = "Posisi lampu kerja: mati \n";
      }

      String saklar2_status1 = "";
      if(saklar2_status){
        saklar2_status1 = "Posisi kipas kerja: hidup \n";
      } else {
        saklar2_status1 = "Posisi kipas kerja: mati \n";
      }

      String saklar3_status1 = "";
      if(saklar3_status){
        saklar3_status1 = "Posisi saklar kerja 1: hidup \n";
      } else {
        saklar3_status1 = "Posisi saklar kerja 1: mati \n";
      }

      String saklar4_status1 = "";
      if(saklar4_status){
        saklar4_status1 = "Posisi saklar kerja 2: hidup \n";
      } else {
        saklar4_status1 = "Posisi saklar kerja 2: mati \n";
      }

      String saklar_status_semua = "Status: \n";
      saklar_status_semua += saklar1_status1;
      saklar_status_semua += saklar2_status1;
      saklar_status_semua += saklar3_status1;
      saklar_status_semua += saklar4_status1;
      
      bot.sendMessage(chat_id, saklar_status_semua, "");
    }

    String saklar_start1 = "/start";
    String saklar_start2 = saklar_start1;
    saklar_start2 += "@";
    saklar_start2 += bot_nama;

    if (text == saklar_start1 or text == saklar_start2) {
      String welcome = "Selamat datang di aplikasi Universal Arduino Telegram Bot untuk ruang kerja, " + from_name + ".\n";
//      welcome += "/kerja_lampu_on : untuk menyalakan lampu LED \n";
//      welcome += "/kerja_lampu_off : untuk mematikan lampu LED \n";
//      welcome += "/kerja_kipas_on : untuk menyalakan kipas \n";
//      welcome += "/kerja_kipas_off : untuk mematikan kipas \n";
//      welcome += "/kerja_saklar1_on : untuk menyalakan Saklar 1 \n";
//      welcome += "/kerja_saklar1_off : untuk mematikan Saklar 2 \n";
//      welcome += "/kerja_saklar2_on : untuk menyalakan Saklar 1 \n";
//      welcome += "/kerja_saklar2_off : untuk mematikan Saklar 2 \n";
//      welcome += "/status : menginfokan status semua saklar\n";
      bot.sendMessage(chat_id, welcome, "Markdown");
    }
  }
}

void setup() {
  Serial.begin(115200);

  // Set WiFi to station mode and disconnect from an AP if it was Previously
  // connected
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

  // attempt to connect to Wifi network:
  Serial.println();
  Serial.println();
  Serial.print("Menghubungkan ke wifi ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  pinMode(saklar1, OUTPUT);
  pinMode(saklar2, OUTPUT);
  pinMode(saklar3, OUTPUT);
  pinMode(saklar4, OUTPUT);
  
  delay(10);
  digitalWrite(saklar1, LOW);
  digitalWrite(saklar2, LOW);
  digitalWrite(saklar3, LOW);
  digitalWrite(saklar4, LOW);
}

void loop() {
  if (millis() > Bot_lasttime + Bot_mtbs)  {
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);

    while(numNewMessages) {
      Serial.println("got response");
      handleNewMessages(numNewMessages);
      numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    }

    Bot_lasttime = millis();
  }
}
