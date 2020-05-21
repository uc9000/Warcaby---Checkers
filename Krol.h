#pragma once
#include "Pion.h"

class Krol: public Pion{

    public:
    Krol() : Pion(){}       
    
    Krol(int _posX, int _posY) : Pion(_posX, _posY){}

    Krol(int _posX, int _posY, bool _czyBialy) : Pion(_posX, _posY){
        setColor(_czyBialy);
    }

    void setColor(bool _czyBialy){
        czyBialy = _czyBialy;
        if((!czyBialy && COLORSWAP) || (czyBialy && !COLORSWAP)){
            unicode = u8"\u2654";
        }
        else{
            unicode = u8"\u265A";
        }
    }

    std::vector<std::string> mozliweRuchy(){
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
};