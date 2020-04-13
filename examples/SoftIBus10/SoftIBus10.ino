#include "SoftIBus.h"
#include "SoftwareSerial.h"
SoftwareSerial IBuspin(2, 3);
void setup() 
{ 
  IBuspin.begin(115200);
  Serial.begin(115200);
  SIBus.begin(IBuspin);
}

void loop() 
{
  IBus.loop();
  Serial.print(SIBus.readChannel(0), DEC);
  Serial.print("\t");
  Serial.print(SIBus.readChannel(1), DEC);
  Serial.print("\t");
  Serial.print(SIBus.readChannel(2), DEC);
  Serial.print("\t");
  Serial.print(SIBus.readChannel(3), DEC);
  Serial.print("\t");
  Serial.print(SIBus.readChannel(4), DEC);
  Serial.print("\t");
  Serial.print(SIBus.readChannel(5), DEC);
  Serial.print("\t");
  Serial.print(SIBus.readChannel(6), DEC);
  Serial.print("\t");
  Serial.print(SIBus.readChannel(7), DEC);
  Serial.print("\t");
  Serial.print(SIBus.readChannel(8), DEC);
  Serial.print("\t");
  Serial.println(SIBus.readChannel(9), DEC);

}
