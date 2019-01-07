from machine import Pin
import dht
sensor = dht.DHT11(Pin(2))
sensor.measure()
print(sensor.temperature())
print(sensor.humidity())

