import time
import machine

adc = machine.ADC(0)

servo = machine.PWM(machine.Pin(12), freq=50)

ain_min = 0
ain_max = 1024

duty_min = 40
duty_max = 115

while True:
    val = adc.read()
    print(val)
    d = int((val - ain_min) * (duty_max - duty_min) / (ain_max - ain_min) + duty_min)
    #print(d)
    servo.duty(d)
    time.sleep_ms(400)