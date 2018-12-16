#include <Adafruit_NeoPixel.h>
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(7, D8, NEO_GRB + NEO_KHZ800);

void setup() {
  pixels.begin(); // This initializes the NeoPixel library.
}

void loop() {
  for (int i=0; i<=255;i++){
        pixels.setPixelColor(0, pixels.Color(i,i,i )); // blanc.
        pixels.setPixelColor(1, pixels.Color(i,0,0 )); // vermell.
        pixels.setPixelColor(2, pixels.Color(i,i,0 )); // groc.
        pixels.setPixelColor(3, pixels.Color(0,i,0 )); // verd.
        pixels.setPixelColor(4, pixels.Color(0,i,i )); // cyan.
        pixels.setPixelColor(5, pixels.Color(0,0,i )); // blau.
        pixels.setPixelColor(6, pixels.Color(i,0,i )); // magenta.
        pixels.show(); // This sends the updated pixel color to the hardware.
        delay(10); // Delay for a period of time (in milliseconds).    
  }
}

