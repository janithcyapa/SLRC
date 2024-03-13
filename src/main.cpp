#include <Arduino.h>
#include <Wire.h>
#include "drive/drive.h"
#include "qrt/qrt.h"
#include <QTRSensors.h>
// the setup function runs once when you press reset or power the board
Drive drive = Drive();
Qrt qrt = Qrt(false);
void setup()
{
  Wire.begin();
  Serial.begin(115200);
  Serial.print("Begin Programme...\n");
  drive.Setup();
  qrt.Begin();
  qrt.Calibrate(400);
  // beginDrive();
}

// the loop function runs over and over again forever
void loop()
{
  qrt.Readline();
  Serial.print(qrt.positionLine);
  Serial.print('\t');
  Serial.println(qrt.positionLineData);

  delay(1000);
}
