#include <Wire.h>  
#include <SFE_MicroOLED.h>  
#include <FS.h>

#define PIN_RESET 255  //
#define DC_JUMPER 0  // I2C Addres: 0 - 0x3C, 1 - 0x3D
MicroOLED oled(PIN_RESET, DC_JUMPER);  // I2C Example
File f;
uint8_t pixels[16*24];

void setup()
{
  SPIFFS.begin();
  oled.begin();
  oled.clear(ALL); 
  oled.display();   
  delay(1000);
  oled.clear(PAGE);
  loadbitmap();
  oled.drawBitmap(pixels);
  oled.display();
}

void loop() {
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

void loadbitmap(){
  uint8_t sa[16];
  String txt;  int i,j,k;
  f = SPIFFS.open("/bitmap.dat","r");
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

