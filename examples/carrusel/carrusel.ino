#include <Wire.h>  
#include <SFE_MicroOLED.h>  
#include <FS.h>
#include "FSManager.h"
extern ESP8266WebServer server;

#define PIN_RESET 255  //
#define DC_JUMPER 0  // I2C Addres: 0 - 0x3C, 1 - 0x3D
MicroOLED oled(PIN_RESET, DC_JUMPER);  // I2C Example
File f;
uint8_t pixels[16*24];


void loadbitmap(String fitxer);

void setup() {
  SPIFFS.begin();
  initHelper(); //inclou connexió Wifi i server
                // Aquí podem afegir altres funcions server.on()
  server.begin();

  oled.begin();
  oled.clear(ALL); 
  oled.display();   
  delay(1000);
}

void loop() {
  Dir dir = SPIFFS.openDir("/");
  while (dir.next()) {
    String fileName = dir.fileName();
    if(fileName.endsWith(".dat")){
      oled.clear(PAGE);
      loadbitmap(fileName);
      oled.drawBitmap(pixels);
      oled.display();
      espera(1000);      
    }
  }
  
}

String getLine() {
  String S = "" ;
  char c = f.read(); 
  while ( c != '\n') {     
    S = S + c ;
    c = f.read();
    }
  return(S) ;
}

int convertFromHex(int ascii){ 
  if(ascii > 0x39) ascii -= 7; // adjust for hex letters upper or lower case
  return(ascii & 0xf);
}

void loadbitmap(String fitxer){
  uint8_t sa[16];
  String txt;  int i,j,k;
  f = SPIFFS.open(fitxer,"r");
    for (i=0;i<24;i++){
      txt=getLine();
      k=0;
      for (j=0; j<16; j++) { 
        while (txt.charAt(k) != 'x') k++;  
        sa[j] = convertFromHex(txt[k+1])*16;
        sa[j] += convertFromHex(txt[k+2]); 
        k++;
      }
      for (j=0;j<16;j++) {
          pixels[i*16+j]=sa[j];
      }
    }
  f.close();
}



