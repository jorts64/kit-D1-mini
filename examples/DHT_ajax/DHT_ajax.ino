
#include <FS.h>
#include "FSManager.h"
extern ESP8266WebServer server;

#include <WEMOS_DHT12.h>
DHT12 dht12;

void setup() {
  SPIFFS.begin();
  pinMode(D4,OUTPUT);
  initHelper(); //inclou connexió Wifi i server
  server.on("/ajax_info.txt", HTTP_GET, []() { 
    dht12.get();
    String txt = String(dht12.cTemp);
    server.send(200, "text/plain", txt);
    txt = String();
  });
  server.begin();
}

void loop() {
  digitalWrite(D4,LOW);
  espera(100);      
  digitalWrite(D4,HIGH);
  espera(100);        
}


