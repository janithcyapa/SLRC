#include <Arduino.h>
#include <QTRSensors.h>
#include "qrt.h"
#include "../config/pins.h"
using namespace std;

Qrt::Qrt(bool _isModeWhite)
{
    isModeWhite = _isModeWhite;
    positionLineData = "";
}
int Qrt::Begin()
{
    uint8_t _SensorCount = SensorCount;
    qtr.setTypeAnalog();
    qtr.setSensorPins((const uint8_t[]){A0, A1, A2, A3, A4, A5, A6, A7}, _SensorCount);
    qtr.setEmitterPin(IREmitterPin);
    Serial.print("Qrt Started\n");
    return 0;
}
int Qrt::Calibrate(int count)
{
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, HIGH);
    Serial.print("Calibration Start\n");
    for (uint16_t i = 0; i < 400; i++)
    {
        qtr.calibrate();
    }
    digitalWrite(LED_BUILTIN, LOW);

    // for (uint8_t i = 0; i < SensorCount; i++)
    // {
    //     Serial.print(qtr.calibrationOn.minimum[i]);
    //     Serial.print(' ');
    // }
    // Serial.println();
    // for (uint8_t i = 0; i < SensorCount; i++)
    // {
    //     Serial.print(qtr.calibrationOn.maximum[i]);
    //     Serial.print(' ');
    // }
    Serial.print("Calibration Complete\n");
    return 0;
}
int Qrt::Readline()
{
    uint16_t _positionLine;
    if (isModeWhite)
        _positionLine = qtr.readLineWhite(sensorValues);
    else
        _positionLine = qtr.readLineBlack(sensorValues);
    positionLine = _positionLine;

    String _positionLineData;
    for (uint8_t i = 0; i < SensorCount; i++)
        if (sensorValues[i] > 900)
            _positionLineData = _positionLineData + "1";
        else
            _positionLineData = _positionLineData + "0";
    positionLineData = _positionLineData;

    // for (uint8_t i = 0; i < SensorCount; i++)
    // {
    //     Serial.print(sensorValues[i]);
    //     Serial.print('\t');
    // }
    // Serial.print(positionLineData);
    // Serial.print('\t');
    // Serial.println(positionLine);
    return 0;
}
int Qrt::setModeWhite()
{
    isModeWhite = true;
    return 0;
}
int Qrt::setModeBlack()
{
    isModeWhite = false;
    return 0;
}
