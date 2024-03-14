
#include <Arduino.h>
#include "../config/pins.h"
class Drive
{
public:
    int Begin();
    int Stop();
    int Go(int r, int l);
    Drive();
};

void OR(int R, uint8_t E1, uint8_t E2);
void OL(int L, uint8_t E3, uint8_t E4);
