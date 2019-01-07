from machine import Pin

class MatrixLED_Shield:

    def __init__(self, dataPin=13, clockPin=14): # D7(data), D5(clock)
        self.dataPin  = Pin(dataPin, Pin.OUT, value = 1)
        self.clockPin = Pin(clockPin, Pin.OUT, value = 1)
        self.intensity = 4
        self.buf = [0,0,0,0,0,0,0,0]

    def send(self, data):
        for i in range(8):
            self.clockPin.off()
            self.dataPin.value((data >> i) & 1)
            self.clockPin.on()

    def sendCommand(self, cmd):
        self.dataPin.off()
        self.send(cmd)
        self.dataPin.on()

    def sendData(self, address, data):
        self.sendCommand(0x44)
        self.dataPin.off()
        self.send(0xC0 | address)
        self.send(data)
        self.dataPin.on()

    def clear(self):
        for i in range(8):
            self.buf[i]=0

    def pixel(self, x, y, color=1):
        if color == 1:
            self.buf[y & 7] |= 1 << (x & 7)
        else:
            self.buf[y & 7] &= ~ (1 << (x & 7))

    def show(self):
        for i in range(8):
            self.sendData(i, self.buf[i])
            self.dataPin.off()
            self.clockPin.off()
            self.clockPin.on()
            self.dataPin.on()
        self.sendCommand(0x88|(self.intensity))