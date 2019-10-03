#include <ESP8266WiFi.h>
#include <Wire.h>
#include "RTClib.h"
RTC_DS1307 RTC;
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

#ifndef APSSID
#define APSSID "Taula2"
#define APPSK  "pollauraadrian"
#endif
const char *ssid = APSSID;
const char *password = APPSK;

ESP8266WebServer server(80);

/* Just a little test message.  Go to http://192.168.4.1 in a web browser
   connected to this access point to see it.
*/

String msg1= "<!DOCTYPE html>"
"<html>"
"<head>"
"<title>Control del Despertador</title>"
"<meta charset='UTF-8'>"
"<meta name='viewport' content='width=device-width'/>"
"</head>"
"<body>"
"<table style='width:100%'><form action='canviar' method='get'>"
"<tr><td>Any:</td><td><input type='number' name='y' min='2019' step='1' value='";
String msg2= "'></td></tr>"
"<tr><td>Mes:</td><td><input type='number' name='mth' min='1' max='12' step='1' value='";
String msg3= "'></td></tr>"
"<tr><td>Dia:</td><td><input type='number' name='d' min='1' max='31' step='1' value='";
String msg4= "'></td></tr>"
"<tr><td>Hora:</td><td><input type='number' name='h'min='0' max='23' step='1' value='";
String msg5= "'></td></tr>"
"<tr><td>Minut:</td><td><input type='number' name='m'min='0' max='60' step='1' value='";
String msg6= "'></td></tr>"
"<tr><td>Melodia:</td><td><input type='number' name='mel'min='0' max='1' step='1' value='";
String msg7= "'></td></tr>"
"<tr><td></td><td><input type='submit' value='Establir' /></td></tr>"
"</form></table>"
"</body>"
"</html>";

DateTime now = RTC.now();
int ds = now.day();
int mths = now.month();
int ys = 0;
int hs = 12;
int ms = 0;
int ss = 0;
int mels = 0;
int d = now.day();
int mth = now.month();
int y = 0;
int h = 12;
int m = 0;
int s = 0;
int mel = 0;

void handleRoot() {
  String pagina = msg1+ys+msg2+mths+msg3+ds+msg4+hs+msg5+ms+msg6+mels+msg7;
  server.send(200, "text/html",pagina);
}

void alarma1(){
  d = server.arg("d").toInt();
  mth = server.arg("mth").toInt();
  y = server.arg("y").toInt();
  h = server.arg("h").toInt();
  m = server.arg("m").toInt();
  mel = server.arg("mel").toInt();
  handleRoot();
}


int notes [36][3] =
{
{'8',B00100000,262}, // C5
{'(',B00100001,277}, // C5#
{'9',B00100010,294}, // D5
{')',B00100011,311}, // D5#
{'0',B00100100,330}, // E5
{'q',B00100101,349}, // F5
{'Q',B00100110,370}, // F5#
{'w',B00100111,392}, // G5
{'W',B00101000,415}, // G5#
{'e',B00101001,440}, // A5
{'E',B00101010,466}, // A5#
{'r',B00101011,494}, // B5
{'t',B00000000,523}, // C6
{'T',B00000001,554}, // C6#
{'y',B00000010,587}, // D6
{'Y',B00000011,622}, // D6#
{'u',B00000100,669}, // E6
{'i',B00000101,698}, // F6
{'I',B00000110,740}, // F6#
{'o',B00000111,784}, // G6
{'O',B00001000,831}, // G6#
{'p',B00001001,880}, // A6
{'P',B00001010,932}, // A6#
{'a',B00001011,988}, // B6
{'s',B00010000,1047}, // C7
{'S',B00010001,1109}, // C7#
{'d',B00010010,1175}, // D7
{'D',B00010011,1245}, // D7#
{'f',B00010100,1318}, // E7
{'g',B00010101,1396}, // F7
{'G',B00010110,1480}, // F7#
{'h',B00010111,1568}, // G7
{'H',B00011000,1661}, // G7#
{'j',B00011001,1760}, // A7
{'J',B00011010,1865}, // A7#
{'k',B00011011,1975}, // B7
};


int buzzer=D5; //Buzzer control port, default D5
int button=D3;

