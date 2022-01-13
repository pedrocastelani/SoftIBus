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

#define UPDATE_INTERVAL 500
iBUSTelemetry telemetry(7); // I use only PCINT2 interrupt vector, so you can use D2 to D7 pins.

uint32_t prevMillis = 0; // Necessary to updateValues() method. Look below.
float i = 0;

#include <Servo.h>

Servo myservo2;  // create servo object to control a servo
Servo myservo3;
Servo myservo4;
Servo myservo5;
Servo myservo6;
//Servo myservo7;
//Servo myservo8;
//Servo myservo9;
Servo myservo10;
Servo myservo11;
Servo myservo12;
Servo myservo13;
Servo myservo14;
Servo myservo15;
Servo myservo16;
Servo myservo17;
Servo myservo18;
Servo myservo19;

void setup()
{
  IBuspin.begin(115200);//the softserial port has to begin at this baud prior to starting it as the IBus port
  Serial.begin(115200);//hardserial for debigging
  IBus.begin(IBuspin);//start the IBus object
  telemetry.begin(); // Let's start having fun!

  telemetry.addSensor(0x01); // You can use sensors definitions from iBUSSensors.h instead of numbers.
  // Ex.: telemetry.addSensor(IBUS_MEAS_TYPE_TEM);

  telemetry.addSensor(IBUS_MEAS_TYPE_GPS_STATUS);
  telemetry.addSensor(IBUS_MEAS_TYPE_SPE);
  telemetry.addSensor(IBUS_MEAS_TYPE_GPS_LAT);
  telemetry.addSensor(IBUS_MEAS_TYPE_ARMED);
  telemetry.addSensor(IBUS_MEAS_TYPE_FLIGHT_MODE);
  telemetry.addSensor(IBUS_MEAS_TYPE_ALT);

  myservo2.attach(2); //1
  myservo3.attach(3); //2
  myservo4.attach(4); //3
  myservo5.attach(5); //4
  myservo6.attach(6); //5
  // myservo7.attach(7); //6
  // myservo8.attach(8); //7
  // myservo9.attach(9); //8
  myservo10.attach(10); //9
  myservo11.attach(11); //10
  myservo12.attach(12); //11
  myservo13.attach(13); //12
  myservo14.attach(14); //13
  myservo15.attach(15); //14
  myservo16.attach(16); //15
  myservo17.attach(17); //16
  myservo18.attach(18); //17
  myservo19.attach(19); //18
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
  updateValues(); // Very important! iBUS protocol is very sensitive to timings.
  // DO NOT USE ANY delay()! Look at updateValues() method.
  // It's an example of how to use intervals without delays.

  telemetry.run(); //It must be here. Period.

  myservo2.write(IBus.readChannel(1));
  myservo3.write(IBus.readChannel(2));
  myservo4.write(IBus.readChannel(3));
  myservo5.write(IBus.readChannel(4));
  myservo6.write(IBus.readChannel(5));
//  myservo7.write(IBus.readChannel(6));
//  myservo8.write(IBus.readChannel(7));
//  myservo9.write(IBus.readChannel(8));
  myservo10.write(IBus.readChannel(9));
  myservo11.write(IBus.readChannel(10));
  myservo12.write(IBus.readChannel(11));
  myservo13.write(IBus.readChannel(12));
  myservo14.write(IBus.readChannel(13));
  myservo15.write(IBus.readChannel(14));
  myservo16.write(IBus.readChannel(1));
  myservo17.write(IBus.readChannel(2));
  myservo18.write(IBus.readChannel(3));
  myservo19.write(IBus.readChannel(4)); 
}


void updateValues()
{
  uint32_t currMillis = millis();

  if (currMillis - prevMillis >= UPDATE_INTERVAL) { // Code in the middle of these brackets will be performed every 500ms.
    prevMillis = currMillis;

    telemetry.setSensorValueFP(1, i); // Now, you have two ways to set sensors values. Using floating point variables
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
