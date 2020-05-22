#pragma once
#include <stdexcept>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>

class Pion{
    protected:
    const bool COLORSWAP;
    bool czyBialy;
    const char* unicode;
    short unsigned int posX, posY;
    
    public:
    Pion(): COLORSWAP(false){ }
    Pion(int _posX, int _posY, bool _COLORSWAP);
    Pion(int _posX, int _posY, bool _czyBialy, bool _COLORSWAP);
    void setPos(int _posX, int _posY);
    void setPos(const std::string& _pos);
    virtual void setColor(bool _czyBialy);
    short unsigned int getPosX(const std::string& _pos) const;
    short unsigned int getPosY(const std::string& _pos) const;
    short unsigned int getPosX() const;
    short unsigned int getPosY() const;
    std::string getPos();
    std::string getPos(int _posX, int _posY);
    bool getCzyBialy() const;
    const char* getUnicode() const;
    virtual std::vector<std::string> mozliweRuchy();
    friend std::ostream& operator << (std::ostream& os, const Pion& p);
    friend std::istream& operator >> (std::istream& is, Pion& p);
};