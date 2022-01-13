/*
 * iBUSTelemetry.cpp - adis1313
 *
 * Libraries or parts of the code used in this project:
 *
 * SoftwareSerialWithHalfDuplex
 * https://github.com/nickstedman/SoftwareSerialWithHalfDuplex
 *
 * iBUStelemetry
 * https://github.com/Hrastovc/iBUStelemetry
 *
 * FlySkyI6
 * https://github.com/qba667/FlySkyI6/blob/master/source/source/ibustelemetry.h
 *
 * Big thanks to the authors!
 */

#ifndef iBUSSensors_h
#define iBUSSensors_h

#define MAX_SENS_COUNT 15

#define STAB           0
#define ACRO           1
#define AHOLD          2
#define AUTO           3
#define GUIDED         4
#define LOITER         5
#define RTL            6
#define CIRCLE         7
#define PHOLD          8
#define LAND           9

#define UNARMED        0
#define ARMED          1

// 2 byte sensors
#define IBUS_MEAS_TYPE_INTV           0x00 // Internal Voltage
#define IBUS_MEAS_TYPE_TEM            0x01 // Temperature
#define IBUS_MEAS_TYPE_EXTV           0x03 // External voltage (Внешнее напряжение)
#define IBUS_MEAS_TYPE_CELL           0x04 // Avg cell voltage(Среднее напряжение ячейки)
#define IBUS_MEAS_TYPE_BAT_CURR       0x05 // Battery current (Ток батареи)
#define IBUS_MEAS_TYPE_FUEL           0x06 // Remaining battery percentage -(Оставшийся процент заряда батареи)
#define IBUS_MEAS_TYPE_RPM            0x07 // Throttle value / battery capacity (Значение дроссельной заслонки /емкость аккумулятора) (обороты)
#define IBUS_MEAS_TYPE_CMP_HEAD       0x08 // Heading
#define IBUS_MEAS_TYPE_CLIMB_RATE     0x09 // Climb rate (Скорость набора высоты)
#define IBUS_MEAS_TYPE_COG            0x0a // Course over ground (Курс над землей)
#define IBUS_MEAS_TYPE_GPS_STATUS     0x0b // GPS status (2 values)
#define IBUS_MEAS_TYPE_ACC_X          0x0c // Acc X
#define IBUS_MEAS_TYPE_ACC_Y          0x0d // Acc Y
#define IBUS_MEAS_TYPE_ACC_Z          0x0e // Acc Z
#define IBUS_MEAS_TYPE_ROLL           0x0f // Roll
#define IBUS_MEAS_TYPE_PITCH          0x10 // Pitch
#define IBUS_MEAS_TYPE_YAW            0x11 // Yaw
#define IBUS_MEAS_TYPE_VERTICAL_SPEED 0x12 // Vertical speed (Вертикальная скорость)
#define IBUS_MEAS_TYPE_GROUND_SPEED   0x13 // Speed m/s (Скорость м/с)
#define IBUS_MEAS_TYPE_GPS_DIST       0x14 // Distance from home (Расстояние от дома)
#define IBUS_MEAS_TYPE_ARMED          0x15 // Armed / unarmed
#define IBUS_MEAS_TYPE_FLIGHT_MODE    0x16 // Flight mode (Режим полета)

#define IBUS_MEAS_TYPE_PRES           0x41 // Pressure (Давление)
#define IBUS_MEAS_TYPE_ODO1           0x7c // Odometer1
#define IBUS_MEAS_TYPE_ODO2           0x7d // Odometer2
#define IBUS_MEAS_TYPE_SPE            0x7e // Speed km/h (Скорость км/ч)//2byte km/h
#define IBUS_MEAS_TYPE_TX_V           0x7f // TX Voltage


// 4 byte sensors

#define IBUS_MEAS_TYPE_GPS_LAT 0x80 // WGS84 in degrees * 1E7 (широта по GPS)
#define IBUS_MEAS_TYPE_GPS_LON 0x81 // WGS84 in degrees * 1E7 (долгота по GPS)
#define IBUS_MEAS_TYPE_GPS_ALT 0x82 // GPS altitude (Высота по GPS)
#define IBUS_MEAS_TYPE_ALT     0x83 // Altitude (Высота)
#define IBUS_MEAS_TYPE_ALT_MAX 0x84 // Max altitude (Максимальная высота)
#define IBUS_MEAS_TYPE_S85     0x85
#define IBUS_MEAS_TYPE_S86     0x86
#define IBUS_MEAS_TYPE_S87     0x87
#define IBUS_MEAS_TYPE_S88     0x88
#define IBUS_MEAS_TYPE_S89     0x89
#define IBUS_MEAS_TYPE_S8a     0x8a

/*
//#define IBUS_MEAS_TYPE_ALT_FLYSKY		0xf9    // Altitude			//2 bytes signed in m
#define IBUS_MEAS_TYPE_SNR      0xfa // SNR
#define IBUS_MEAS_TYPE_NOISE    0xfb // Noise
#define IBUS_MEAS_TYPE_RSSI     0xfc // RSSI
#define IBUS_MEAS_TYPE_ERR      0xfe // Error rate
#define IBUS_MEAS_TYPE_UNKNOWN  0xff


#define IBUS_MEAS_TYPE_GPS_FULL   0xfd
#define IBUS_MEAS_TYPE_VOLT_FULL  0xf0
#define IBUS_MEAS_TYPE_ACC_FULL   0xef
*/

#endif // ifndef iBUSSensors_h
