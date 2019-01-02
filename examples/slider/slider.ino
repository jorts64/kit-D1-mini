#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

const char *ssid = "Aquí el nom de la teva xarxa";
const char *password = "Aquí la contrasenya de la xarxa";

ESP8266WebServer server ( 80 );

#include <Adafruit_NeoPixel.h>
#define PIN            D2
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(1, PIN, NEO_GRB + NEO_KHZ800);

String mensaje = "";

//-----------CODIGO HTML PAGINA DE CONFIGURACION---------------
String pagina = "<!DOCTYPE html>"
"<html>"
"<head>"
"<title>Tutorial slider</title>"
"<meta charset='UTF-8'>"
"<meta name='viewport' content='width=device-width'/>"
"</head>"
"<body>"
"<table style='width:100%'><form action='canviar' method='get'>"
"<tr><td>Vermell:</td><td><input type='range' name='r' min='0' max='255'></td></tr>"
"<tr><td>Verd:</td><td><input type='range' name='g' min='0' max='255'></td></tr>"
"<tr><td>Blau:</td><td><input type='range' name='b' min='0' max='255'></td></tr>"
"<tr><td></td><td><input type='submit' value='CANVIAR' /></td></tr>"
"</form></table>"
"</body>"
"</html>";

void paginacanvi() {
  server.send(200, "text/html", pagina); 
}

void canviar_colors() {
  pixels.setPixelColor(0, server.arg("r").toInt(), server.arg("g").toInt(), server.arg("b").toInt());
  pixels.show(); // This sends the updated pixel color to the hardware.
  paginacanvi();
}

void setup() {
  WiFi.begin ( ssid, password );
  pixels.begin(); 
  server.on("/", paginacanvi); 
  server.on("/canviar", canviar_colors); 
  server.begin();

  pixels.setPixelColor(0, pixels.Color(0, 63, 0));
  pixels.show(); 

}

void loop() {
  server.handleClient();
}


