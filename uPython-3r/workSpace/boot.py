

# This file is executed on every boot (including wake-boot from deepsleep)

#import esp

#esp.osdebug(None)

import gc

#import webrepl

#webrepl.start()

gc.collect()

import time
import ssd1306
from machine import I2C, Pin, PWM
import dht12
import neopixel

i2c = I2C(-1, Pin(5), Pin(4))
display = ssd1306.SSD1306_I2C(64, 48, i2c)

sensor = dht12.DHT12()

button = Pin(0)

def polsador():
   return not(button.value())

freqs = {'do' : 523, 're' : 587, 'mi' : 669, 'fa' : 698, 'sol' : 784, 'la' : 880,  'si' : 988} 

def toca(nota):
   beeper = PWM(Pin(14), freq=freqs[nota], duty=512)
   time.sleep(0.5)
   beeper.deinit()

led = neopixel.NeoPixel(Pin(15, Pin.OUT), 7)

color = {'vermell' : (0x20, 0x00, 0x00) , 'groc' : (0x20, 0x20, 0x00),
  'verd' : (0x00, 0x20, 0x00), 'cyan' : (0x00, 0x20, 0x20),
  'blau' : (0x00, 0x00, 0x20),  'magenta' : (0x20, 0x00, 0x20),
  'blanc' : (0x20, 0x20, 0x20), 'apagat' : (0x00, 0x00, 0x00)}

