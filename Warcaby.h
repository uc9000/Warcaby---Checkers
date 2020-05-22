#pragma once
#include "Warcabnica.h"

class Warcaby{
    private:
    std::vector<std::unique_ptr<Pion>> piony;
    Gracz gracze[2];
    Warcabnica war = Warcabnica(piony);

    public:    
    Warcaby();
    void start();
    void menu();
};