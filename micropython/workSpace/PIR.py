from machine import Pin
from time import sleep
button = Pin(12,Pin.IN)
while (True):
 if button.value():
    print("Persona detectada.")
 else:
    print("No es detecta.")
 sleep(3)
  






