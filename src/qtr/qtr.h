#include <Arduino.h>
#include <QTRSensors.h>
#include "../config/pins.h"
class Qtr
{
public:
    QTRSensors qtr;
    int threshold[SensorCount];
    bool isModeWhite;
    uint16_t positionLine;
    String positionLineData;
    uint16_t sensorValues[(int)SensorCount];
    Qtr(bool _isModeWhite);
    int Begin();
    int Calibrate(int count);

    int setModeWhite();
    int setModeBlack();
    int Readline();
};
