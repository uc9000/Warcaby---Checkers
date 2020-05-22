#include "Gracz.h"

Gracz::Gracz(std::string _nazwa){
    setNazwa(_nazwa);
}

Gracz::Gracz(bool _czyBialy){
    setCzyBialy(_czyBialy);
}

void Gracz::setNazwa(const std::string& _nazwa){
    nazwa = std::string(_nazwa);
    if(nazwa.length() > 30)
        nazwa.erase(nazwa.begin() + 30, nazwa.end()); //ograniczenie dlugosci nazwy do 30 znakow        
}

std::string Gracz::getNazwa() const{ return nazwa; }

void Gracz::setCzyBialy(bool _czyBialy){
    czyBialy = _czyBialy;
    if(nazwa.size() == 0){
        if(_czyBialy)
            nazwa = "Białe";
        if(!_czyBialy)
            nazwa = "Czarne";
    }
}

bool Gracz::getCzyBialy() const{
    return czyBialy;
}

std::string Gracz::decyzja(const std::vector<std::string>& ruchy){        
    using namespace std;        
    if(ruchy.size() == 0){
        throw invalid_argument("Brak dostepnych ruchów!");
    }
    int i, wybor;
    cout << "Ruch gracza " << nazwa << endl;
    for(i = 0; i < (int)ruchy.size(); ++i){
        cout << i + 1 << ". " << ruchy[i] << endl;
    }
    cout << i + 1 << ". " << "Poddaj sie" << endl;
    while(true){
        cin >> wybor;
        if(cin.good() && wybor > 0 && wybor <= i + 1){
            break;
        }
        cout << "Podaj liczbe od 1 do " << i + 1 << "!"<< endl;
        cin.clear();
        cin.ignore(1024, '\n');
    }
    if(wybor == i + 1){
        return "-q";
    }
    return ruchy[wybor - 1];
}

std::ostream& operator << (std::ostream& os, const Gracz& g){
    os << g.getNazwa();
    return os;
}