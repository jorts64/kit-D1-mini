#include <FS.h>
#include "FSManager.h"
extern ESP8266WebServer server;

void setup() {
  SPIFFS.begin();
  pinMode(D4,OUTPUT);
  initHelper(); //inclou connexió Wifi i server
  server.begin();
}

void loop() {
  digitalWrite(D4,LOW);
  espera(100);      
  digitalWrite(D4,HIGH);
  espera(100);        
}


