#pragma once
#include <memory>
#include "Gracz.h"
#include "Pion.h"
#include "Krol.h"


class Warcabnica{
    private:
    bool COLORSWAP;
    short int* pola1D;
    short int** pola; // tablica 2D przyjmuje wartości: -1 dla niedostępnego pola, 0 gdy pole jest puste, ID piona/króla (index vectora + 1)    
    std::vector<std::unique_ptr<Pion>>& piony;
    void skan();
    void readConfig();

    public:
    Warcabnica(std::vector<std::unique_ptr<Pion>>& _piony);
    ~Warcabnica();
    std::vector<std::string> wszystkieMozliweRuchy(bool czyBialy);
    void usunPiona(short int posX, short int posY);
    void promocjaPiona(unsigned int index);
    void przesunPiona(short int fromX, short int fromY, short int toX, short int toY);
    void przesunPiona(std::string ruch);
    void initBoard(); //rozstawienie pionów do pozycji początkowej
    void print(bool czyBialy);
    unsigned int ilePionow(bool czyBialy);
};