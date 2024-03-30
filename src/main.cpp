#include <Arduino.h>
#include <Wire.h>
#include "drive/drive.h"
#include "qtr/qtr.h"
#include "display/display.h"
#include "config/constants.h"
Drive drive = Drive();
Qtr qtr = Qtr(true);

float Kp = 0.2;
float Ki = 0.0001;
float Kd = 0.01;
int baseSpeed = 175;
int speedLimit = 255;

int P = 0, D = 0, I = 0, LE = 0;
void setup()
{
  Wire.begin();
  Serial.begin(115200);
  OLEDBegin();
  drive.Begin();
  Drive::_instance = &drive;
  qtr.Begin();
}

void loop()
{
  if (Serial.available() > 0)
  {
    String data = Serial.readStringUntil('\n');

    if (data == "Test")
    {
      Serial.println("TESTDONE");
    }
    else if (data == "QCal")
    {
      qtr.Calibrate(400);
      Serial.println("DONE");
    }
    else if (data == "QWhite")
    {
      qtr.setModeWhite();
      Serial.println("DONE");
    }
    else if (data == "QBlack")
    {
      qtr.setModeWhite();
      Serial.println("DONE");
    }
    else if (data == "Go" || data == "GoO")
    {

      LE = 0;
      I = 0;
      if (data == "GoO")
      {
        pinMode(ObstaclePin1, INPUT);
        pinMode(ObstaclePin1, INPUT);
      }

      while (true)
      {
        if (data == "GoO")
          if (digitalRead(ObstaclePin1) != 1 || digitalRead(ObstaclePin2) != 1)
          {
            drive.Stop();
            break;
          }
        int lineVal = qtr.Readline();
        String line = qtr.positionLineData;

        // for (uint8_t i = 0; i < SensorCount; i++)
        // {
        //   Serial.print(qtr.sensorValues[i]);
        //   Serial.print('\t');
        // }
        // Serial.print(lineVal);
        // Serial.print('\t');
        // Serial.print(line);
        // Serial.print('\t');
        if (line == "00000000" || line == "11111111" || line == "11110000" || line == "00001111")
        // if (false)
        {
          drive.Stop();
          break;
        }
        else
        {
          int error = 3500 - lineVal;

          P = error;
          I = error + I;
          D = error - LE;

          LE = error;

          int mSP = P * Kp + I * Ki + D * Kd;

          int R = baseSpeed + mSP;
          int L = baseSpeed - mSP;

          R = constrain(R, -1 * speedLimit, speedLimit);
          L = constrain(L, -1 * speedLimit, speedLimit);

          // Serial.print(R);
          // Serial.print('\t');
          // Serial.println(L);
          drive.Go(R, L);
        }
      }
      Serial.println("DONE");
    }
    else if (data == "Reverse" || data == "ReverseO")
    {
      LE = 0;
      I = 0;
      if (data == "ReverseO")
      {
        pinMode(ObstaclePin1, INPUT);
        pinMode(ObstaclePin2, INPUT);
      }
      while (true)
      {
        if (data == "ReverseO")
          if (digitalRead(ObstaclePin1) != 1 || digitalRead(ObstaclePin2) != 1)
          {
            drive.Stop();
            break;
          }
        qtr.Readline();
        String line = qtr.positionLineData;
        if (line == "00000000" || line == "11111111" || line == "11110000" || line == "00001111")
        {
          drive.Stop();
          break;
        }
        else
        {
          int error = 3500 - qtr.positionLine;

          P = error;
          I = error + I;
          D = error - LE;

          LE = error;

          int mSP = P * Kp + I * Ki + D * Kd;

          int R = -1 * baseSpeed + mSP;
          int L = -1 * baseSpeed - mSP;

          R = constrain(R, -1 * speedLimit, speedLimit);
          L = constrain(L, -1 * speedLimit, speedLimit);
          drive.Go(R, L);
        }
      }
      Serial.println("DONE");
    }
    else if (data == "CenterPID")
    {
      LE = 0;
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
          D = error - LE;

          LE = error;

          int mSP = P * Kp + I * Ki + D * Kd;

          int R = baseSpeed + mSP;
          int L = baseSpeed - mSP;

          R = constrain(R, -1 * speedLimit, speedLimit);
          L = constrain(L, -1 * speedLimit, speedLimit);
          drive.Go(R, L);
        }
      }

      Serial.println("DONE");
    }
    else if (data.indexOf("D") != -1)
    {

      int pos1 = data.indexOf('_');
      int pos2 = data.lastIndexOf('_');
      int RC = data.substring(pos1 + 1, pos2).toInt();
      int LC = data.substring(pos2 + 1).toInt();
      drive.Encored(RC, LC);
      Serial.println("DONE");
    }
    else if (data.indexOf("Z") != -1)
    {

      int pos1 = data.indexOf('_');
      int pos2 = data.lastIndexOf('_');
      int RC = data.substring(pos1 + 1, pos2).toInt();
      int LC = data.substring(pos2 + 1).toInt();
      drive.Go(RC, LC);
      Serial.println("DONE");
    }

    else if (data.indexOf("Kp") != -1)
    {
      float number = String(data).substring(String(data).indexOf('_') + 1).toFloat();
      Kp = number;
      Serial.println("DONE");
    }
    else if (data.indexOf("Ki") != -1)
    {
      float number = String(data).substring(String(data).indexOf('_') + 1).toFloat();
      Ki = number;
      Serial.println("DONE");
    }
    else if (data.indexOf("Kd") != -1)
    {
      float number = String(data).substring(String(data).indexOf('_') + 1).toFloat();
      Kd = number;
      Serial.println("DONE");
    }
    else if (data.indexOf("Bs") != -1)
    {
      int number = String(data).substring(String(data).indexOf('_') + 1).toInt();
      baseSpeed = number;
      Serial.println("DONE");
    }
    else if (data.indexOf("Sl") != -1)
    {
      int number = String(data).substring(String(data).indexOf('_') + 1).toInt();
      speedLimit = number;
      Serial.println("DONE");
    }
    else
    {
      drive.Stop();
      Serial.println("DONE");
    }
  }
}