#include <QTRSensors.h>
#include "../config/pins.h"
#include <Arduino.h>
class Qrt
{
public:
    QTRSensors qtr;
    bool isModeWhite;
    uint16_t positionLine;
    String positionLineData;
    uint16_t sensorValues[(int)SensorCount];
    Qrt(bool _isModeWhite);
    int Begin();
    int Calibrate(int count);
    int setModeWhite();
    int setModeBlack();
    int Readline();
    Qrt();
};
