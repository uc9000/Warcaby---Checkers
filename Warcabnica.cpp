#include "Warcabnica.h"

void Warcabnica::skan(){
    for(int i = 0; i < 64; ++i){
        if(pola1D[i] != -1){
            pola1D[i] = 0;
        }
    }
    for(short unsigned int i = 0; i < piony.size(); ++i){
        pola[piony[i]->getPosX()][piony[i]->getPosY()] = i + 1;
    }
}

void Warcabnica::readConfig(){
    std::string line;
    std::ifstream file("warcaby.config");
    if(!file.is_open()){
        throw std::runtime_error("Brak pliku warcaby.config!");
    }
    COLORSWAP = false;
    while(std::getline(file, line)){
        if(line.compare("COLORSWAP=TRUE") == 0){
            COLORSWAP = true;
        }
    }
}

Warcabnica::Warcabnica(std::vector<std::unique_ptr<Pion>>& _piony): piony(_piony) {
    pola1D = new short int[64]; //tablica 2D w jednym bloku pamięci
    pola = new short int*[8];
    for(int i = 0; i < 8; ++i){
        pola[i] = pola1D + i * 8;
    }
    readConfig();
}

Warcabnica::~Warcabnica(){
    delete[] pola1D;
    delete[] pola;
}

std::vector<std::string> Warcabnica::wszystkieMozliweRuchy(bool czyBialy){   
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

void Warcabnica::usunPiona(short int posX, short int posY){
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

void Warcabnica::promocjaPiona(unsigned int index){
    std::unique_ptr<Pion> k(new Krol(piony[index]->getPosX(), piony[index]->getPosY(), piony[index]->getCzyBialy()));
    piony[index] = std::move(k);
}

void Warcabnica::przesunPiona(short int fromX, short int fromY, short int toX, short int toY){
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

void Warcabnica::przesunPiona(std::string ruch){
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

void Warcabnica::initBoard(){ //rozstawienie pionów do pozycji początkowej
    piony.clear();
    for(int i = 0; i < 64; ++i){
        pola1D[i] = -1;
    }
    for(int i = 0; i < 8; ++i){
        for(int j = 0; j < 8; ++j){
            if((j%2 + i%2)%2 == 0){
                if(i < 3){
                    std::unique_ptr<Pion> p(new Pion(j, i, true, COLORSWAP));
                    piony.push_back(move(p));
                    pola[j][i] = piony.size();
                }
                else if(i >= 5){
                    std::unique_ptr<Pion> p(new Pion(j, i, false, COLORSWAP));
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

void Warcabnica::print(bool czyBialy){
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
                    cout << *piony[pola[j][i] - 1] << " ";
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
                cout << *piony[pola[j][i] - 1] << " ";
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

unsigned int Warcabnica::ilePionow(bool czyBialy){
    unsigned int ile = 0;
    for(auto& p: piony){
        if(p->getCzyBialy() == czyBialy){
            ++ile;
        }
    }
    return ile;
}