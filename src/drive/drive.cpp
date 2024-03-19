#include "../config/pins.h"
#include "../config/constants.h"
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

int Drive::Encored(int rC, int lC)
{
    _instance->tickR = 0;
    _instance->tickL = 0;
    attachInterrupt(digitalPinToInterrupt(encR), Drive::countr, FALLING);
    attachInterrupt(digitalPinToInterrupt(encL), Drive::countl, FALLING);
    int rP = 0, rD = 0, rI = 0, rLE = 0;
    int lP = 0, lD = 0, lI = 0, lLE = 0;

    while (abs(rC) > _instance->tickR || abs(lC) > _instance->tickL)
    {
        int R = 0;
        int L = 0;
        if (abs(rC) > _instance->tickR)
        {
            int rE = abs(rC) - (_instance->tickR);
            rP = rE;
            rI = rE + rI;
            rD = rE - rLE;
            rLE = rE;
            R = baseSpeed + rP * Kp + rI * Ki + rD * Kd;
            Serial.print(String(_instance->tickR) + "\t" + String(rE) + "\t" + String(R));
        }
        if (abs(lC) > _instance->tickL)
        {
            int lE = abs(lC) > _instance->tickL ? abs(lC) - (_instance->tickL) : 0;

            lP = lE;
            lI = lE + lI;
            lD = lE - lLE;
            lLE = lE;

            L = baseSpeed + lP * Kp + lI * Ki + lD * Kd;
            Serial.print("\t" + String(_instance->tickL) + "\t" + String(lE) + "\t" + String(L));
        }

        R = constrain(R, 0, speedLimit);
        L = constrain(L, 0, speedLimit);
        R = rC > 0 ? R : -1 * R;
        L = lC > 0 ? L : -1 * L;
        Serial.println("\t" + String(R) + "\t" + String(L));

        Go(R, L);
    }
    Stop();
    detachInterrupt(digitalPinToInterrupt(encR));
    detachInterrupt(digitalPinToInterrupt(encL));
    return 0;
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