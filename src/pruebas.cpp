#include <iostream>
#include <string>
#include <cstdlib>


#include "carta.hpp"
#include "jugador.hpp"

// para facilitar el debuggeo, pero despues se sacan y se compila solo el directorio
//#include "carta.cpp"
//#include "jugador.cpp"


using namespace std;


int main(){

    TiposCarta_T var;
    srand(time(NULL));

    for (int i = 0; i < 10; i++)
    {
        //cout<< rand() % 10<<endl;
        var=TiposCarta_T (rand() % (LAST_CARD_TYPE + 1));
        cout<<var<<endl;
    }

    var=misil;
    cout<<var<<endl;
    var=LAST_CARD_TYPE;
    cout<<var<<endl;

    return 0;
}