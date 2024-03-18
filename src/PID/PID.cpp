#include "../drive/drive.h"
#include "../qtr/qtr.h"
#include "PID.h"
#include <Arduino.h>
#include "../config/constants.h"

int P;
int I;
int D;

float Kp = 0.03;
float Ki = 0.0;
float Kd = 0.01;

int lastError = 0;

int baseSpeed = 75;
int speedLimit = 255;

int turnR = 1000;
int turnL = 1000;
int UTurnR = 1000;
int UTurnL = 1000;

void GoPID(Qtr qtr, Drive drive)
{
    lastError = 0;
    I = 0;
    while (true)
    {
        qtr.Readline();
        String line = qtr.positionLineData;
        if (line == "00000000" || line == "11111111" || line == "11111000" || line == "11110000" || line == "00001111" || line == "00011111")
        {
            drive.Stop();
            break;
        }
        else
        {
            int error = 3500 - qtr.positionLine;

            P = error;
            I = error + I;
            D = error - lastError;

            lastError = error;

            int motorSpeedChange = P * Kp + I * Ki + D * Kd;

            int motorSpeedR = baseSpeed - motorSpeedChange;
            int motorSpeedL = baseSpeed + motorSpeedChange;

            if (motorSpeedR < -1 * speedLimit)
                motorSpeedR = -1 * speedLimit;
            else if (motorSpeedR > speedLimit)
                motorSpeedR = speedLimit;

            if (motorSpeedL < -1 * speedLimit)
                motorSpeedL = -1 * speedLimit;
            else if (motorSpeedL > speedLimit)
                motorSpeedL = speedLimit;

            drive.Go(motorSpeedR, motorSpeedL);
        }
    }
}

void CenterPID(Qtr qtr, Drive drive)
{
    lastError = 0;
    I = 0;
    while (true)
    {
        qtr.Readline();
        String line = qtr.positionLineData;
        int error = 3500 - qtr.positionLine;
        if (abs(error) < 100)
        {
            drive.Stop();
            break;
        }
        else
        {

            P = error;
            I = error + I;
            D = error - lastError;

            lastError = error;

            int motorSpeedChange = P * Kp + I * Ki + D * Kd;

            int motorSpeedR = -2.5 * motorSpeedChange;
            int motorSpeedL = 2.5 * motorSpeedChange;

            if (motorSpeedR < -1 * speedLimit)
                motorSpeedR = -1 * speedLimit;
            else if (motorSpeedR > speedLimit)
                motorSpeedR = speedLimit;

            if (motorSpeedL < -1 * speedLimit)
                motorSpeedL = -1 * speedLimit;
            else if (motorSpeedL > speedLimit)
                motorSpeedL = speedLimit;

            drive.Go(motorSpeedR, motorSpeedL);
        }
    }
}

void TurnR(Drive drive)
{
    drive._instance->tickR = 0;
    lastError = 0;
    I = 0;
    attachInterrupt(digitalPinToInterrupt(encR), Drive::countr, FALLING);
    while (drive._instance->tickR < turnR)
    {
        int error = turnR - (drive._instance->tickR);
        // Serial.print(error);
        P = error;
        I = error + I;
        D = error - lastError;
        int motorSpeedChange = baseSpeed + P * Kp + I * Ki + D * Kd;
        motorSpeedChange = constrain(motorSpeedChange, 0, 255);
        // Serial.println(motorSpeedChange);
        drive.Go(0, motorSpeedChange);
    }
    detachInterrupt(digitalPinToInterrupt(encR));
    drive.Stop();
}
void TurnL(Drive drive)
{
    drive._instance->tickL = 0;
    attachInterrupt(digitalPinToInterrupt(encL), Drive::countl, FALLING);
    lastError = 0;
    I = 0;
    while (drive._instance->tickL < turnL)
    {
        int error = turnL - drive._instance->tickL;
        P = error;
        I = error + I;
        D = error - lastError;
        int motorSpeedChange = baseSpeed + P * Kp + I * Ki + D * Kd;
        motorSpeedChange = constrain(motorSpeedChange, 0, 255);
        drive.Go(motorSpeedChange, 0);
    }
    detachInterrupt(digitalPinToInterrupt(encL));
    drive.Stop();
}
void TurnU(Drive drive)
{
    drive.tickL = 0;
    drive.tickR = 0;
    attachInterrupt(digitalPinToInterrupt(encR), Drive::countr, FALLING);
    attachInterrupt(digitalPinToInterrupt(encL), Drive::countl, FALLING);
    lastError = 0;
    I = 0;
    while (drive.tickL < turnL || drive.tickR < turnR)
    {
        int error = drive.tickL - turnL;
        P = error;
        I = error + I;
        D = error - lastError;
        int motorSpeedChange = P * Kp + I * Ki + D * Kd;
        motorSpeedChange = constrain(motorSpeedChange, 0, 255);
        int R = 0;
        int L = 0;
        if (drive.tickL < turnL)
            L = -1 * motorSpeedChange;
        if (drive.tickR < turnR)
            R = motorSpeedChange;

        drive.Go(R, L);
    }
    detachInterrupt(digitalPinToInterrupt(encR));
    detachInterrupt(digitalPinToInterrupt(encL));
    drive.Stop();
}