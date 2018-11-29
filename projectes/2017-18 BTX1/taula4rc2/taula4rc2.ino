#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <FS.h>

const char *ssid = "IPV-IOT-4";
const char *password = "INSPVIANA";

int Lectura,valor;

ESP8266WebServer server ( 80 );

#include <Adafruit_NeoPixel.h>
#define PIN            D2
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(1, PIN, NEO_GRB + NEO_KHZ800);

void handleRoot() {
  char temp[400];
  int sec = millis() / 1000;
  int min = sec / 60;
  int hr = min / 60;

  snprintf ( temp, 400,

"<html>\
  <head>\
    <meta http-equiv='refresh' content='5'/>\
    <title>ESP8266 Demo</title>\
    <style>\
      body { background-color: #cccccc; font-family: Arial, Helvetica, Sans-Serif; Color: #000088; }\
    </style>\
  </head>\
  <body>\
    <h1>Sonda de temperatura amb ESP8266</h1>\
    <p><a href='gauge/index.html'>gauge</a><p/>\
    <p>Uptime: %02d:%02d:%02d</p>\
  </body>\
</html>",

    hr, min % 60, sec % 60
  );
  server.send ( 200, "text/html", temp );
}

void handleAjax(){
  String out = "";
  char temp[100];
  snprintf(temp, 100, "%d", Lectura);
  out += temp;
  server.send ( 200, "text/txt", out);
}

void setup() {
  Serial.begin(115200);
  SPIFFS.begin();
  WiFi.mode(WIFI_AP);
  WiFi.softAP ( ssid, password );
  server.on ( "/", handleRoot );
  server.serveStatic("/gauge", SPIFFS, "/gauge"); //  gauge files dir
  server.on ("/ajax_info.txt", handleAjax );
  pixels.begin(); // This initializes the NeoPixel library.
  server.begin();

  pixels.setPixelColor(0, pixels.Color(0, 0, 0));
  pixels.show(); // This sends the updated pixel color to the hardware.

}

void loop() {
  server.handleClient();
       Lectura=0;
       for (int i=0;i<300;i++) {
          valor = analogRead(A0) ;
          Lectura = Lectura+valor;
       }
       Lectura = Lectura/300;
       Serial.println( Lectura);

       if (Lectura > 0) {
        pixels.setPixelColor(0, 0, 63, 0);
        pixels.show();
       }
       if (Lectura > 48) {
        pixels.setPixelColor(0, 0, 0, 63);
        pixels.show();
       }
       if (Lectura > 55) {
        pixels.setPixelColor(0, 63, 0, 0);
        pixels.show();
       }
}

