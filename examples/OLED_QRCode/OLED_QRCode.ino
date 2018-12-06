// uses QRcode library from arduino library manager
// generates QRcode version 1 (otger versions need display with more pixels to make double points

#include "qrcode.h"

#include <Wire.h>  // Include Wire if you're using I2C
#include <SFE_MicroOLED.h>  // Include the SFE_MicroOLED library
#define PIN_RESET 255  // Connect RST to pin 9
#define DC_JUMPER 0
MicroOLED oled(PIN_RESET, DC_JUMPER);    // I2C declaration

void setup() {
    Serial.begin(115200);

  oled.begin();    // Initialize the OLED
  oled.clear(ALL); // Clear the display's internal memory
  oled.display();  // Display what's in the buffer (splashscreen)
  delay(1000);     // Delay 1000 ms
  oled.clear(PAGE); // Clear the buffer.
  
  QRCode qrcode;
  uint8_t qrcodeData[qrcode_getBufferSize(3)];
  qrcode_initText(&qrcode, qrcodeData, 1, 0, "HELLO WORLD");

  for (uint8_t y = 0; y < qrcode.size; y++) {
    for (uint8_t x = 0; x < qrcode.size; x++) {
      if (qrcode_getModule(&qrcode, x, y)){
        oled.pixel(2*x+3,2*y+3);
        oled.pixel(2*x+4,2*y+3);
        oled.pixel(2*x+3,2*y+4);
        oled.pixel(2*x+4,2*y+4);
        }
      }
    }
  oled.display();
  oled.invert(true);

}

void loop() {
  delay(1000);

}
