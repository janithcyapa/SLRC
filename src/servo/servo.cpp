// #include <Wire.h>
// #include <Arduino.h>
// #include <Adafruit_PWMServoDriver.h>
// #include "servo.h"
// #include "../config/constants.h"
// Servo::Servo() {}
// Servo::Begin()
// {
//     servo.begin();
//     servo.setOscillatorFrequency(SERVO_OCILT_FREQ);
//     servo.setPWMFreq(SERVO_FREQ);
//     return 0;
// }

// Servo::Set(int servonum, int angle)
// {
//     uint16_t pulselength = map(angle, 0, 180, SERVOMIN, SERVOMAX);
//     servo.setPWM(servonum, 0, pulselength);
//     return 0;
// }