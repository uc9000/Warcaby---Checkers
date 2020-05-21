#include <sstream>
#include <memory>
#include "Gracz.h"
#include "Pion.h"
#include "Krol.h"


class Warcabnica{
    private:
    short int* pola1D;
    short int** pola; // tablica 2D przyjmuje wartości: -1 dla niedostępnego pola, 0 gdy pole jest puste, ID piona/króla (index vectora + 1)    
    std::vector<std::unique_ptr<Pion>>& piony;

    void skan(){
        for(int i = 0; i < 64; ++i){
            if(pola1D[i] != -1){
                pola1D[i] = 0;
            }
        }
        for(short unsigned int i = 0; i < piony.size(); ++i){
            pola[piony[i]->getPosX()][piony[i]->getPosY()] = i + 1;
        }
    }

    public:
    Warcabnica(std::vector<std::unique_ptr<Pion>>& _piony): piony(_piony) {
        pola1D = new short int[64]; //tablica 2D w jednym bloku pamięci
        pola = new short int*[8];
        for(int i = 0; i < 8; ++i){
            pola[i] = pola1D + i * 8;
        }
    }

    ~Warcabnica(){
        delete[] pola1D;
        delete[] pola;
    }

    std::vector<std::string> wszystkieMozliweRuchy(bool czyBialy){   
        std::vector<std::string> wszystkieRuchy;     
        short unsigned int x, y;
        bool bicie = false;
        for(auto& p: piony){
            if(p->getCzyBialy() != czyBialy){
                continue;
            }            
            std::vector<std::string> ruchyDlaPiona;
            std::vector<std::string> tmp;          
            ruchyDlaPiona = std::vector<std::string>(p->mozliweRuchy());
            // tylko dla bicia
            for(unsigned int i = 0; i < ruchyDlaPiona.size(); ++i){
                x = p->getPosX(ruchyDlaPiona[i]);
                y = p->getPosY(ruchyDlaPiona[i]);
                if(pola[x][y] == 0 
                &&  ( (x == p->getPosX() + 2) || (x == p->getPosX() - 2) )
                && pola[ ( x + p->getPosX() ) / 2] [ ( y + p->getPosY() ) / 2] > 0){
                    if(piony[pola[ ( x + p->getPosX() ) / 2] [ ( y + p->getPosY() ) / 2] - 1]->getCzyBialy() != p->getCzyBialy()){
                        //std::cout << piony[pola[ ( x + p->getPosX() ) / 2] [ ( y + p->getPosY() ) / 2] - 1]->getPos() << std::endl;
                        tmp.push_back(ruchyDlaPiona[i]);
                        bicie = true;
                    }
                }
            }
            for(auto a: tmp){
                std::stringstream ss;
                ss << p->getPos() << " " << a;
                wszystkieRuchy.push_back(ss.str());
            }
        }
        // dla "normalnych" ruchow jeśli nie było bicia

        if(!bicie){
            for(auto& p: piony){
                if(p->getCzyBialy() != czyBialy){
                    continue;
                }            
                std::vector<std::string> ruchyDlaPiona;
                std::vector<std::string> tmp;          
                ruchyDlaPiona = std::vector<std::string>(p->mozliweRuchy());            
                for(unsigned int i = 0; i < ruchyDlaPiona.size(); ++i){
                    x = p->getPosX(ruchyDlaPiona[i]);
                    y = p->getPosY(ruchyDlaPiona[i]);
                    if((x == p->getPosX() + 1 || x == p->getPosX() - 1) && (pola[x][y] == 0)){
                        tmp.push_back(ruchyDlaPiona[i]);
                    }
                }
                for(auto a: tmp){
                    std::stringstream ss;
                    ss << p->getPos() << " " << a;
                    wszystkieRuchy.push_back(ss.str());
                }
            }
        }
        return wszystkieRuchy;
    }

    void usunPiona(short int posX, short int posY){
        if(pola[posX][posY] > 0){
            piony.erase(piony.begin() + pola[posX][posY] - 1);
            pola[posX][posY] = 0;
            skan();
            return;
        }
        std::stringstream ss;
        ss << "Error: nie można usunąć piona z tego pola: X = " << posX << " Y = " << posY;
        throw std::invalid_argument(ss.str());        
    }

    void promocjaPiona(unsigned int index){
        std::unique_ptr<Pion> k(new Krol(piony[index]->getPosX(), piony[index]->getPosY(), piony[index]->getCzyBialy()));
        piony[index] = std::move(k);
    }

