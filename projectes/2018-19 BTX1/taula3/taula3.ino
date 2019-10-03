#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <FS.h>
#include <WEMOS_DHT12.h>

DHT12 dht12;


const char *ssid = "XarxaTermo12";
const char *password = "Robotica12";

const int relayPin = D7;
const long interval = 2000;

int tmin=20;
int tmax=30;
ESP8266WebServer server ( 80 );

const int led = BUILTIN_LED;

int t;

String pagina = "<!DOCTYPE html>"
"<html>"
"<head>"
"<title>Seleccio de temperatures</title>"
"<meta charset='UTF-8'>"
"<meta name='viewport' content='width=device-width'/>"
"</head>"
"<body>"
"<table style='width:100%'><form action='canviar' method='get'>"
"<tr><td>Temp max:</td><td><input type='text' name='tmax' min='10' max='45' value='' step='1'></td></tr>"
"<tr><td>Temp min:</td><td><input type='text' name='tmin' min='10' max='45' value='' step='1'></td></tr>"
"<tr><td></td><td><input type='submit' value='CANVIAR' /></td></tr>"
"</form></table>"
"</body>"
"</html>";

void paginacanvi() {
  server.send(200, "text/html", pagina);
}

void canvites(){
  tmin = server.arg("tmin").toInt();
  tmax = server.arg("tmax").toInt();
  Serial.print ( "tmin=" );
  Serial.println ( tmin );
  Serial.print ( "tmax=" );
  Serial.println ( tmax );
  paginacanvi();
}

void handleRoot() {
  digitalWrite ( led, LOW );
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
    <H1>Termostato</H1>\
    <p><a href='gauge/index.html'>Indicador de temperatura</a><p/>\
    <p><a href='posar'>Seleccio Tmin Tmax</a><p/>\
  </body>\
</html>",

    hr, min % 60, sec % 60
  );
  server.send ( 200, "text/html", temp );
  digitalWrite ( led, HIGH );
}

void handleNotFound() {
  digitalWrite ( led, LOW );
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += ( server.method() == HTTP_GET ) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";

  for ( uint8_t i = 0; i < server.args(); i++ ) {
    message += " " + server.argName ( i ) + ": " + server.arg ( i ) + "\n";
  }

  server.send ( 404, "text/plain", message );
  digitalWrite ( led, HIGH );
}


void handleAjax(){
  digitalWrite ( led, LOW );
  dht12.get();
  t=dht12.cTemp;
  Serial.print("Temperature: ");
  Serial.println(t);
  String out = "";
  char temp[100];
  snprintf(temp, 100, "%d", t);
  out += temp;
  server.send ( 200, "text/txt", out);

  
  digitalWrite ( led, HIGH );
  if(dht12.cTemp<tmin){
  digitalWrite(relayPin,HIGH);
  delay(interval);
  }
  
if(dht12.cTemp>tmax){
  digitalWrite(relayPin,LOW);
  delay(interval);
  }

}

void controla(){
    if(dht12.cTemp<tmin){
  digitalWrite(relayPin,HIGH);
  }
  
if(dht12.cTemp>tmax){
  digitalWrite(relayPin,LOW);
  }

}

void setup ( void ) {
pinMode(relayPin,OUTPUT);

pinMode ( led, OUTPUT );
digitalWrite ( led, HIGH );
Serial.begin ( 115200 );
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, password);
SPIFFS.begin();
Serial.println ( "" );
// Wait for connection
server.on ( "/", handleRoot );
server.serveStatic("/gauge", SPIFFS, "/gauge"); //
server.on ("/ajax_info.txt", handleAjax );
server.on ("/posar", paginacanvi );
server.on("/canviar", canvites);
server.onNotFound ( handleNotFound );
server.begin();
Serial.println ( "HTTP server started" );



}

void loop ( void ) {
  server.handleClient();
  controla();
/*if(dht12.get()==0){
Serial.print("Temperature in Celsius : ");
Serial.println(dht12.cTemp);
Serial.print("Relative Humidity : ");
Serial.println(dht12.humidity);
Serial.println();
}
delay(1000);*/



}


