import machine
from machine import I2C, Pin
from drivers import ds1307

class RTC_Shield:

    def __init__(self):
        i2c = I2C(sda=Pin(4), scl=Pin(5))
        self.rtc = ds1307.DS1307(i2c)
        self.day_names = ('Sunday', 'Monday', 'Tuesday', 'Wednesday', 'Thursday', 'Friday', 'Saturday')
        self.day_abbreviations = ('Sun', 'Mon', 'Tue', 'Wed', 'Thu', 'Fri', 'Sat')

    def datetime(self):
        return self.rtc.datetime()

    def year(self):
        return self.rtc.datetime().year

    def month(self):
        return self.rtc.datetime().month

    def day(self):
        return self.rtc.datetime().day

    def weekday(self):
        return self.rtc.datetime().weekday

    def hour(self):
        return self.rtc.datetime().hour

    def minute(self):
        return self.rtc.datetime().minute

    def second(self):
        return self.rtc.datetime().second

