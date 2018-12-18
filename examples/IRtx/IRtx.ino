#include <IRremoteESP8266.h>
#include <IRsend.h>
IRsend irsend(D3);

void setup() {
  irsend.begin();
}

void loop() {
  irsend.sendSony(0xa90, 12, 2);
  delay(2000);
}
