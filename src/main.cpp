#include <Arduino.h>
#include <Wire.h>
#include "drive/drive.h"
#include "qtr/qtr.h"
#include "PID/PID.h"
#include "display/display.h"
#include "config/constants.h"
Drive drive = Drive();
Qtr qtr = Qtr(false);

float Kp = 0.1;
float Ki = 0.0001;
float Kd = 0.01;
int baseSpeed = 75;
int speedLimit = 255;

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
    // String data = String(Serial.read());
    // Serial.write(data);
    // TODO: U Turn , forward, backward
    // print(data);
    // Serial.println(data);
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
    else if (data == "Go")
    {
      GoPID(qtr, drive, false);
      Serial.println("DONE");
    }
    else if (data == "Reverse")
    {
      ReversePID(qtr, drive, false);
      Serial.println("DONE");
    }
    else if (data == "GoO")
    {
      GoPID(qtr, drive, true);
      Serial.println("DONE");
    }
    else if (data == "ReverseO")
    {
      ReversePID(qtr, drive, true);
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

    else if (data == "CenterPID")
    {
      CenterPID(qtr, drive);
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