    void przesunPiona(short int fromX, short int fromY, short int toX, short int toY){
        if(toY == 7 && piony[pola[fromX][fromY] - 1]->getCzyBialy()){
            promocjaPiona(pola[fromX][fromY] - 1);
        }
        if(toY == 0 && !piony[pola[fromX][fromY] - 1]->getCzyBialy()){
            promocjaPiona(pola[fromX][fromY] - 1);
        }
        piony[pola[fromX][fromY] - 1]->setPos(toX, toY);
        if(abs(fromX - toX) == 2){ // bicie
            usunPiona((fromX + toX) / 2 , (fromY + toY) / 2);
        }else{
            skan();
        }
        
    }

    void przesunPiona(std::string ruch){
        if(ruch.size() > 5){
            throw std::out_of_range("Error: string za dlugi w przesunPiona()");
        }
        std::stringstream ss(ruch);
        std::string from, to;
        ss >> from;
        ss >> to;
        short int fromX, fromY, toX, toY;
        fromX = piony[0]->getPosX(from);
        fromY = piony[0]->getPosY(from);
        toX = piony[0]->getPosX(to);
        toY = piony[0]->getPosY(to);
        przesunPiona(fromX, fromY, toX, toY);
    }

    void initBoard(){ //rozstawienie pionów do pozycji początkowej
        for(int i = 0; i < 64; ++i){
            pola1D[i] = -1;
        }
        for(int i = 0; i < 8; ++i){
            for(int j = 0; j < 8; ++j){
                if((j%2 + i%2)%2 == 0){
                    if(i < 3){
                        std::unique_ptr<Pion> p(new Pion(j, i, true));
                        piony.push_back(move(p));
                        pola[j][i] = piony.size();
                    }
                    else if(i >= 5){
                        std::unique_ptr<Pion> p(new Pion(j, i, false));
                        piony.push_back(move(p));
                        pola[j][i] = piony.size();
                    }
                    else{
                        pola[j][i] = 0;
                    }
                }
            }
        }
    }

    void print(bool czyBialy){
        using namespace std;
        char alpha[] = "ABCDEFGH";
        if(czyBialy){
            for(int i = 7; i >= 0; --i){
                for(int j = 0; j < 8; ++j){
                    if(pola[j][i] == -1){
                        cout << "# ";//u8"  \u25A1";
                    }
                    else if(pola[j][i] == 0){
                        cout << "  ";//u8"  \u25A1";
                    }
                    else{
                        cout << piony[pola[j][i] - 1]->getUnicode() << " ";
                    }
                }
                cout << "| " << i + 1 << endl;
            }
            for(int i = 0; i < 8; ++i){
                cout << "-|";
            }
            cout << endl;
            for(int i = 0; i < 8; ++i){
                cout << alpha[i] << " ";
            }
            cout << endl;
            return;
        }
        for(int i = 0; i < 8; ++i){
            for(int j = 7; j >= 0; --j){
                if(pola[j][i] == -1){
                    cout << "# ";//u8"  \u25A1";
                }
                else if(pola[j][i] == 0){
                    cout << "  ";//u8"  \u25A1";
                }
                else{
                    cout << piony[pola[j][i] - 1]->getUnicode() << " ";
                }
            }
            cout << "| " << i + 1 << endl;
        }
        for(int i = 7; i >= 0; --i){
            cout << "-|";
        }
        cout << endl;
        for(int i = 7; i >= 0; --i){
            cout << alpha[i] << " ";
        }
        cout << endl;
    }

    unsigned int ilePionow(bool czyBialy){
        unsigned int ile = 0;
        for(auto& p: piony){
            if(p->getCzyBialy() == czyBialy){
                ++ile;
            }
        }
        return ile;
    }
};

class Warcaby{
    private:
    std::vector<std::unique_ptr<Pion>> piony;
    Gracz gracze[2];

    public:
    Warcabnica war = Warcabnica(piony);
    Warcaby(){
        setlocale(LC_CTYPE, "Polish");
        gracze[0].setCzyBialy(true);
        gracze[1].setCzyBialy(false);        
    }

    void start(){
        bool czyBialy;
        bool remis = false;
        bool wygranaBialych;
        std::string decyzja;
        war.initBoard();
        for(int ruch = 0; ; ++ruch){
            czyBialy = gracze[ruch % 2].getCzyBialy();
            war.print(czyBialy);
            std::vector<std::string> ruchy = std::vector<std::string>(war.wszystkieMozliweRuchy(czyBialy));
            if(ruchy.size() == 0){
                remis = true;
                break;
            }
            decyzja = std::string(gracze[ruch % 2].decyzja( ruchy ));
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
};


int main(){
    using namespace std;
    Warcaby w;
    w.start();
    //w.warcabnica.test();
}