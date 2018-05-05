/* 
 *  Concebut i recuinat per Jordi Orts (http://jorts.net)
 *  A la carpeta data s'utilitza la llibreria gauge.js amb llicencia MIT, http://bernii.github.io/gauge.js/
 *  Si us plau, respecteu aquestes llicencies
 */
 
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <FS.h>
#include <WEMOS_DHT12.h>

DHT12 dht12;


const char *ssid = "Aquí el nom de la teva xarxa";
const char *password = "Aquí la contrasenya de la xarxa";

ESP8266WebServer server ( 80 );

const int led = BUILTIN_LED;

int t;


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
    <h1>Sonda de temperatura amb ESP8266</h1>\
    <p><a href='gauge/index.html'>gauge</a><p/>\
    <p>Uptime: %02d:%02d:%02d</p>\
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
}



void setup ( void ) {
  pinMode ( led, OUTPUT );
  digitalWrite ( led, HIGH );
  Serial.begin ( 115200 );
  WiFi.begin ( ssid, password );
  SPIFFS.begin();
  Serial.println ( "" );

  // Wait for connection
  while ( WiFi.status() != WL_CONNECTED ) {
    delay ( 500 );
    Serial.print ( "." );
  }

  Serial.println ( "" );
  Serial.print ( "Connected to " );
  Serial.println ( ssid );
  Serial.print ( "IP address: " );
  Serial.println ( WiFi.localIP() );

  server.on ( "/", handleRoot );
  server.serveStatic("/gauge", SPIFFS, "/gauge"); //  gauge files dir
  server.on ("/ajax_info.txt", handleAjax );
  server.onNotFound ( handleNotFound );
  server.begin();
  Serial.println ( "HTTP server started" );
}

void loop ( void ) {
  server.handleClient();
}

