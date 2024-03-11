#include "../config/pins.h"
#include <Arduino.h>
#include "drive.h"
void beginDrive()
{
    pinMode(MenA, OUTPUT);
    pinMode(MenB, OUTPUT);
    pinMode(Min1, OUTPUT);
    pinMode(Min2, OUTPUT);
    pinMode(Min3, OUTPUT);
    pinMode(Min4, OUTPUT);

    // Turn off motors - Initial state
    digitalWrite(Min1, LOW);
    digitalWrite(Min2, LOW);
    digitalWrite(Min3, LOW);
    digitalWrite(Min4, LOW);
}