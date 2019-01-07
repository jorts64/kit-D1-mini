import matrixled_shield
from time import sleep
matrix = matrixled_shield.MatrixLED_Shield()
matrix.clear()
for x in range(0, 8):
  for y in range(0, 8):
    matrix.pixel(x, y, 1)
    matrix.show()
    sleep(0.1)
    matrix.pixel(x, y, 0)
    matrix.show()
