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
    
    CardStats st;

    st= c1->getStats();

    st.alcance=27;

    delete p1;

    delete c1;

    return 0;
}