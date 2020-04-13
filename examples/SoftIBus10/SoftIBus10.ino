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
  Serial.print("\t");
  Serial.print(IBus.readChannel(1), DEC);
  Serial.print("\t");
  Serial.print(IBus.readChannel(2), DEC);
  Serial.print("\t");
  Serial.print(IBus.readChannel(3), DEC);
  Serial.print("\t");
  Serial.print(IBus.readChannel(4), DEC);
  Serial.print("\t");
  Serial.print(IBus.readChannel(5), DEC);
  Serial.print("\t");
  Serial.print(IBus.readChannel(6), DEC);
  Serial.print("\t");
  Serial.print(IBus.readChannel(7), DEC);
  Serial.print("\t");
  Serial.print(IBus.readChannel(8), DEC);
  Serial.print("\t");
  Serial.println(IBus.readChannel(9), DEC);

}
