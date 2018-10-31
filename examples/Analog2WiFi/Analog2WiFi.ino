
#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>

const char *ssid = "ESPap";
const char *password = "robotica";

ESP8266WebServer server(80);

void handleRoot() {
  server.send(200, "text/html", "<html><head></head><body><a href='graf.svg'>Grafica</a><br><a href='rst'>Reset</a></body></html>");
}


const int buttonPin = D3;
const int ledPin = BUILTIN_LED;


void setup() {
  delay(1000);
  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, HIGH);
}

void loop() {
  if (digitalRead(buttonPin)==LOW) {
    prova();
  }
  else {
    if (analogRead(A0)>512) {
        digitalWrite(ledPin, LOW);
        delay(100);
        digitalWrite(ledPin, HIGH);
        delay(100);
    }
  }
  delay(1);
}


void prova() {
  digitalWrite(ledPin, LOW);
  WiFi.softAP(ssid, password);
  server.on("/", handleRoot);
  server.on("/graf.svg", grafica);
  server.on("/rst", reinicia);
  server.begin();
  while (true) {
    server.handleClient();
  }
}

void grafica() {
  String out = "";
  char temp[1000];
  out += "<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\" width=\"400\" height=\"150\">\n";
  out += "<rect width=\"400\" height=\"150\" fill=\"rgb(250, 230, 210)\" stroke-width=\"1\" stroke=\"rgb(0, 0, 0)\" />\n";
  out += "<g stroke=\"black\">\n";
  int y = analogRead(A0)/10;
  delay(5);
  for (int x = 1; x < 399; x++) {
    int y2 = analogRead(A0)/10;
    delay(5);
    sprintf(temp, "<line x1=\"%d\" y1=\"%d\" x2=\"%d\" y2=\"%d\" stroke-width=\"1\" />\n", x, 140 - y, x + 10, 140 - y2);
    out += temp;
    y = y2;
  }
  out += "</g>\n</svg>\n";

  server.send ( 200, "image/svg+xml", out);
}

void reinicia() {
  ESP.restart();
}

