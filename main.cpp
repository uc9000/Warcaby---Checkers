#include "Warcaby.h"

int main(){
    using namespace std;
    try{
        Warcaby w;
        w.menu();
    }
    catch(runtime_error& e){
        cout << e.what() << endl;
    }
    catch(exception& e){
        cout << "Cos sie popsulo :(" << endl;
    }
}