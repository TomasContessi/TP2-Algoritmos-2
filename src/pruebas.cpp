#include <iostream>
#include <string>



#include "carta.hpp"
#include "jugador.hpp"

// para facilitar el debuggeo, pero despues se sacan y se compila solo el directorio
//#include "carta.cpp"
//#include "jugador.cpp"


using namespace std;


int main(){
    jugador* p1=new jugador("player_1");
    carta* c1 = new carta(p1->getName(),misil);
    unsigned int pos [] ={1,2,3};
    CardStats st,st2;

    c1->setPos(pos);

    p1->agregarCarta(c1);

    c1 = new carta(p1->getName(),avion);
    
    unsigned int pos2 []={0,0,1};
    c1->setPos(pos2);

    p1->agregarCarta(c1);

    st=p1->getCardStats(pos);
    st2=p1->getCardStats(pos2);



    st= c1->getStats();

    st.alcance=27;

    delete p1;

    return 0;
}