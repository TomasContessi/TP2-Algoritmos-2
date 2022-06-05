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
    carta* c1 = new carta("player_2",misil);

    unsigned int arr [3];
    unsigned int * ptr = NULL;

    p1->agregarCarta(new carta(p1->getName(),misil));
    p1->agregarCarta(new carta(p1->getName(),avion));

    cout<<p1->getName()<<endl;
    cout<<p1->contarCartas(misil)<<endl;

    cout<<sizeof(c1->getPos())<<endl;

    int size=0;

    size=sizeof(arr)/sizeof(arr[0]);
    cout<<size<<endl;

    ptr=c1->getPos();
    size=sizeof(ptr)/sizeof(ptr[0]);
    cout<<size<<endl;

    for (int i = 0; i < 3; i++)
    {
        cout<<ptr[i]<<endl;
    }
    
    

    delete p1;

    delete c1;

    return 0;
}