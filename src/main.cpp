#include <Arduino.h>
#include <Wire.h>
#include "drive/drive.h"
#include "qtr/qtr.h"
#include "servo/servo.h"
#include "ultrasonic/ultrasonic.h"
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
  // mySerial.print("Send");
  if (Serial.available() > 0)
  {
    String data = Serial.readStringUntil('\n');
    if (data == "Test")
    {
      Serial.println("DONE");
    }

    else if (data == "QCal")
    {
      print("Calibrating");
      qtr.Calibrate(400);
      Serial.println("DONE");
    }
    else if (data == "QWhite")
    {
      print("Calibrating");
      qtr.setModeWhite();
      Serial.println("DONE");
    }
    else if (data == "QWhite")
    {
      print("Calibrating");
      qtr.setModeWhite();
      Serial.println("DONE");
    }
    else if (data == "QBlack")
    {
      print("Calibrating");
      qtr.setModeWhite();
      Serial.println("DONE");
    }

    else if (data == "Go")
    {
      print("PID GO");
      GoPID(qtr, drive, false);
      Serial.println("DONE");
    }
    else if (data == "Reverse")
    {
      print("PID GO");
      ReversePID(qtr, drive, false);
      Serial.println("DONE");
    }
    else if (data == "GoO")
    {
      print("PID GO");
      GoPID(qtr, drive, true);
      Serial.println("DONE");
    }
    else if (data == "ReverseO")
    {
      print("PID GO");
      ReversePID(qtr, drive, true);
      Serial.println("DONE");
    }
    else if (data == "CenterPID")
    {
      print("PID GO");
      CenterPID(qtr, drive);
      Serial.println("DONE");
    }
    else if (data == "TurnR")
    {
      print("Turn Right");
      TurnR(drive);
      Serial.println("DONE");
    }
    else if (data == "TurnL")
    {
      print("Turn Left");
      TurnL(drive);
      Serial.println("DONE");
    }
    else if (data == "U")
    {
      print("Turn Left");
      TurnU(drive);
      Serial.println("DONE");
    }

    else if (data.indexOf("Kp") != -1)
    {
      print("SET Kp");
      float number = String(data).substring(String(data).indexOf('_') + 1).toFloat();
      Kp = number;
      Serial.println("DONE");
    }
    else if (data.indexOf("Ki") != -1)
    {
      print("SET Ki");
      float number = String(data).substring(String(data).indexOf('_') + 1).toFloat();
      Ki = number;
      Serial.println("DONE");
    }
    else if (data.indexOf("Kd") != -1)
    {
      print("SET Kd");
      float number = String(data).substring(String(data).indexOf('_') + 1).toFloat();
      Kd = number;
      Serial.println("DONE");
    }
    else if (data.indexOf("Bs") != -1)
    {
      print("SET Base Speed");
      int number = String(data).substring(String(data).indexOf('_') + 1).toInt();
      baseSpeed = number;
      Serial.println("DONE");
    }
    else if (data.indexOf("Sl") != -1)
    {
      print("SET Speed Limit");
      int number = String(data).substring(String(data).indexOf('_') + 1).toInt();
      speedLimit = number;
      Serial.println("DONE");
    }
    else if (data.indexOf("TR") != -1)
    {
      print("Right Count");
      int number = String(data).substring(String(data).indexOf('_') + 1).toInt();
      turnR = number;
      Serial.println("DONE");
    }
    else if (data.indexOf("TL") != -1)
    {
      print("Left Count");
      int number = String(data).substring(String(data).indexOf('_') + 1).toInt();
      turnL = number;
      Serial.println("DONE");
    }
    else if (data.indexOf("UTR") != -1)
    {
      print("Right Count");
      int number = String(data).substring(String(data).indexOf('_') + 1).toInt();
      UTurnR = number;
      Serial.println("DONE");
    }
    else if (data.indexOf("UTL") != -1)
    {
      print("Left Count");
      int number = String(data).substring(String(data).indexOf('_') + 1).toInt();
      UTurnL = number;
      Serial.println("DONE");
    }
    else
    {
      drive.Stop();
    }
  }
  // // 90
  // drive.Go(0, 255);
  // delay(2000);
  // drive.Stop();
  // drive.Go(255, 0);
  // delay(2000);
  // drive.Stop();
  // Serial.print(drive.tickR);
  // Serial.print("\t");
  // Serial.println(drive.tickL);

  // delay(1000);
  // // GoPIDCenter(qtr, drive);
  // delay(5000);

  // // 180
  // for (size_t i = 0; i < 255; i++)
  // {
  //   drive.Go(i, i);
  //   delay(100);

  //   /* code */
  // }

  // drive.Stop();
  // delay(2000);

  // GoPIDCenter(qtr, drive);
  // delay(5000);
}
