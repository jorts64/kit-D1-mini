import ssd1306
from machine import I2C, Pin
i2c = I2C(-1, Pin(5), Pin(4))
display = ssd1306.SSD1306_I2C(64, 48, i2c)
display.fill(0)
display.text("Hello", 0, 0)
display.text("world!", 0, 8)
display.pixel(20, 20, 1)
display.show()

