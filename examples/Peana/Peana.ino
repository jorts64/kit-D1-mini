//Install [Adafruit_NeoPixel_Library](https://github.com/adafruit/Adafruit_NeoPixel) first.

#include <Adafruit_NeoPixel.h>

#define PIN            D2

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(1, PIN, NEO_BRG + NEO_KHZ800);

// colors RGB values from Viquipedia: https://ca.wikipedia.org/wiki/Colors_HTML

uint32_t color[]={
  0xFFC0CB, //   0 Pink
  0xFFB6C1, //   1 LightPink
  0xFF69B4, //   2 HotPink
  0xFF1493, //   3 DeepPink
  0xDB7093, //   4 PaleVioletRed
  0xC71585, //   5 MediumVioletRed
  0xFFA07A, //   6 LightSalmon
  0xFA8072, //   7 Salmon
  0xE9967A, //   8 DarkSalmon
  0xF08080, //   9 LightCoral
  0xCD5C5C, //  10 IndianRed
  0xDC143C, //  11 Crimson
  0xB22222, //  12 FireBrick
  0x8B0000, //  13 DarkRed
  0xFF0000, //  14 Red
  0xFF4500, //  15 OrangeRed
  0xFF6347, //  16 Tomato
  0xFF7F50, //  17 Coral
  0xFF8C00, //  18 DarkOrange
  0xFFA500, //  19 Orange
  0xFFD700, //  20 Gold
  0xFFFF00, //  21 Yellow
  0xFFFFE0, //  22 LightYellow
  0xFFFACD, //  23 LemonChiffon
  0xFAFAD2, //  24 LightGoldenrodYellow
  0xFFEFD5, //  25 PapayaWhip
  0xFFE4B5, //  26 Moccasin
  0xFFDAB9, //  27 PeachPuff
  0xEEE8AA, //  28 PaleGoldenrod
  0xF0E68C, //  29 Khaki
  0xBDB76B, //  30 DarkKhaki
  0xFFF8DC, //  31 Cornsilk
  0xFFEBCD, //  32 BlanchedAlmond
  0xFFE4C4, //  33 Bisque
  0xFFDEAD, //  34 NavajoWhite
  0xF5DEB3, //  35 Wheat
  0xDEB887, //  36 BurlyWood
  0xD2B48C, //  37 Tan
  0xBC8F8F, //  38 RosyBrown
  0xF4A460, //  39 SandyBrown
  0xDAA520, //  40 Goldenrod
  0xB8860B, //  41 DarkGoldenrod
  0xCD853F, //  42 Peru
  0xD2691E, //  43 Chocolate
  0x8B4513, //  44 SaddleBrown
  0xA0522D, //  45 Sienna
  0xA52A2A, //  46 Brown
  0x800000, //  47 Maroon
  0x556B2F, //  48 DarkOliveGreen
  0x808000, //  49 Olive
  0x6B8E23, //  50 OliveDrab
  0x9ACD32, //  51 YellowGreen
  0x32CD32, //  52 LimeGreen
  0x00FF00, //  53 Lime
  0x7CFC00, //  54 LawnGreen
  0x7FFF00, //  55 Chartreuse
  0xADFF2F, //  56 GreenYellow
  0x00FF7F, //  57 SpringGreen
  0x00FA9A, //  58 MediumSpringGreen
  0x90EE90, //  59 LightGreen
  0x98FB98, //  60 PaleGreen
  0x8FBC8F, //  61 DarkSeaGreen
  0x3CB371, //  62 MediumSeaGreen
  0x2E8B57, //  63 SeaGreen
  0x228B22, //  64 ForestGreen
  0x008000, //  65 Green
  0x006400, //  66 DarkGreen
  0x66CDAA, //  67 MediumAquamarine
  0x00FFFF, //  68 Aqua
  0x00FFFF, //  69 Cyan
  0xE0FFFF, //  70 LightCyan
  0xAFEEEE, //  71 PaleTurquoise
  0x7FFFD4, //  72 Aquamarine
  0x40E0D0, //  73 Turquoise
  0x48D1CC, //  74 MediumTurquoise
  0x00CED1, //  75 DarkTurquoise
  0x20B2AA, //  76 LightSeaGreen
  0x5F9EA0, //  77 CadetBlue
  0x008B8B, //  78 DarkCyan
  0x008080, //  79 Teal
  0xB0C4DE, //  80 LightSteelBlue
  0xB0E0E6, //  81 PowderBlue
  0xADD8E6, //  82 LightBlue
  0x87CEEB, //  83 SkyBlue
  0x87CEFA, //  84 LightSkyBlue
  0x00BFFF, //  85 DeepSkyBlue
  0x1E90FF, //  86 DodgerBlue
  0x6495ED, //  87 CornflowerBlue
  0x4682B4, //  88 SteelBlue
  0x4169E1, //  89 RoyalBlue
  0x0000FF, //  90 Blue
  0x0000CD, //  91 MediumBlue
  0x00008B, //  92 DarkBlue
  0x000080, //  93 Navy
  0x191970, //  94 MidnightBlue
  0xE6E6FA, //  95 Lavender
  0xD8BFD8, //  96 Thistle
  0xDDA0DD, //  97 Plum
  0xEE82EE, //  98 Violet
  0xDA70D6, //  99 Orchid
  0xFF00FF, // 100 Magenta
  0xBA55D3, // 101 MediumOrchid
  0x9370DB, // 102 MediumPurple
  0x8A2BE2, // 103 BlueViolet
  0x9400D3, // 104 DarkViolet
  0x9932CC, // 105 DarkOrchid
  0x8B008B, // 106 DarkMagenta
  0x800080, // 107 Purple
  0x4B0082, // 108 Indigo
  0x483D8B, // 109 DarkSlateBlue
  0x6A5ACD, // 110 SlateBlue
  0x7B68EE, // 111 MediumSlateBlue
  0xFFFFFF, // 112 White
  0xF5F5DC, // 113 Beige
  0xFAEBD7, // 114 AntiqueWhite
  0xFFE4E1, // 115 MistyRose
  0x808080, // 116 Gray
  0x708090  // 117 SlateGray
};

