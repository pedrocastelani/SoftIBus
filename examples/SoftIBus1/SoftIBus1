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
  SIBus.loop();
  Serial.print(SIBus.readChannel(0), DEC);
}
