// 2017/10/14 imo lab.
//https://garchiving.com/

#include <Wire.h>

int16_t axRaw, ayRaw, azRaw, gxRaw, gyRaw, gzRaw, temperature;

void setup() {
  Serial.begin(9600);
  Wire.setClock(400000);
  Wire.begin();
  
  Wire.beginTransmission(0x68);
  Wire.write(0x6B);
  Wire.write(0x00);
  Wire.endTransmission();
  Wire.beginTransmission(0x68);
  Wire.write(0x1C);
  Wire.write(0x10);
  Wire.endTransmission();
  Wire.beginTransmission(0x68);
  Wire.write(0x1B);
  Wire.write(0x08);
  Wire.endTransmission();
  Wire.beginTransmission(0x68);
  Wire.write(0x1A);
  Wire.write(0x05);
  Wire.endTransmission();
}

void loop() {
  Wire.beginTransmission(0x68);
  Wire.write(0x3B);
  Wire.endTransmission();
  Wire.requestFrom(0x68, 14);
  while (Wire.available() < 14);
  axRaw = Wire.read() << 8 | Wire.read();
  ayRaw = Wire.read() << 8 | Wire.read();
  azRaw = Wire.read() << 8 | Wire.read();
  temperature = Wire.read() << 8 | Wire.read();
  gxRaw = Wire.read() << 8 | Wire.read();　
  gyRaw = Wire.read() << 8 | Wire.read();
  gzRaw = Wire.read() << 8 | Wire.read();

  Serial.print(axRaw); Serial.print(",");
  Serial.print(ayRaw); Serial.print(",");
  Serial.print(azRaw); Serial.print(",");
  Serial.print(gxRaw); Serial.print(",");
  Serial.print(gyRaw); Serial.print(",");
  Serial.println(gzRaw);
}
