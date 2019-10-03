#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
const char* ssid = "Semaforo";
const char* password = "robotica";

ESP8266WebServer server(80);
int estat;

void handleRoot() {
server.send(200, "text/plain", "hello from esp8266!");
}
void engegar() {
digitalWrite(D1, true);
estat=1;
server.send(200, "text/plain", "ON");
}
void apagar() {
estat=0;
server.send(200, "text/plain", "OFF");
digitalWrite(D1, false);
}
void canviar() {
if(estat==0){
digitalWrite(D1, true);
estat=1;
}
else{
digitalWrite(D1, false);
estat=0;
}
server.send(200, "text/plain", "CHANGED");
}
void handleNotFound(){
String message = "File Not Found\n\n";
message += "URI: ";
message += server.uri();
message += "\nMethod: ";
message += (server.method() == HTTP_GET)?"GET":"POST";
message += "\nArguments: ";message += server.args();
message += "\n";
for (uint8_t i=0; i<server.args(); i++){
message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
}
server.send(404, "text/plain", message);
}


const int buttonPin = D3;
const int ledPin = BUILTIN_LED;

  int val = 0;
  int state = 0;
  int old_val = 0;

const int relayPin = D7; // uncomment for kit D1 mini R1
const long interval = 100; // pause for x seconds

#include <Adafruit_NeoPixel.h>
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(7, D8, NEO_GRB + NEO_KHZ800);


void setup(void) {


pinMode(D1, OUTPUT);
Serial.begin(115200);

WiFi.mode(WIFI_AP);
WiFi.softAP(ssid, password);

Serial.println("");
// Wait for connection
server.on("/", handleRoot);
server.on("/on", engegar);
server.on("/off", apagar);
server.on("/change", canviar);
server.on("/inline", [](){
server.send(200, "text/plain", "this works as well");
});
server.onNotFound(handleNotFound);
server.begin();
Serial.println("HTTP server started");estat=0;
digitalWrite(D1, false);


  
pinMode(buttonPin, INPUT);
pinMode(ledPin, OUTPUT);
pinMode(relayPin, OUTPUT);

pixels.begin(); // This initializes the NeoPixel library.
pixels.setPixelColor(0, pixels.Color(0,0,0 ));
pixels.setPixelColor(1, pixels.Color(0,0,0 ));
pixels.setPixelColor(2, pixels.Color(0,0,0 ));
pixels.setPixelColor(3, pixels.Color(0,0,0 ));
pixels.setPixelColor(4, pixels.Color(0,0,0 ));
pixels.setPixelColor(5, pixels.Color(0,0,0 ));
pixels.setPixelColor(6, pixels.Color(0,0,0 ));
pixels.show();

}

void loop(void) {


server.handleClient();

  

if(estat==1){
  digitalWrite (relayPin, HIGH);
pixels.setPixelColor(0, pixels.Color(200,200,200 ));
pixels.setPixelColor(1, pixels.Color(200,200,200 ));
pixels.setPixelColor(2, pixels.Color(200,200,200 ));
pixels.setPixelColor(3, pixels.Color(200,200,200 ));
pixels.setPixelColor(4, pixels.Color(200,200,200 ));
pixels.setPixelColor(5, pixels.Color(200,200,200 ));
pixels.setPixelColor(6, pixels.Color(200,200,200 ));
pixels.setPixelColor(7, pixels.Color(200,200,200 ));// blanc.
pixels.show();
}
    
  else{
  digitalWrite (relayPin, LOW);
  pixels.setPixelColor(0, pixels.Color(0,0,0 ));
  pixels.setPixelColor(1, pixels.Color(0,0,0 ));
  pixels.setPixelColor(2, pixels.Color(0,0,0 ));
  pixels.setPixelColor(3, pixels.Color(0,0,0 ));
  pixels.setPixelColor(4, pixels.Color(0,0,0 ));
  pixels.setPixelColor(5, pixels.Color(0,0,0 ));
  pixels.setPixelColor(6, pixels.Color(0,0,0 ));
  pixels.setPixelColor(7, pixels.Color(0,0,0 ));// apagat.
pixels.show();
  delay (interval);
      }

val= digitalRead(buttonPin); 
if ((val == LOW))
  {
    canviar();
    delay (1000);
  }



}
