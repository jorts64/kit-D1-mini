#include <LOLIN_HP303B.h>
LOLIN_HP303B HP303BPressureSensor;

void setup()
{
  Serial.begin(9600);
  HP303BPressureSensor.begin();
  Serial.println("Barometric test");
}

void loop()
{
  int32_t temperature;
  int32_t pressure;
  int16_t oversampling = 7;
  int16_t ret;
  ret = HP303BPressureSensor.measureTempOnce(temperature, oversampling);
  Serial.print("T=");
  Serial.print(temperature);
  Serial.print(" °C, ");
  ret = HP303BPressureSensor.measurePressureOnce(pressure, oversampling);
  Serial.print("P=");
  Serial.print(pressure);
  Serial.println(" Pa");
  delay(500);
}
