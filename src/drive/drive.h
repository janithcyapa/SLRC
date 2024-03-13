
class Drive
{
public:
    int Setup();
    int Stop();
    int Go(int r, int l);
    Drive();
};

void OR(int R, uint8_t E1, uint8_t E2);
void OL(int L, uint8_t E3, uint8_t E4);
