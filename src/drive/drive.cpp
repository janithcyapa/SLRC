#include "../config/pins.h"
#include <Arduino.h>
#include "drive.h"
#include <Wire.h>

Drive::Drive()
{
    tickR = 0;
    tickL = 0;
}

int Drive::Begin()
{

    pinMode(MenA, OUTPUT);
    pinMode(MenB, OUTPUT);
    pinMode(Min1, OUTPUT);
    pinMode(Min2, OUTPUT);
    pinMode(Min3, OUTPUT);
    pinMode(Min4, OUTPUT);
    pinMode(encR, INPUT_PULLUP);
    pinMode(encL, INPUT_PULLUP);

    // Turn off motors - Initial state
    OR(0, LOW, LOW);
    OL(0, LOW, LOW);

    // attachInterrupt(digitalPinToInterrupt(encR), Drive::countr, FALLING);
    // attachInterrupt(digitalPinToInterrupt(encL), Drive::countl, FALLING);
    // attachInterrupt(encL, i2, RISING);
    // Serial.println("Drive started..\n");
    return 0;
}
int Drive::Stop()
{
    OR(0, LOW, LOW);
    OL(0, LOW, LOW);
    return 0;
}
int Drive::Go(int r, int l)
{

    if (r >= 0)
        OR(r, HIGH, LOW);
    else
        OR(r * (-1), LOW, HIGH);

    if (l >= 0)
        OL(l, HIGH, LOW);
    else
        OL(l * (-1), LOW, HIGH);

    return 0;
}

Drive *Drive::_instance = nullptr;

void Drive::countr()
{
    // Serial.println("int0");
    if (_instance)
    {
        _instance->tickR++;
    }
}
void Drive::countl()
{
    if (_instance)
    {
        _instance->tickL++;
    }
}

void OR(int R, uint8_t E1, uint8_t E2)
{
    analogWrite(MenA, R);
    digitalWrite(Min1, E1);
    digitalWrite(Min2, E2);
}
void OL(int L, uint8_t E3, uint8_t E4)
{
    analogWrite(MenB, L);
    digitalWrite(Min3, E3);
    digitalWrite(Min4, E4);
}