#include <Wire.h>  // Include Wire if you're using I2C
#include <SFE_MicroOLED.h>  // Include the SFE_MicroOLED library
#define PIN_RESET 255  // Connect RST to pin 9
#define DC_JUMPER 0
MicroOLED oled(PIN_RESET, DC_JUMPER);    // I2C declaration

void setup()
{
  oled.begin();    // Initialize the OLED
  oled.clear(ALL); // Clear the display's internal memory
  oled.display();  // Display what's in the buffer (splashscreen)
  delay(1000);     // Delay 1000 ms
  oled.clear(PAGE); // Clear the buffer.
}

void loop()
{
  oled.clear(PAGE);
  oled.setFontType(1);
  oled.setCursor(0,0);
  oled.println("What's up, doc?");
  oled.display();
  delay(1500);
}

