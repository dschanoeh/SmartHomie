#include "hardware.h"
#ifdef LIGHT_INTENSITY_NODE

#include <Wire.h>
#include "LiFuelGauge.h"
#include "light_intensity.h"
#include <math.h>

HomieNode lightIntensityNode("light", "intensity");
byte buff[2];
int BH1750address = 0x23; //setting i2c address

void lightIntensitySetup() {
  Wire.begin();
  lightIntensityNode.setProperty("unit").send("lx");

}

void postlightIntensityUpdate() {
  uint16_t val=0;
  BH1750_Init(BH1750address);
  delay(200);
  if(2==BH1750_Read(BH1750address))
  {
    val=((buff[0]<<8)|buff[1])/1.2;
    lightIntensityNode.setProperty("intensity").send(String(val));
  }
}

void BH1750_Init(int address)
{
   Wire.beginTransmission(address);
   Wire.write(0x10); //1lx reolution 120ms
   Wire.endTransmission();
}

int BH1750_Read(int address)
{
   int i=0;
   Wire.beginTransmission(address);
   Wire.requestFrom(address, 2);
   while(Wire.available())
   {
      buff[i] = Wire.read();  // receive one byte
      i++;
   }
   Wire.endTransmission();
   return i;
}

#endif
