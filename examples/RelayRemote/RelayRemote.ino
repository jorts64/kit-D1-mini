#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

const char* ssid = "la teva xarxa aqui";
const char* password = "contrasenya dexarxa aqui";

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

void setup(void){
  pinMode(D1, OUTPUT);
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.println("");
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

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
  }

void loop(void){
  server.handleClient();
  }

