#include "Krol.h"

Krol::Krol(int _posX, int _posY, bool _COLORSWAP) : Pion::Pion(_posX, _posY, _COLORSWAP){}

Krol::Krol(int _posX, int _posY, bool _czyBialy, bool _COLORSWAP) : Pion::Pion(_posX, _posY, _COLORSWAP){
    setColor(_czyBialy);
}

void Krol::setColor(bool _czyBialy){
    czyBialy = _czyBialy;
    if((!czyBialy && COLORSWAP) || (czyBialy && !COLORSWAP)){
        unicode = u8"\u2654";
    }
    else{
        unicode = u8"\u265A";
    }
}

std::vector<std::string> Krol::mozliweRuchy(){
    std::vector<std::string> ruchy;
    for(short int tmp = -2; tmp <= 2; ++tmp){
        for(short int i = -2; i <= 2; ++i){
            if (i == 0 || tmp == 0){
                continue;
            }
            if((posY + tmp < 8) && (posY + tmp >=0)){ // o tmp do przodu
                if(posX + i >= 0 && posX + i < 8){ // o i w prawo
                    ruchy.push_back(getPos(posX + i, posY + tmp));
                }
            }
        }
    }
    return ruchy;
}