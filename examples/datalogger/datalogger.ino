#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <FS.h>
#include <WEMOS_DHT12.h>

DHT12 dht12;
ESP8266WebServer server ( 80 );
unsigned long ara;

const char *ssid = "Nom de la xarxa";
const char *password = "contrasenya";

void espera (int n) {
  while (millis()<ara+n) {
    delay(1);
    server.handleClient();  
  }
}

void setup() {
  Serial.begin(9600);
  SPIFFS.begin();
  WiFi.begin ( ssid, password );
  while ( WiFi.status() != WL_CONNECTED ) {
    delay ( 500 );
  }
  Serial.println ( "" );
  Serial.print ( "Connected to " );
  Serial.println ( ssid );
  Serial.print ( "IP address: " );
  Serial.println ( WiFi.localIP() );
  server.serveStatic("/dades", SPIFFS, "/dades"); //  gauge files dir
  server.begin();
  SPIFFS.remove("/dades/dat1.csv");
}

void loop() { 
  File f = SPIFFS.open("/dades/dat1.csv","a");
    for(int i=1; i<=100; i++){
      ara = millis();
      if(dht12.get()==0){
        f.print(ara/1000);
        f.print(",");
        f.println(dht12.cTemp);
        espera(1000);
      }
      
    }
  f.close();
}


