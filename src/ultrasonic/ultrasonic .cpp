#include <Wire.h>
#include <Arduino.h>
#include "ultrasonic.h"
#include "../config/pins.h"

UltraSonic::UltraSonic()
{
    distance = 0;
}
int UltraSonic::Begin()
{
    pinMode(TriggerPin, OUTPUT); // Sets the trigPin as an Output
    pinMode(EchoPin, INPUT);     // Sets the echoPin as an Input
    return 0;
}

float UltraSonic::Read()
{
    digitalWrite(TriggerPin, LOW);
    delayMicroseconds(2);
    digitalWrite(TriggerPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(TriggerPin, LOW);
    long duration = pulseIn(EchoPin, HIGH);
    distance = duration * 0.034 / 2;
    return distance;
}