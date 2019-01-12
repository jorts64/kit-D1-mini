#include <FS.h>
#include "FSManager.h"
extern ESP8266WebServer server;
#include "DHT.h"
#define DHTTYPE DHT11   // DHT 11
#define DHTPIN 2     // what digital pin we're connected to
DHT dht(DHTPIN, DHTTYPE);

void handleRoot() {
  server.send(200, "text/plain", "hello from esp8266!");
}
  

void humitat() {
  float h = dht.readHumidity();
  String s = String(h);
  server.send(200, "text/plain", s);
}

void temperatura() {
  float t = dht.readTemperature();
  String s = String(t);
  server.send(200, "text/plain", s);
}

void setup(void){
  dht.begin();
  SPIFFS.begin();
  initHelper(); //inclou connexió Wifi i server
  server.on("/", handleRoot);
  server.on("/rh", humitat);
  server.on("/temp", temperatura);
  server.begin();
  }

void loop(void){
  espera(100);   
  }

