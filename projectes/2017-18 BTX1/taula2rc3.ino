#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

const char* ssid = "IPV-IoT-2";
const char* password = "INSPVIANA";

ESP8266WebServer server(80);
int estat;

void handleRoot() {
  server.send(200, "text/html", "<h1>IoT Princep de Viana</h1> <br> <a href='/open'> Control acces portes institut </a>");
 
}
  
 void obrir() {
  digitalWrite(D1, true);
  estat=1;
  digitalWrite(D8, true);
  estat=1;
  digitalWrite(D4, false);
  estat=0;
  server.send(200, "text/plain", "OPEN");
  delay(7000);
  digitalWrite(D4, true);
  estat=1;
  digitalWrite(D1, false);
    estat=0;
  digitalWrite(D8, false);
  estat=0;
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

void setup(void){
  pinMode(D1, OUTPUT); //RELÉ
  pinMode(D4,OUTPUT); // RED
  pinMode(D8,OUTPUT); // GREEN
  Serial.begin(115200);
  WiFi.softAP(ssid, password);
  Serial.println("");

  server.on("/", handleRoot);
  server.on("/change", canviar);
  server.on("/open", obrir);
  server.on("/inline", [](){
    server.send(200, "text/plain", "this works as well");
    });
  server.onNotFound(handleNotFound);
  
  server.begin();
  Serial.println("HTTP server started");estat=0;
  digitalWrite(D1, false);
  }

void loop(void){
  server.handleClient();
}

