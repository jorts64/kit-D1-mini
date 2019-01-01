#include <Wire.h>
#include <WEMOS_SHT3X.h>
#include <SFE_MicroOLED.h>  // Include the SFE_MicroOLED library
#define PIN_RESET 255  // Connect RST to pin 9
#define DC_JUMPER 0

MicroOLED oled(PIN_RESET, DC_JUMPER);    // I2C declaration
SHT3X sht30(0x45);

void setup() {
  oled.begin();    // Initialize the OLED
  oled.clear(ALL); // Clear the display's internal memory
  oled.display();  // Display what's in the buffer (splashscreen)
  delay(1000);     // Delay 1000 ms
  oled.clear(PAGE); // Clear the buffer.

  Serial.begin(115200);
}

void loop() {
  sht30.get();
  oled.clear(PAGE);
  oled.setFontType(1);
  oled.setCursor(0,0);
  oled.print("T:");
  oled.print(sht30.cTemp);
  oled.setCursor(0,24);
  oled.print("H:");
  oled.print(sht30.humidity);
  oled.display();
  delay(1000);

}