String melodia1 = "ff f sf h   o   s  o  u  p a Pp o fhj gh f sda  s  o  u  p a Pp o fhj gh f sda  fs  o O pf fp   a jjj hgfs po   fs  o O pf fp   a jjj hgfs po   s  o  u  p a Pp o fhj gh f sda  hGgd f Ops psd  hGgd f s ss   hGgd f Ops psd  D  d  s   ";
String melodia2 = "o t Yio t Yio t Yio t uio t uio t uio t uio t uiooo ttt Yiooo ttt Yiy w Ety w Ety w Ety w y iii EEE Yyiii EEE Yyt q WEt q WEt q WEt";//"oii paSdfgf dd ddsPpoP pp oipoyi ppoii paSdfgf dd ddsPpoP pp oipoyi ppp p dfgfd fdsd pp p dfgfd fsPf g s P poii paSdfgf dd ddsPpoPpp oipoyi ppp p dfgfd fdsd pp p dfgfd fsPf goii paSdfgf dd ddsPpoPpp oipoyi ppipoyi pp";

int melodia[] = {0xEB,0xEB,0xEB,0xEC,0xEB,0xEB,0xEB,0xEC,0xEB,0xC2,0xE7,0xE9,0xAB,0xC0,0xC0,0x80,0xEB,0xEB,0xAB,0xEB,0xE9,0xE9,0xEB,0xA9,0xC2};

void playn (String melody) {
    for(int j=0; j<melody.length(); j++){
    int i;
    if ((melody.charAt(j)==' ')||(melody.charAt(j)=='|')) {
      if (melody.charAt(j)==' '){
        delay(150);        
      }
      else {
        delay(600);                
      }
    }
    else
    {
      for(i=0; notes[i][0]!=melody.charAt(j);i++);
      analogWriteFreq(notes[i][2]);
      analogWrite(buzzer, 512);
      delay(125);
      analogWrite(buzzer, 0);
      pinMode(buzzer, OUTPUT);
      digitalWrite(buzzer, LOW);
      delay(3);
      if(digitalRead(button)==0){
        break;
      }
    }
  }
}

void playp (int pmelody[], int n){
    for(int j=0; j<n; j++){
    int i,c,d;
    c = pmelody[j] & B00111111;
    d = 131;
    if (pmelody[j] & B01000000) d = d / 2;
    if (pmelody[j] & B10000000) d = d * 4;
    if (pmelody[j] & B11000000) d = d * 2;
    if ((c & B00001100)== B00001100) {
      delay (d);
    }
    else {
      for(i=0; notes[i][1]!=c;i++);
      analogWriteFreq(notes[i][2]);
      analogWrite(buzzer, 512);
      delay(d);
      analogWrite(buzzer, 0);
      pinMode(buzzer, OUTPUT);
      digitalWrite(buzzer, LOW);
      delay(d/7);    
    }
  }
}


void setup() {
    delay(1000);
    Serial.begin(9600);
  Wire.begin();
  RTC.begin();
  if (! RTC.isrunning()) {
  Serial.println("RTC is NOT running!");
  RTC.adjust(DateTime(__DATE__, __TIME__));
  }
  DateTime now = RTC.now();
  ds = now.day();
  mths = now.month();
  ys = now.year();
  hs = now.hour();
  ms = now.minute();
  ss = 0;
  mels = 0;

  WiFi.softAP(ssid, password);

  IPAddress myIP = WiFi.softAPIP();
  server.on("/", handleRoot);
  server.on("/canviar", alarma1);
  server.begin();
  
  
  pinMode(buzzer, OUTPUT);
  digitalWrite(buzzer, LOW);
  }


void loop() {
  server.handleClient();
  DateTime now = RTC.now();
    ds = now.day();
    mths = now.month();
    ys = now.year();
    hs = now.hour();
    ms = now.minute();
  Serial.print(now.day(), DEC);
  Serial.print('/');
  Serial.print(now.month(), DEC);
  Serial.print('/');
  Serial.print(now.year(), DEC);
  Serial.print(' ');
  Serial.print(now.hour(), DEC);
  Serial.print(':');
  Serial.print(now.minute(), DEC);
  Serial.print(':');
  Serial.print(now.second(), DEC);
  Serial.println();
  delay(1000);
  if(now.day()==d & now.month()==mth & now.year()==y & now.hour()==h & now.minute()==m & now.second()==s){
    if(mel==0){
      playn (melodia1);
    }else if(mel==1){
      playn (melodia2);
    }
    delay(1000);
  }

}
