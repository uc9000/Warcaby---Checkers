#include "Pion.h"

Pion::Pion(int _posX, int _posY, bool _COLORSWAP): COLORSWAP(_COLORSWAP){
    setPos(_posX, _posY);
}

Pion::Pion(int _posX, int _posY, bool _czyBialy, bool _COLORSWAP): COLORSWAP(_COLORSWAP){
    setPos(_posX, _posY);
    setColor(_czyBialy);
}

void Pion::setPos(int _posX, int _posY){
    if(_posX > 7 || _posX < 0 || _posY > 7 || _posY < 0){
        std::stringstream warning;
        warning << "Error: wyjście poza warcabnice: posX = " << _posX << " posY = " << _posY;
        throw std::invalid_argument(warning.str());
    }
    posX = (short unsigned int)_posX;
    posY = (short unsigned int)_posY;
}

void Pion::setPos(const std::string& _pos){
    setPos(getPosX(_pos),getPosX(_pos));
}

void Pion::setColor(bool _czyBialy){
    czyBialy = _czyBialy;
    if((!czyBialy && COLORSWAP) || (czyBialy && !COLORSWAP)){
        unicode = u8"\u2657";
    }
    else{
        unicode = u8"\u265F";
    }
}

short unsigned int Pion::getPosX(const std::string& _pos) const{
    if(_pos.length() > 2){
        std::stringstream warning;
        warning << "Error: wyjście poza warcabnice: string za dlugi";
        throw std::invalid_argument(warning.str());
    }
    const char alpha[] = "ABCDEFGH";
    for(int i = 0; i < 8; ++i){
        if(_pos[0] == alpha[i]){
            return i;
        }
    }
    throw std::invalid_argument("Error: wyjście poza warcabnice: X");
    return -1;       
}

short unsigned int Pion::getPosY(const std::string& _pos) const{
    if(_pos.length() > 2){
        std::stringstream warning;
        warning << "Error: wyjście poza warcabnice: string za dlugi" << std::endl;
        throw std::invalid_argument(warning.str());
    }
    const char nums[] = "12345678";
    for(int i = 0; i < 8; ++i){
        if(_pos[1] == nums[i]){
            return i;
        }
    }
    throw std::invalid_argument("Error: wyjście poza warcabnice: Y");
    return -1;
}

short unsigned int Pion::getPosX() const{
    return posX;
}

short unsigned int Pion::getPosY() const{
    return posY;
}

std::string Pion::getPos() {
    return getPos(posX, posY);
}

std::string Pion::getPos(int _posX, int _posY) {
    if(_posX > 7 || _posX < 0 || _posY > 7 || _posY < 0){
        throw std::out_of_range("Error: wyjście poza warcabnice: getPos()");
    }
    const char alpha[] = "ABCDEFGH";
    std::stringstream ss;
    ss << alpha[_posX] << _posY + 1;
    return ss.str();
}

bool Pion::getCzyBialy() const{
    return czyBialy;
}

const char* Pion::getUnicode() const{
    return unicode;
}

std::vector<std::string> Pion::mozliweRuchy(){
    std::vector<std::string> ruchy;
    short int tmp = 1;
    if(!czyBialy){
        tmp = -1;
    }
    for( ; abs(tmp) <= 2; tmp *= 2){
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

std::ostream& operator << (std::ostream& os, const Pion& p){
    os << p.getUnicode();
    return os;
}

std::istream& operator >> (std::istream& is, Pion& p){
    std::string pos;
    is >> pos;
    p.setPos(pos);
    return is;
}