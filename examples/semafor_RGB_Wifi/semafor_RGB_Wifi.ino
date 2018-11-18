/*
 *  Jordi Orts. Novembre 2018
 *  https://github.com/jorts64
 *  Inspirat en el projecte #retoSemaforo
 *  https://twitter.com/hashtag/retoSemaforo
 */


#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

const char *ssid = "Semaforo";
const char *password = "robotica";

ESP8266WebServer server ( 80 );

#include <Adafruit_NeoPixel.h>

#define PIN   D8
#define LED_NUM 7

Adafruit_NeoPixel leds = Adafruit_NeoPixel(LED_NUM, PIN, NEO_GRB + NEO_KHZ800);

int tr=2000;
int ty=500;
int tg=1500;

String mensaje = "";

//-----------CODIGO HTML PAGINA DE CONFIGURACION---------------
String pagina = "<!DOCTYPE html>"
"<html>"
"<head>"
"<title>Control de temps semafor</title>"
"<meta charset='UTF-8'>"
"<meta name='viewport' content='width=device-width'/>"
"</head>"
"<body>"
"<table style='width:100%'><form action='canviar' method='get'>"
"<tr><td>Temps vermell:</td><td><input type='range' name='fr' min='1' max='60' value='3' step='1'></td></tr>"
"<tr><td>Temps groc:</td><td><input type='range' name='fy' min='1' max='60' value='1' step='1'></td></tr>"
"<tr><td>Temps verd:</td><td><input type='range' name='fg' min='1' max='60' value='2' step='1'></td></tr>"
"<tr><td></td><td><input type='submit' value='CANVIAR' /></td></tr>"
"</form></table>"
"</body>"
"</html>";

void espera(int temps) {
  unsigned long ara = millis();
  unsigned long seguent = ara + temps;
  delay(1); //refresh watchdog
  while (millis()<seguent){
      server.handleClient();
  }
}

void paginacanvi() {
  server.send(200, "text/html", pagina); 
}

void canviar_temps() {
  tr=server.arg("fr").toInt()*1000;
  ty=server.arg("fy").toInt()*1000;
  tg=server.arg("fg").toInt()*1000;
  paginacanvi();
}


void led_set(uint8 R, uint8 G, uint8 B) {
  for (int i = 0; i < LED_NUM; i++) {
    leds.setPixelColor(i, leds.Color(R, G, B));
    leds.show();
    delay(50);
  }
}

void red_set() {
  leds.setPixelColor(1, leds.Color(100, 0, 0));
  leds.setPixelColor(0, leds.Color(10, 10, 0));
  leds.setPixelColor(4, leds.Color(0, 10, 0));
  leds.show();
  espera(tr);
}

void yellow_set() {
  leds.setPixelColor(1, leds.Color(10, 0, 0));
  leds.setPixelColor(0, leds.Color(50, 50, 0));
  leds.setPixelColor(4, leds.Color(0, 10, 0));
  leds.show();
  espera(ty);
}

void green_set() {
  leds.setPixelColor(1, leds.Color(10, 0, 0));
  leds.setPixelColor(0, leds.Color(10, 10, 0));
  leds.setPixelColor(4, leds.Color(0, 100, 0));
  leds.show();
  espera(tg);
}


void setup() {
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, password);
  server.on("/", paginacanvi); 
  server.on("/canviar", canviar_temps); 
  server.begin();
  leds.begin();
  led_set(0, 0, 0);
}


void loop() {

  green_set();
  yellow_set();
  red_set();

}

