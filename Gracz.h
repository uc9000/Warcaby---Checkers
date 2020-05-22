#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

class Gracz{
    private:
    std::string nazwa;
    bool czyBialy;

    public:
    Gracz(){};
    Gracz(std::string _nazwa);
    Gracz(bool _czyBialy);
    void setNazwa(const std::string& _nazwa);
    std::string getNazwa() const;
    void setCzyBialy(bool _czyBialy);
    bool getCzyBialy() const;
    std::string decyzja(const std::vector<std::string>& ruchy);
    friend std::ostream& operator << (std::ostream& os, const Gracz& g);
};