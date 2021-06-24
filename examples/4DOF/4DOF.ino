#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <Servo.h>

const char *ssid = "NOMDELAXARXA";
const char *password = "CONTRASENYA";

ESP8266WebServer server ( 80 );

Servo myservo1;
Servo myservo2;
Servo myservo3;
Servo myservo4;

int pos1;
int pos2;
int pos3;
int pos4;

String mensaje = "";

//-----------CODIGO HTML PAGINA DE CONFIGURACION---------------

void paginacanvi() {
  String pagina = "<!DOCTYPE html>"
  "<html>"
  "<head>"
  "<title>4DOF</title>"
  "<meta charset='UTF-8'>"
  "<meta name='viewport' content='width=device-width'/>"
  "</head>"
  "<body>"
  "<table style='width:100%'><form action='canviar' method='get'>"
  "<tr><td>Arpa:</td><td><input type='range' name='r' min='0' max='80' value='"+String(pos1)+"'></td></tr>"
  "<tr><td>Alçada:</td><td><input type='range' name='g' min='100' max='165' value='"+String(pos2)+"'></td></tr>"
  "<tr><td>Radi:</td><td><input type='range' name='b' min='0' max='100' value='"+String(pos3)+"'></td></tr>"
  "<tr><td>Azimut:</td><td><input type='range' name='t' min='0' max='180' value='"+String(pos4)+"'></td></tr>"
  "<tr><td></td><td><input type='submit' value='CANVIAR' /></td></tr>"
  "</form></table>"
  "</body>"
  "</html>";
  server.send(200, "text/html", pagina); 
}

void canviar_colors() {
  pos1 = server.arg("r").toInt();
  pos2 = server.arg("g").toInt();
  pos3 = server.arg("b").toInt();
  pos4 = server.arg("t").toInt();
  myservo1.write(pos1);
  myservo2.write(pos2);
  myservo3.write(pos3);
  myservo4.write(pos4);
  paginacanvi();
}

void setup() {
  myservo1.attach(D5);
  myservo2.attach(D6);
  myservo3.attach(D7);
  myservo4.attach(D8);
  pos1 =40;
  pos2 =100;
  pos3 = 0;
  pos4 = 78;
  myservo1.write(pos1);
  myservo2.write(pos2);
  myservo3.write(pos3);
  myservo4.write(pos4);
  
  WiFi.begin ( ssid, password );
  server.on("/", paginacanvi); 
  server.on("/canviar", canviar_colors); 
  server.begin();

}

void loop() {
  server.handleClient();
}
