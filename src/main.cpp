#include <Arduino.h>
#include <Wire.h>
#include "drive/drive.h"
// #include "qtr/qtr.h"
#include "servo/servo.h"
#include "ultrasonic/ultrasonic.h"

Drive drive = Drive();
// Qtr Qtr = Qtr(false);
Servo servo = Servo();
UltraSonic us = UltraSonic();
void setup()
{
  Wire.begin();
  Serial.begin(115200);
  Serial.print("Begin Programme...\n");
  // drive.Begin();
  // Qtr.Begin();
  // qrt.Calibrate(100);
  // us.Begin();
  // servo.Begin();
}

void loop()
{
  // qrt.Readline();
  // delay(1000);
}
