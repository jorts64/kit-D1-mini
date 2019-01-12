#include <FS.h>
#include "FSManager.h"
extern ESP8266WebServer server;
#define PIN 0

int estat;

void handleRoot() {
  server.send(200, "text/plain", "hello from esp8266!");
}
  

void engegar() {
  digitalWrite(PIN, LOW);
  estat=1;
  server.send(200, "text/plain", "ON");
}

void apagar() {
  estat=0;
  server.send(200, "text/plain", "OFF");
  digitalWrite(PIN, HIGH);
}

void canviar() {
  if(estat==0){
    digitalWrite(PIN, LOW);
    estat=1;
    }
   else{
    digitalWrite(PIN, HIGH);
    estat=0;
    }
  server.send(200, "text/plain", "CHANGED");
}

void report() {
  String t = String(estat);
  server.send(200, "text/plain", t);
}

void setup(void){
  pinMode(PIN, OUTPUT);
  digitalWrite(PIN, HIGH);
  estat = 0;
  SPIFFS.begin();
  initHelper(); //inclou connexió Wifi i server
  server.on("/", handleRoot);
  server.on("/on", engegar);
  server.on("/off", apagar);
  server.on("/change", canviar);
  server.on("/estat", report);
  server.begin();
  }

void loop(void){
  espera(100);   
  }

