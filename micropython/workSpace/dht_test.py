import time
from shields import dht12
from machine import I2C, Pin
sensor = dht12.DHT12()

while True:
	sensor.measure()
	print(sensor.temperature())
	print(sensor.humidity())
	time.sleep_ms(4000)


