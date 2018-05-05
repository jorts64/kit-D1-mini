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
"<form action='canviar' method='get'>"
"<input type='color' name='favcolor' value='#ff0000'>"
"<input type='submit' value='CANVIAR' /></br>"
"</form>"
"</body>"
"</html>";

void paginacanvi() {
  server.send(200, "text/html", pagina); 
}

int hex2dec(byte c) {
  if (c >= '0' && c <= '9') {
    return c - '0';
  } else if (c >= 'A' && c <= 'F') {
    return c - 'A' + 10;
  } else if (c >= 'a' && c <= 'f') {
    return c - 'a' + 10;
  }
}

void canviar_colors() {
  int r,g,b;
  String c;
  c = server.arg("favcolor");
  Serial.print("c= ");
  Serial.println(c);
  r=hex2dec(c.charAt(1))*16+hex2dec(c.charAt(2));
  g=hex2dec(c.charAt(3))*16+hex2dec(c.charAt(4));
  b=hex2dec(c.charAt(5))*16+hex2dec(c.charAt(6));
  Serial.print("r= ");
  Serial.println(r);
  Serial.print("g= ");
  Serial.println(g);
  Serial.print("b= ");
  Serial.println(b);
  pixels.setPixelColor(0, r, g, b);
  pixels.show(); // This sends the updated pixel color to the hardware.
  paginacanvi();
}

void setup() {
  Serial.begin(115200);
  WiFi.begin ( ssid, password );
  pixels.begin(); // This initializes the NeoPixel library.
  server.on("/", paginacanvi); //esta es la pagina de configuracion
  server.on("/canviar", canviar_colors); //Graba en la eeprom la configuracion
  server.begin();

  pixels.setPixelColor(0, pixels.Color(0, 63, 0));
  pixels.show(); // This sends the updated pixel color to the hardware.

}

void loop() {
  server.handleClient();
}


