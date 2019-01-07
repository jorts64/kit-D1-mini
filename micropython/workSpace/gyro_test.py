from machine import Pin,I2C
from drivers import mpu6050

i2c = I2C(sda=Pin(5), scl=Pin(4))

x = mpu6050.accel(i2c)
x.val_test()
