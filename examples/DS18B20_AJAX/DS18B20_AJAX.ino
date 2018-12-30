#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <OneWire.h>
#include <DallasTemperature.h>

const char *ssid = "jortsnet";
const char *password = "9periodico";

ESP8266WebServer server ( 80 );

#define ONE_WIRE_BUS D7  // DS18B20 pin
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature DS18B20(&oneWire);
float t;

const char *pagina = "<html>\
<head>\
  <meta http-equiv='Content-Type' content='text/html; charset=UTF-8'>\
  <meta name='viewport' content='width=device-width'> \
  <title>AJAX Test</title>\
  <style>body{padding:0;margin:0;background:#999}</style>\
  <script>\
function loadTemp() {\
  var xhttp = new XMLHttpRequest();\
  var temp = 0;\
  xhttp.open('GET', 'ajax_info.txt', false);\
  xhttp.send();\
  temp = parseFloat(xhttp.responseText);\
  return (temp);\
} \
  </script>\
</head>\
<body>\
<p>Temperatura:</p>\
<p id='demo'></p>\
<script>\
var myVar = setInterval(myTimer, 1000);\
function myTimer() {\
  document.getElementById('demo').innerHTML = loadTemp();\
}\
</script>\
</body>\
</html>";

void handleRoot() {
  server.send ( 200, "text/html", pagina );
}

void handleNotFound() {
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
}


void handleAjax(){
  DS18B20.requestTemperatures(); 
  t = DS18B20.getTempCByIndex(0);
  int t1,t2;
  Serial.print("Temperature: ");
  Serial.println(t);
  String out = "";
  char temp[100];
  t1 = int(t);
  snprintf(temp, 100, "%d", t1);
  out += temp;
  out += ".";
  t2 = int((t+0.005)*100)-100*t1;
  snprintf(temp, 100, "%d", t2);
  out += temp;

  server.send ( 200, "text/txt", out);
}

void setup ( void ) {
  Serial.begin ( 115200 );
  WiFi.begin ( ssid, password );
  DS18B20.begin();
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
  server.on ("/ajax_info.txt", handleAjax );
  server.onNotFound ( handleNotFound );
  server.begin();
  Serial.println ( "HTTP server started" );
}

void loop ( void ) {
  server.handleClient();
}

