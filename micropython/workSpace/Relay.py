from machine import Pin
from time import sleep
relay = Pin(13, Pin.OUT)
relay.off() # Switch off
sleep(2)
relay.on() # Switch on

