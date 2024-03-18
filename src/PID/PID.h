extern float Kp;
extern float Ki;
extern float Kd;
extern int baseSpeed;
extern int speedLimit;

extern int turnL;
extern int turnR;
extern int UTurnL;
extern int UTurnR;

void GoPID(Qtr qtr, Drive drive);
void CenterPID(Qtr qtr, Drive drive);
void TurnR(Drive drive);
void TurnL(Drive drive);
void TurnU(Drive drive);

#pragma once
