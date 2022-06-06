#include <iostream>
#include <string>
#include <cstdlib>


#include "carta.hpp"
#include "jugador.hpp"
#include "ronda.hpp"

// para facilitar el debuggeo, pero despues se sacan y se compila solo el directorio
//#include "carta.cpp"
//#include "jugador.cpp"


using namespace std;


int main(){
    ronda* rondita;

    rondita= new ronda;
    
    rondita->agregarJugador(new jugador("player_1"));
    rondita->agregarJugador(new jugador("player_2"));
    rondita->agregarJugador(new jugador("player_3"));

    rondita->iniciarRonda();

    for (int i = 0; i < 4; i++)
    {
        cout<<rondita->getJugadorEnTurno()<<endl;
        rondita->avanzarTurno();
    }
    
    delete rondita;

    return 0;
}