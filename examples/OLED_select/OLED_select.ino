#include <Wire.h>  // Include Wire if you're using I2C
#include <SFE_MicroOLED.h>  // Include the SFE_MicroOLED library
#define PIN_RESET 255  // Connect RST to pin 9
#define DC_JUMPER 0
MicroOLED oled(PIN_RESET, DC_JUMPER);    // I2C declaration 

int PosMax = 3;
String noms[] = {"A1","B2","C3","D4"};
 
int pinA = D3;  
int pinB = D4;  
int Pos = 0; 

void printTitle(String title, int font);

void setup() { 
  pinMode (pinA,INPUT);
  pinMode (pinB,INPUT);

  oled.begin();    // Initialize the OLED
  oled.clear(ALL); // Clear the display's internal memory
  oled.display();  // Display what's in the buffer (splashscreen)
  delay(1000);     // Delay 1000 ms
  oled.clear(PAGE); // Clear the buffer.
  printTitle(noms[Pos], 1);

  Serial.begin (9600);
} 

void loop() {
  
   if (digitalRead(pinA)== LOW){ 
    Pos++;
    if (Pos > PosMax){
      Pos = 0;
      }
    Serial.print ("Rotated: ");
    Serial.print("Encoder Position: ");
    Serial.println(Pos);
    printTitle(noms[Pos], 1);
    delay(300);       
    }
    
   if (digitalRead(pinB)==LOW) {
    oled.invert(true);
    delay(1000);
    oled.invert(false);
    Serial.println("premut");
   }
   
} 

void printTitle(String title, int font) {
  int middleX = oled.getLCDWidth() / 2;
  int middleY = oled.getLCDHeight() / 2;
  
  oled.clear(PAGE);
  oled.setFontType(font);
  // Try to set the cursor in the middle of the screen
  oled.setCursor(middleX - (oled.getFontWidth() * (title.length()/2)),
                 middleY - (oled.getFontWidth() / 2));
  // Print the title:
  oled.print(title);
  oled.display();
}
 
