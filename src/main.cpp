#include <Arduino.h>
#include <Wire.h>
#include "drive/drive.h"
#include "qrt/qrt.h"
#include "servo/servo.h"
#include "ultrasonic/ultrasonic.h"

Drive drive = Drive();
Qrt qrt = Qrt(false);
Servo servo = Servo();
UltraSonic us = UltraSonic();
void setup()
{
  Wire.begin();
  Serial.begin(115200);
  Serial.print("Begin Programme...\n");
  // drive.Begin();
  // qrt.Begin();
  // qrt.Calibrate(400);
  us.Begin();
  servo.Begin();
}

void loop()
{
  delay(1000);
  for (int i = 0; i <= 180; i++)
  {
    servo.Set(0, i);
    float dis = us.Read();
    Serial.print(i);
    Serial.print("\t");
    Serial.println(dis);
    delay(200);
  }
  delay(5000);
  // float distance = us.Read();
  // Serial.println(distance);
  // servo.Set(0, 0);
  // servo.Set(1, 0);
  // delay(1000);
  // servo.Set(0, 90);
  // delay(1000);
}
