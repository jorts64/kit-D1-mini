 #include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <FS.h>

const char *ssid = "ModoDiablo";
const char *password = "Eskereee";

ESP8266WebServer server ( 80 );

#include <Adafruit_NeoPixel.h>
#define PIN            D8
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(7, PIN, NEO_GRB + NEO_KHZ800);

String mensaje = "";

//-----------CODIGO HTML PAGINA DE CONFIGURACION---------------
String pagina = "<!DOCTYPE html>"
"<html>"
"<head>"
"<title>Canvis de color</title>"
"<meta charset='UTF-8'>"
"</head>"
"<body>"
"<img src='/img/led7.jpg' width='375' height='362' alt='COLOREH'>"
"<form action='canviar' method='get'>"
"<select name='nled'>"
"<option value='0'>Central</option>"
"<option value='1'>N</option>"
"<option value='2'>NE</option>"
"<option value='3'>SE</option>"
"<option value='4'>S</option>"
"<option value='5'>SW</option>"
"<option value='6'>NW</option>"
"</select>"
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
  String led;
  c = server.arg("favcolor");
  led = server.arg("nled");
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
  pixels.setPixelColor(led.toInt(), r, g, b);
  pixels.show(); // This sends the updated pixel color to the hardware.
  paginacanvi();
}

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_AP);
  WiFi.softAP ( ssid, password );
  pixels.begin(); 
  SPIFFS.begin();
  server.on("/", paginacanvi); 
  server.on("/canviar", canviar_colors); 
  server.serveStatic("/img", SPIFFS, "/img");
  server.begin();

  pixels.setPixelColor(0, pixels.Color(0, 0, 0));  
  pixels.setPixelColor(1, pixels.Color(0, 0, 0));  
  pixels.setPixelColor(2, pixels.Color(0, 0, 0));
  pixels.setPixelColor(3, pixels.Color(0, 0, 0));
  pixels.setPixelColor(4, pixels.Color(0, 0, 0));  
  pixels.setPixelColor(5, pixels.Color(0, 0, 0));
  pixels.setPixelColor(6, pixels.Color(0, 0, 0));
  pixels.show(); 

}

void loop() {
  server.handleClient();
}

