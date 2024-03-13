#include <Arduino.h>
#include <Wire.h>

class UltraSonic
{
public:
    float distance;
    UltraSonic();
    int Begin();
    float Read();
};