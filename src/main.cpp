#include <Arduino.h>
#include <Wire.h>
#include "drive/drive.h"
#include "qtr/qtr.h"
#include "servo/servo.h"
#include "ultrasonic/ultrasonic.h"
#include "PID/PID.h"

Drive drive = Drive();
Qtr qtr = Qtr(false);
Servo servo = Servo();
UltraSonic us = UltraSonic();
void setup()
{
  Wire.begin();
  Serial.begin(115200);
  Serial.print("Begin Programme...\n");
  drive.Begin();
  // qtr.Begin();
  // qtr.Calibrate(10);
  // delay(3000);
  // us.Begin();
  // servo.Begin();
  // GoPID(qtr, drive);
}

void loop()
{

  // 90
  // drive.Go(100, 0);
  // delay(750);
  // drive.Stop();
  // delay(500);
  // GoPIDCenter(qtr, drive);
  // delay(5000);

  // // 180
  drive.Go(255, 255);
  delay(5000);
  drive.Stop();
  delay(500);
  // GoPIDCenter(qtr, drive);
  // delay(5000);
}
