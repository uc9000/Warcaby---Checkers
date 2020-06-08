#include "Warcaby.h"

Warcaby::Warcaby(){
    #ifndef _WIN32
    setlocale(LC_CTYPE, "Polish");
    #endif
    #ifdef _WIN32 
    SetConsoleOutputCP(65001);
    #endif
    gracze[0].setCzyBialy(true);
    gracze[1].setCzyBialy(false);        
}

void Warcaby::start(){
    bool czyBialy;
    bool remis = false;
    bool wygranaBialych;        
    war.initBoard();
    for(int ruch = 0; ; ++ruch){
        czyBialy = gracze[ruch % 2].getCzyBialy();
        war.print(czyBialy);
        std::vector<std::string> ruchy = std::vector<std::string>(war.wszystkieMozliweRuchy(czyBialy));
        if(ruchy.size() == 0){
            remis = true;
            break;
        }
        std::string decyzja = std::string(gracze[ruch % 2].decyzja( ruchy ));
        if(decyzja.compare("-q") == 0){
            if(gracze[ruch % 2].getCzyBialy()){
                wygranaBialych = false;
            }
            else{
                wygranaBialych = true;
            }
            break;
        }
        war.przesunPiona( decyzja );
        if(war.ilePionow(true) == 0){
            wygranaBialych = false;
            break;
        }
        if(war.ilePionow(false) == 0){
            wygranaBialych = true;
            break;
        }
    }
    using namespace std;
    // Wyniki
    if(remis){
        cout << "Remis! - pat" << endl;
    }
    else if(wygranaBialych){
        cout << "Wygrana gracza " << gracze[0] << endl;
    }
    else{
        cout << "Wygrana gracza " << gracze[1] << endl;
    }
}

void Warcaby::menu(){
    using namespace std;
    int w = 0, w2 = 0;
    std::string nazwa;
    cout << "Witoj w terminalowych warcabach angielskich! \nWybierz jedną z opcji:" << endl;
    while(true){
        switch(w){
            case 0:
            cout << endl << "1) Rozpocznij nową grę" << endl
            << "2) Ustaw nazwy graczy" << endl
            << "3) Zakończ" << endl;
            while(true){
                cin >> w;
                if(cin.good() && w > 0 && w <= 3){
                    break;
                }
                cout << "Podaj liczbe od 1 do " << 3 << "!"<< endl;
                cin.clear();
                cin.ignore(1024, '\n');
            }                
            break;

            case 1:
            try { start(); }
            catch (invalid_argument& e){
                cerr << e.what() << endl <<
                "Koniec rozgrywki." << endl;
            }
            w = 0;
            break;

            case 2:
            cout << endl << "Zmień nazwę gracza z:" << endl
            << "1) Białymi pionami (aktualna nazwa: " << gracze[0]<< ")" << endl
            << "2) Czarnymi pionami (aktualna nazwa: " << gracze[1]<< ")" << endl;
            while(true){
                cin >> w2;
                if(cin.good() && w2 > 0 && w2 <= 2){
                    break;
                }
                cout << "Podaj liczbe od 1 do " << 2 << "!"<< endl;
                cin.clear();
                cin.ignore(1024, '\n');
            }
            cin.clear();
            cin.ignore(1024, '\n');
            cout << "Podaj nową nazwę:" << endl;
            std::getline(std::cin, nazwa);                              
            gracze[w2 - 1].setNazwa(nazwa);
            nazwa = std::string();
            w = 0;
            break;

            case 3:
            return;                               
        }
    }
}