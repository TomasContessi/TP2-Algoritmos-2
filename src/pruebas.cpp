#include <iostream>
#include <string>



#include "carta.h"
#include "jugador.h"

// para facilitar el debuggeo, pero despues se sacan y se compila solo el directorio
#include "carta.cpp"
#include "jugador.cpp"


using namespace std;


int main(){
    jugador* p1=new jugador("player_1");

    p1->agregarCarta(new carta(p1,misil));

    cout<<p1->getName()<<endl;

    delete p1;

    return 0;
}