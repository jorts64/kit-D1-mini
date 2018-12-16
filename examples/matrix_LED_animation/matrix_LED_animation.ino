#include <WEMOS_Matrix_LED.h>

MLED mled(5); //set intensity=5

const uint64_t IMAGES[] = {
  0x00080cfefffe0c08,
  0x0004067f7f7f0604,
  0x0002033f3f3f0302,
  0x0001011f1f1f0101,
  0x0000000f0f0f0000,
  0x0000000707070000,
  0x0000000303030000,
  0x0000000101010000,
  0x0000000000000000
};
const int IMAGES_LEN = sizeof(IMAGES)/8;


void setup() {
}

void displayImage(uint64_t image) {
  for (int i = 0; i < 8; i++) {
    byte row = (image >> i * 8) & 0xFF;
    for (int j = 0; j < 8; j++) {
      mled.dot(j, 7-i, bitRead(row, j));
    }
  }
  mled.display();
}

int i = 0;

void loop() {
  displayImage(IMAGES[i]);
  if (++i >= IMAGES_LEN ) {
    i = 0;
  }
  delay(100);
}

