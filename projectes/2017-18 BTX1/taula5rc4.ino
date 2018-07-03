

/******************************************************************************
 * MicroOLED_Demo.ino
 * SFE_MicroOLED Library Demo
 * Jim Lindblom @ SparkFun Electronics
 * Original Creation Date: October 27, 2014
 * 
 * This sketch uses the MicroOLED library to draw a 3-D projected
 * cube, and rotate it along all three axes.
 * 
 * Development environment specifics:
 *  Arduino 1.0.5
 *  Arduino Pro 3.3V
 *  Micro OLED Breakout v1.0
 * 
 * This code is beerware; if you see me (or any other SparkFun employee) at the
 * local, and you've found our code helpful, please buy us a round!
 * 
 * Distributed as-is; no warranty is given.
 ******************************************************************************/
#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>
const char *ssid = "IPV-IOT-5";
const char *password = "INSPVIANA";
char *preu="2,99EUR";
ESP8266WebServer server(80);
#include <Wire.h>  // Include Wire if you're using I2C
#include <SFE_MicroOLED.h>  // Include the SFE_MicroOLED library


//-----------CODIGO HTML PAGINA DE CONFIGURACION---------------
String pagina = "<!DOCTYPE html>"
"<html>"
"<head>"
"<title>Canviar preus</title>"
"<meta charset='UTF-8'>"
"<meta name='viewport' content='width=device-width'/>"
"</head>"
"<body>"
"<form action='canviar' method='get'>"
"<input type='text' name='preunou' value='3,40EUR'>"
"<input type='submit' value='CANVIAR' /></br>"
"</form>"
"</body>"
"</html>";
//////////////////////////
// MicroOLED Definition //
//////////////////////////
#define PIN_RESET 255  // Connect RST to pin 9
#define DC_JUMPER 0

//////////////////////////////////
// MicroOLED Object Declaration //
//////////////////////////////////
MicroOLED oled(PIN_RESET, DC_JUMPER);    // I2C declaration


void canviar_preu() {
  String c;
  c = server.arg("preunou");
  c.toCharArray(preu, 7);
  DispPreu();
  paginacanvi();
}

void DispPreu(void) {
    oled.clear(PAGE);            // Clear the display
    oled.setCursor(7, 0);        // Set cursor to top-left
    oled.setFontType(1);         // Smallest font
    oled.print("Preu");
    oled.setCursor(0, 25); 
    oled.setFontType(1);         // 7-segment font
    oled.print(preu);  // Print a0 reading
    oled.display();
/*
    delay(1500);
    oled.clear(PAGE);            // Clear the display
    oled.setCursor(7, 0);        // Set cursor to top-left
    oled.setFontType(1);         // Smallest font
    oled.print("Price");
    oled.setCursor(0, 25); 
    oled.setFontType(1);         // 7-segment font
    oled.print("3,52$");  // Print a0 reading
    oled.display();
    delay(1500);
*/  
}

void paginacanvi() {
  server.send(200, "text/html", pagina); 
}

void setup()
{
  WiFi.softAP(ssid,password);
  oled.begin();    // Initialize the OLED
  oled.clear(ALL); // Clear the display's internal memory
  oled.display();  // Display what's in the buffer (splashscreen)
  delay(1000);     // Delay 1000 ms
  oled.clear(PAGE); // Clear the buffer.
  delay(1);
  server.on("/", paginacanvi); //esta es la pagina de configuracion
  server.on("/canviar", canviar_preu); //Graba en la eeprom la configuracion
  server.begin();
  DispPreu();
  

}

void loop()
{
    server.handleClient();
}



