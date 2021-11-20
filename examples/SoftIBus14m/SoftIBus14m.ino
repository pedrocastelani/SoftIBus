#include "SoftIBus.h"             // SoftIBus library
SoftwareSerial IBuspin(14, 15);   // "serial" port on which we will be running the IBus connection. 
                                  // Since to read values we only need the Rx, just connect pin D14 and leave D15 open

// *** ВАЖНО!!! *** ЧИТАТЬ ВНИМАТЕЛЬНО!!! ***
// Так как библиоткека iBUSTelemetry.h использует прерывание PCINT0 во избежание конфликта
// в библиотеке SoftwareSerial (CustomSoftwareSerial.h) требуется замаркировать блок обработки прерывания PCINT0
// строки 313 - 320 (для CustomSoftwareSerial), то-есть для порта можно использовать пины  A0 .. A5 или D0 .. D7
// Информация актуальна при совместном использовании библиотек SoftIBus.h и iBUSTelemetry.h
/*
    D8 .. D13 - генерируют запрос прерывания PCINT0
    A0 .. A5  - генерируют запрос прерывания PCINT1
    D0 .. D7  - генерируют запрос прерывания PCINT2
*/
int ch = 14;                      // число каналов радиоаппаратуры RC

void setup()
{
  IBuspin.begin(115200);//the softserial port has to begin at this baud prior to starting it as the IBus port
  Serial.begin(115200);//hardserial for debigging
  IBus.begin(IBuspin);//start the IBus object
}

void loop()
{
  static uint16_t inibus;
  IBus.loop();
  for (int i = 0; i < ch; i++)
  {
    inibus = IBus.readChannel(i);
    if (i < ch - 1)
    {
      Serial.print(inibus);
      Serial.print("\t");
    } else {
      Serial.println(inibus);
    }
  }
}
