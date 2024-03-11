#include <Arduino.h>
#include <Wire.h>
#include "drive/drive.h"
// the setup function runs once when you press reset or power the board

void setup()
{
  Wire.begin();
  Serial.begin(115200);
  Serial.print("Begin Programme...\n");
  beginDrive();
}

// the loop function runs over and over again forever
void loop()
{

  delay(2000);

  // // Now change motor directions
  // digitalWrite(in1, LOW);
  // digitalWrite(in2, HIGH);
  // digitalWrite(in3, LOW);
  // digitalWrite(in4, HIGH);
  // delay(2000);

  // // Turn off motors
  // digitalWrite(in1, LOW);
  // digitalWrite(in2, LOW);
  // digitalWrite(in3, LOW);
  // digitalWrite(in4, LOW);
  // delay(1000);
  // // speedControl();
  // // Turn on motors
  // digitalWrite(in1, LOW);
  // digitalWrite(in2, HIGH);
  // digitalWrite(in3, LOW);
  // digitalWrite(in4, HIGH);

  // // Accelerate from zero to maximum speed
  // for (int i = 0; i < 256; i++)
  // {
  //   analogWrite(enA, i);
  //   analogWrite(enB, i);
  //   delay(20);
  // }

  // // Decelerate from maximum speed to zero
  // for (int i = 255; i >= 0; --i)
  // {
  //   analogWrite(enA, i);
  //   analogWrite(enB, i);
  //   delay(20);
  // }

  // // Now turn off motors
  // digitalWrite(in1, LOW);
  // digitalWrite(in2, LOW);
  // digitalWrite(in3, LOW);
  // digitalWrite(in4, LOW);
  delay(1000);
}
