from machine import Pin
button = Pin(0)
if button.value():
    print("The button is not pressed.")
else:
  print("The button is pressed.")




