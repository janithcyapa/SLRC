#include "../drive/drive.h"
#include "../qtr/qtr.h"
#include "PID.h"
#include <Arduino.h>
#include "../config/constants.h"

int P;
int I;
int D;

float Kp = 0.03;
float Ki = 0.00001;
float Kd = 0.01;

int lastError = 0;

int baseSpeed = 60;
int speedLimit = 175;
void GoPID(Qtr qtr, Drive drive)
{
    lastError = 0;
    while (true)
    {
        qtr.Readline();
        String line = qtr.positionLineData;
        if (line == "00000000" || line == "11111111" || line == "11111000" || line == "11110000" || line == "00001111" || line == "00011111")
        {
            drive.Stop();
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

void GoPIDCenter(Qtr qtr, Drive drive)
{
    lastError = 0;
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