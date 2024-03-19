#include <Arduino.h>
#include <Wire.h>
#include "drive/drive.h"
#include "qtr/qtr.h"
#include "PID/PID.h"
#include "display/display.h"

Drive drive = Drive();
Qtr qtr = Qtr(true);

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
    print(data);
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
    else if (data == "CenterPID")
    {
      CenterPID(qtr, drive);
      Serial.println("DONE");
    }
    else if (data == "TurnR")
    {
      TurnR(drive);
      Serial.println("DONE");
    }
    else if (data == "TurnL")
    {
      TurnL(drive);
      Serial.println("DONE");
    }
    else if (data == "U")
    {
      TurnU(drive);
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
    else if (data.indexOf("TR") != -1)
    {
      int number = String(data).substring(String(data).indexOf('_') + 1).toInt();
      turnR = number;
      Serial.println("DONE");
    }
    else if (data.indexOf("TL") != -1)
    {
      int number = String(data).substring(String(data).indexOf('_') + 1).toInt();
      turnL = number;
      Serial.println("DONE");
    }
    else if (data.indexOf("UTR") != -1)
    {
      int number = String(data).substring(String(data).indexOf('_') + 1).toInt();
      UTurnR = number;
      Serial.println("DONE");
    }
    else if (data.indexOf("UTL") != -1)
    {
      int number = String(data).substring(String(data).indexOf('_') + 1).toInt();
      UTurnL = number;
      Serial.println("DONE");
    }
    else
    {
      drive.Stop();
    }
  }
}
