#include <MsTimer2.h>
#include <Wire.h>

#define CTRL_PERIOD 200 // 制御周期[ms]

volatile int temp, counter = 0;
volatile double angleofst = 0;
volatile double curangv = 0;
volatile double preangv = 0;
volatile double pregang = 0;
volatile double curgang = 0;

int16_t axRaw, ayRaw, azRaw, gxRaw, gyRaw, gzRaw, temperature;
float preangg, predps;

void test()
{
//  double tmpangv;
//  
////  if (!(angleofst))
////  {
////    angleofst = (counter * 360.0 / 2000.0) - ((analogRead(0) * 5.0 / 1024.0 - 1.65) * 90.0 / 0.66);
////  }
////  Serial.print("E: ");
////  Serial.print(counter * 360.0 / 2000.0 - angleofst);
////  temp = counter;
//  
//
//  Serial.print("\tA: ");
//  Serial.print((analogRead(0) * 5.0 / 1024.0 - 1.65) * 90.0 / 0.66);
//
//
//  tmpangv = ((double)analogRead(1) * 5 / 1024 - 1.46) / 0.00067;
//  
//  if (abs(tmpangv - preangv) > 5)
//  {
////    curangv = tmpangv;
////    curgang = pregang + ((preangv + curangv) * (CTRL_PERIOD / 1000) / 2);
//  }
//  curangv = ((double)analogRead(1) * 5 / 1024 - 1.46) / 0.00067;
//  curgang = pregang + ((preangv + curangv) * (CTRL_PERIOD / 1000) / 2);
//  
//  Serial.print("\tG: "); 
////  Serial.println((double)analogRead(1)); // これは数値が出る！！
////  Serial.println(curgang);
//  Serial.println(curangv);
//  
//  pregang = curgang;
//  preangv = curangv;


  float tgtaraw, tgtzraw, tgtgraw, tgta, tgtz, curangg, curanga;
  
  axRaw = Wire.read() << 8 | Wire.read();
  ayRaw = Wire.read() << 8 | Wire.read();
  azRaw = Wire.read() << 8 | Wire.read();
  temperature = Wire.read() << 8 | Wire.read();
  gxRaw = Wire.read() << 8 | Wire.read();
  gyRaw = Wire.read() << 8 | Wire.read();
  gzRaw = Wire.read() << 8 | Wire.read();

//  Serial.print(axRaw); Serial.print(",");
//  Serial.print(ayRaw); Serial.print(",");
//  Serial.print(azRaw); Serial.print(",");
//  Serial.print(gxRaw); Serial.print(",");
//  Serial.print(gyRaw); Serial.print(",");
//  Serial.println(gzRaw);

//  /tgtaraw = (float)azRaw / 4096 * 9.8;

  
  tgtaraw = (float)axRaw / 4096;
  tgtzraw = (float)azRaw / 4096;
  tgtgraw = gyRaw / 65.5;

  if (tgtaraw > 1) {
    tgta = 1;
  }
  else if (tgtaraw < -1) {
    tgta = -1;
  }
  
  if (tgtzraw > 1) {
    tgtz = 1;
  }
  else if (tgtzraw < -1) {
    tgtz = -1;
  }
  

  curanga = atan2(tgtaraw, tgtzraw) * (180.0 / PI);
//  curanga = asin(tgta/raw) * (180.0 / PI);

  curangv = preangg + ((tgtgraw + predps) * (CTRL_PERIOD / 1000.0) / 2.0);
//  curangv = ((CTRL_PERIOD / 1000.0/) / 2.0);

  Serial.print("Accel: ");
//  Serial.print(tgtaraw);
  Serial.print(curanga);

  Serial.print("\t\tGyro: ");
//  Serial.println(tgtgraw);
  Serial.print(curangv);

//  Serial.print(tgtgraw);
//  Serial.print('\t');
//  Serial.print(predps);
//  Serial.print('\t');
//  Serial.print(preangg);
  
  
  Serial.print("\n");

  preangg = curangv;
  predps = tgtgraw;
}


void setup()
{
  Serial.begin (9600);
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

  MsTimer2::set(CTRL_PERIOD, test);
  MsTimer2::start();
}

void loop()
{
  Wire.beginTransmission(0x68);
  Wire.write(0x3B);
  Wire.endTransmission();
  Wire.requestFrom(0x68, 14);
  while (Wire.available() < 14);
}
