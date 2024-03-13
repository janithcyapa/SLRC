#include <Arduino.h>
#include <Wire.h>
#include "drive/drive.h"
#include "qrt/qrt.h"
#include "servo/servo.h"

Drive drive = Drive();
Qrt qrt = Qrt(false);
Servo servo = Servo();
void setup()
{
  Wire.begin();
  Serial.begin(115200);
  Serial.print("Begin Programme...\n");
  // drive.Begin();
  // qrt.Begin();
  // qrt.Calibrate(400);
  servo.Begin();
}

void loop()
{
  // servo.Set(0, 0);
  servo.Set(1, 0);
  delay(1000);
  // servo.Set(0, 90);
  // delay(1000);

}
