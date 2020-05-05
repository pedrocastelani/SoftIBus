#include "SoftIBus.h"//SoftIBus library
SoftwareSerial IBuspin(2, 3);//"serial" port on which we will be running the IBus connection. Since to read values we only need the Rx, just connect pin 2 and leave 3 open
void setup() 
{ 
  IBuspin.begin(115200);//the softserial port has to begin at this baud prior to starting it as the IBus port
  Serial.begin(115200);//hardserial for debigging
  IBus.begin(IBuspin);//start the IBus object
}

void loop() 
{
  IBus.loop();
  Serial.print(IBus.readChannel(0));//get channel 1 (real channel-1= IBus channel) values in DEC format, from 1000 to 2000 if limits set to 100% on transmitter (endpoints are 900 and 2100)
  Serial.print("\t");//separate the channel values for easy view. Makes the serial plotter (if used) identify each value as another variable
  Serial.print(IBus.readChannel(1));
  Serial.print("\t");
  Serial.print(IBus.readChannel(2));
  Serial.print("\t");
  Serial.print(IBus.readChannel(3));
  Serial.print("\t");
  Serial.print(IBus.readChannel(4));
  Serial.print("\t");
  Serial.print(IBus.readChannel(5));
  Serial.print("\t");
  Serial.print(IBus.readChannel(6));
  Serial.print("\t");
  Serial.print(IBus.readChannel(7));
  Serial.print("\t");
  Serial.print(IBus.readChannel(8));
  Serial.print("\t");
  Serial.println(IBus.readChannel(9));//add an "enter" after this value to start a new line next loop

}
