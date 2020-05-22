#pragma once
#include "Pion.h"

class Krol: public Pion{

    public:
    Krol() : Pion(){}
    Krol(int _posX, int _posY, bool _COLORSWAP);
    Krol(int _posX, int _posY, bool _czyBialy, bool _COLORSWAP);
    void setColor(bool _czyBialy);
    std::vector<std::string> mozliweRuchy();
};