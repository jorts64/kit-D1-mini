import machine
import onewire
import ds18x20

class DS18B20_Shield:

    def __init__(self,pin):
        dat = machine.Pin(pin)
        self.ds = ds18x20.DS18X20(onewire.OneWire(dat))
        self.roms = self.ds.scan()

    def celsius(self):
        self.ds.convert_temp()
        return self.ds.read_temp(self.roms[0])

    def farenheit(self):
        return (self.celsius() * 1.8) + 32.0

import time


# create object to retrieve the temp
ds_shield = DS18B20_Shield(12)

# infinite loop
while True:

    temp = ds_shield.celsius()

    #offset
    temp -= 10.0

    print(temp)

    # wait for the next check
    time.sleep_ms(2000)
