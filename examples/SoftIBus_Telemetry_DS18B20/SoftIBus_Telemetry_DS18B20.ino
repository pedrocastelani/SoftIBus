// #define DEBUG // В рабочей версии замаркировать определение

#include <iBUSTelemetry.h>
#include "SoftIBus.h"             // SoftIBus library
SoftwareSerial IBuspin(8, 9);     // "serial" port on which we will be running the IBus connection.
// Since to read values we only need the Rx, just connect pin D8 and leave D9 open

// *** ВАЖНО!!! *** ЧИТАТЬ ВНИМАТЕЛЬНО!!! ***
// Так как библиоткека iBUSTelemetry.h использует прерывание PCINT0 во избежание конфликта
// в библиотеке SoftwareSerial (CustomSoftwareSerial.h) требуется замаркировать блок обработки прерывания PCINT0
// строки 313 - 320 (для CustomSoftwareSerial), то-есть для порта можно использовать пины  A0 .. A5 или D0 .. D7
// Информация актуальна при совместном использовании библиотек SoftIBus.h и iBUSTelemetry.h
/*
    D8 .. D13 - генерируют запрос прерывания PCINT0
    A0 .. A5  - генерируют запрос прерывания PCINT1 (D14 - D19)
    D0 .. D7  - генерируют запрос прерывания PCINT2
*/
int ch = 14;                      // число каналов радиоаппаратуры RC

#define UPDATE_INTERVAL 750
iBUSTelemetry telemetry(7); // I use only PCINT2 interrupt vector, so you can use D2 to D7 pins.

uint32_t prevMillis = 0; // Necessary to updateValues() method. Look below.
float i = 0;

#include <OneWire.h>
OneWire  ds(2);  // 4 - D2 (ESP8266)
byte addr[8];
byte data[12];
byte zero = 0;

volatile float temperature;
unsigned long timing;
unsigned long t1;
unsigned long t2;
uint16_t t_convert = 750; // врененной цикл запроса температуры, мин. 750


void setup()
{
  IBuspin.begin(115200);//the softserial port has to begin at this baud prior to starting it as the IBus port
#ifdef DEBUG
  Serial.begin(115200);//hardserial for debigging
#endif
  IBus.begin(IBuspin);//start the IBus object
  telemetry.begin(); // Let's start having fun!

  /*1*/  telemetry.addSensor(0x01); // You can use sensors definitions from iBUSSensors.h instead of numbers.
  // Ex.: telemetry.addSensor(IBUS_MEAS_TYPE_TEM);

  /*2*/ telemetry.addSensor(IBUS_MEAS_TYPE_GPS_STATUS);
  /*3*/ telemetry.addSensor(IBUS_MEAS_TYPE_SPE);
  /*4*/ telemetry.addSensor(IBUS_MEAS_TYPE_GPS_LAT);
  /*5*/ telemetry.addSensor(IBUS_MEAS_TYPE_ARMED);
  /*6*/ telemetry.addSensor(IBUS_MEAS_TYPE_FLIGHT_MODE);
  /*7*/ telemetry.addSensor(IBUS_MEAS_TYPE_ALT);

  pinMode(3, OUTPUT);
  digitalWrite(3, HIGH);
  int ii = 0;

label:
  if (ii < 6)
  {
    if ( !ds.search(addr))
    { // пока возвращаемый адрес == 0
#ifdef DEBUG
      Serial.println F("No more addresses.");
      Serial.println(addr[8]);
#endif
      ds.reset_search();
      delay(250);
      ++ii;
      goto label;
    }

    if (OneWire::crc8(addr, 7) != addr[7])
    { //проверка массива адреса на CRC-8
#ifdef DEBUG
      Serial.println F("CRC is not valid!");
#endif
      ++ii; goto label;
    }
  }
  ds.reset();      // сброс шины
  ds.select(addr); // выставить адрес
  ds.write(0x4E);  // разрешение записать конфиг
  ds.write(0x7F);  // Th контроль температуры макс 128грд
  ds.write(0xFF);  // Tl контроль температуры мин -128грд
  ds.write(0x60);  // 0x60 12-бит разрешение, 0x00 9-бит разрешение
  ds.write(0x1F);  // точность 0,5гр = 1F; 0,25гр = 3F; 0,125гр = 5F; 0,0625гр = 7F;

  // запросим температуру, считывать будем по таймеру
  ds.reset();
  ds.write(0xCC); // Обращение ко всем датчикам
  ds.write(0x44); // Команда на конвертацию
  timing = millis();
}

void loop()
{
#ifdef DEBUG
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
#endif

  updateValues(); // Very important! iBUS protocol is very sensitive to timings.
  // DO NOT USE ANY delay()! Look at updateValues() method.
  // It's an example of how to use intervals without delays.

  telemetry.run(); //It must be here. Period.
}


void updateValues()
{
  uint32_t currMillis = millis();

  if (currMillis - prevMillis >= UPDATE_INTERVAL) { // Code in the middle of these brackets will be performed every 500ms.
    prevMillis = currMillis;
    // возвращает температуру с датчика
    int temp;
    ds.reset();
    ds.select(addr);
    ds.write(0xBE);
    for (int i = 0; i < 9; i++) data[i] = ds.read();

    if (OneWire::crc8(data, 8) != data[8])
    { // проверка CRC считанной температуры.
#ifdef DEBUG
      Serial.println F("Data CRC is not valid!");
#endif
    } else {

      temp = (data[1] << 8) | data[0]; // Переводим в температуру
      if (data[7] == 0x10) temp = (temp & 0xFFF0) + 12 - data[6];
      if ((temp == 0) && (data[5] < 0xFF)) zero++;
      temperature = (float)temp / 16.00;

      ds.reset();
      ds.write(0xCC);                       // Обращение ко всем датчикам
      ds.write(0x44);                       // Команда на конвертацию
      t2 = micros();
    }



    telemetry.setSensorValueFP(1, temperature /*i*/); // Now, you have two ways to set sensors values. Using floating point variables
    // or directly in 32bit integer, but then you have to format variable by yourself.
    // Ex.: telemetry.setSensorValueFP(1, 24.45); is equivalent to telemetry.setSensorValue(1, 2445);
    // The values differ for different sensors.

    telemetry.setSensorValue(2, telemetry.gpsStateValues(3, 8)); // As GPS status consists of two values,
    // use gpsStateValues(firstVal, secondVal) to set it properly.

    telemetry.setSensorValue(3, 123 * 10);

    telemetry.setSensorValue(4, 179583647); // You can set LAT / LON using FP metohod, but due to fact floats have only 6 digits precision,
    // your values on tx may be corrupted in some cases. It's better to use setSensorValue().

    telemetry.setSensorValue(5, UNARMED); // ARMED / UNARMED or 1 / 0 could be used.

    telemetry.setSensorValue(6, LOITER); // Available flight modes:     STAB   0
    // ACRO   1
    // AHOLD  2
    // AUTO   3
    // GUIDED 4
    // LOITER 5
    // RTL    6
    // CIRCLE 7
    // PHOLD  8
    // LAND   9

    telemetry.setSensorValueFP(7, 54.87);

    i += 0.1;
    if (i > 50)
      i = 0;

    // These were the most difficult sensors to use. I hope that this library will be useful for you and will make your work easier. :)
  }
} /* updateValues */
