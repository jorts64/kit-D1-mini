#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <SD.h>
#include <WEMOS_DHT12.h>
#include <Wire.h>
#include "RTClib.h"

RTC_DS1307 RTC;
DateTime now;
DHT12 dht12;
ESP8266WebServer server ( 80 );
unsigned long ara;

const char *ssid = "Nom de la xarxa";
const char *password = "contrasenya";

void espera (int n) {
  while (millis()<ara+n) {
    delay(1);
  }
}

void sendFile() {
  
  File dataFile = SD.open("/dat1.csv");
  server.streamFile(dataFile, "application/octet-stream");
  dataFile.close();
}

void setup() {
  pinMode(D3,INPUT);
  pinMode(D4,OUTPUT);
  digitalWrite(D4,HIGH);
  Serial.begin(9600);
  SD.begin();
  SD.remove("/dat1.csv");
  Wire.begin();
  RTC.begin();
  if (! RTC.isrunning()) {
    Serial.println("RTC is NOT running!");
    RTC.adjust(DateTime(__DATE__, __TIME__));
  }
}

void loop() { 
  if (digitalRead(D3)==true){
  File f = SD.open("/dat1.csv",FILE_WRITE);
    for(int i=1; i<=30; i++){
      ara = millis();
      now = RTC.now(); 
      if(dht12.get()==0){
        f.print(ara/1000);
        f.print(",");
        f.print(now.day());
        f.print("/");
        f.print(now.month());
        f.print("/");
        f.print(now.year()%2000);
        f.print(" ");
        f.print(now.hour());
        f.print(":");
        f.print(now.minute());
        f.print(":");
        f.print(now.second());
        f.print(",");
        f.println(dht12.cTemp);
        espera(1000);
      }
    }
  f.close();
  }
  else {
    digitalWrite(D4,LOW);
    WiFi.begin ( ssid, password );
    while ( WiFi.status() != WL_CONNECTED ) {
      delay ( 500 );
    }
    Serial.println ( "" );
    Serial.print ( "Connected to " );
    Serial.println ( ssid );
    Serial.print ( "IP address: " );
    Serial.println ( WiFi.localIP() );
    server.on("/dat1.csv", HTTP_GET, sendFile);
    server.begin();
    while(true){
      server.handleClient();
    }
  }
}

