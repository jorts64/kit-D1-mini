#include <FS.h>
#include "FSManager.h"
extern ESP8266WebServer server;
#include <OneWire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS 2  // DS18B20 pin
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature DS18B20(&oneWire);
void handleRoot() {
  server.send(200, "text/plain", "hello from esp8266!");
}
  
void temperatura() {
  DS18B20.requestTemperatures(); 
  float t = DS18B20.getTempCByIndex(0);
  String s = String(t);
  server.send(200, "text/plain", s);
}

void setup(void){
  DS18B20.begin();
  SPIFFS.begin();
  initHelper(); //inclou connexió Wifi i server
  server.on("/", handleRoot);
  server.on("/temp", temperatura);
  server.begin();
  }

void loop(void){
  espera(100);   
  }

