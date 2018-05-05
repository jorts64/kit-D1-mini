#include <ESP8266WiFi.h>
#include "ThingSpeak.h"
#include <WEMOS_DHT12.h>

DHT12 dht12;

const char *ssid = "Nom de la xarxa WiFi aqui";
const char *password = "Contrasenya de la WiFi aqui";
WiFiClient  client;
unsigned long myChannelNumber = 135405; //canvia pel teu canal
const char * myWriteAPIKey = "API key aqui";

const int led = BUILTIN_LED;  // internal blue led

void setup () {
  pinMode ( led, OUTPUT );
  digitalWrite ( led, HIGH );

  WiFi.begin ( ssid, password );

  // Wait for connection
  while ( WiFi.status() != WL_CONNECTED ) {
    delay ( 500 );
  }

  ThingSpeak.begin(client);
}

void loop () {

  digitalWrite ( led, LOW );
  dht12.get();
  ThingSpeak.writeField(myChannelNumber, 1, dht12.cTemp, myWriteAPIKey);
  digitalWrite ( led, HIGH );

  delay(60000); // ThingSpeak will only accept updates every 15 seconds.
}

