from machine import Pin
import neopixel
pixels = neopixel.NeoPixel(Pin(4, Pin.OUT), 1)
pixels[0] = (0xff, 0x00, 0x22)
pixels.write()

