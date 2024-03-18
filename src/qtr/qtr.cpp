#include <Arduino.h>
#include <QTRSensors.h>
#include "qtr.h"
#include "../config/pins.h"
#include "../config/constants.h"
using namespace std;

Qtr::Qtr(bool _isModeWhite)
{
    isModeWhite = _isModeWhite;
    positionLineData = "";
}
int Qtr::Begin()
{
    uint8_t _SensorCount = SensorCount;
    qtr.setTypeAnalog();
    qtr.setSensorPins((const uint8_t[]){A0, A1, A2, A3, A4, A5, A6, A7}, _SensorCount);
    qtr.setEmitterPin(IREmitterPin);
    return 0;
}
int Qtr::Calibrate(int count)
{
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, HIGH);
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
    return 0;
}

int Qtr::Readline()
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
/// @brief Detection mode to white Line
/// @return
int Qtr::setModeWhite()
{
    isModeWhite = true;
    return 0;
}
/// @brief Detection mode to black Line
/// @return
int Qtr::setModeBlack()
{
    isModeWhite = false;
    return 0;
}
