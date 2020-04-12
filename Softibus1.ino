#include "SoftIBus.h"
#include "SoftwareSerial.h"
SoftwareSerial IBuspin(2, 3);
void setup() 
{ 
  IBuspin.begin(115200);
  Serial.begin(115200);
  IBus.begin(IBuspin);
}

void loop() 
{
  IBus.loop();
  Serial.print(IBus.readChannel(0), DEC);
}