int indexcolor;
uint32_t oldcolor, newcolor;

void setup() {
  pixels.begin(); // This initializes the NeoPixel library.
  indexcolor = random(118);
  oldcolor=color[indexcolor]; 
  pixels.setPixelColor(0, oldcolor); 
  pixels.show(); // This sends the updated pixel color to the hardware.
  delay(400); // Delay for a period of time (in milliseconds).
}

void loop() {

  indexcolor = random(118);
  newcolor=color[indexcolor]; 
  while (oldcolor != newcolor) {
    uint32_t oldR = oldcolor & 0xFF0000;
    uint32_t newR = newcolor & 0xFF0000;
    uint32_t oldG = oldcolor & 0x00FF00;
    uint32_t newG = newcolor & 0x00FF00;
    uint32_t oldB = oldcolor & 0x0000FF;
    uint32_t newB = newcolor & 0x0000FF;
    if (newR > oldR) {
      oldcolor += 0x10000;
    }
    if (newR < oldR) {
      oldcolor -= 0x10000;
    }
    if (newG > oldG) {
      oldcolor += 0x100;
    }
    if (newG < oldG) {
      oldcolor -= 0x100;
    }
    if (newB > oldB) {
      oldcolor += 0x1;
    }
    if (newB < oldB) {
      oldcolor -= 0x1;
    }
   
    pixels.setPixelColor(0, oldcolor); 
    pixels.show(); // This sends the updated pixel color to the hardware.
    delay(10); // Delay for a period of time (in milliseconds).       
  }
  pixels.setPixelColor(0, oldcolor); 
  pixels.show(); // This sends the updated pixel color to the hardware.
  delay(1000); // Delay for a period of time (in milliseconds).      
}

