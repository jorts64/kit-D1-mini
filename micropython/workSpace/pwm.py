from machine import Pin, PWM
import time
pwm2 = PWM(Pin(2), freq=500, duty=20)
while (True):
  for i in range (0,20):
    pwm2.duty(i)
    time.sleep_ms(50)
  for i in range (20,0,-1):
    pwm2.duty(i)
    time.sleep_ms(50)
