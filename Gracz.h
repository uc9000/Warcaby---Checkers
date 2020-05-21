#pragma once
#include <iostream>
#include <string>
#include <vector>

class Gracz{
    private:
    std::string nazwa;
    bool czyBialy;

    public:
    Gracz(){}
    Gracz(std::string _nazwa){
        setNazwa(_nazwa);
    }

    Gracz(bool _czyBialy){
        setCzyBialy(_czyBialy);
    }

    void setNazwa(std::string& _nazwa){
        nazwa = _nazwa;
        if(nazwa.length() > 30)
            nazwa.erase(_nazwa.begin() + 30, _nazwa.end()); //ograniczenie dlugosci nazwy do 30 znakow        
    }

    std::string getNazwa() const{ return nazwa; }

    void setCzyBialy(bool _czyBialy){
        czyBialy = _czyBialy;
        if(nazwa.size() == 0){
            if(_czyBialy)
                nazwa = "Białe";
            if(!_czyBialy)
                nazwa = "Czarne";
        }
    }

    bool getCzyBialy() const{
        return czyBialy;
    }

    std::string decyzja(std::vector<std::string> ruchy){        
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

    friend std::ostream& operator << (std::ostream& os, Gracz& g){
        os << g.getNazwa();
        return os;
    }
};