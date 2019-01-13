from machine import Pin, PWM
import time
beeper = PWM(Pin(14), freq=440, duty=512)
time.sleep(0.5)
beeper.deinit()
