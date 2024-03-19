
#include <Arduino.h>
#include "../config/pins.h"
class Drive
{
public:
    Drive();
    int Begin();
    int Stop();
    int Encored(int rC, int lC);
    int Go(int r, int l);
    volatile int tickR;
    volatile int tickL;
    static Drive *_instance;
    static void countr();
    static void countl();
};

void OR(int R, uint8_t E1, uint8_t E2);
void OL(int L, uint8_t E3, uint8_t E4);