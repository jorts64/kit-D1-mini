import machine
import onewire
import ds18x20
import time

dat = machine.Pin(4)
ds = ds18x20.DS18X20(onewire.OneWire(dat))
roms = ds.scan()
while True:
  ds.convert_temp()
  temp = ds.read_temp(roms[0])
  print(temp)
  time.sleep_ms(1000)


