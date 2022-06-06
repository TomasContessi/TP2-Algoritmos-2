#include <iostream>
#include <string>
#include <cstdlib>


#include "carta.hpp"
#include "jugador.hpp"
#include "ronda.hpp"
#include "casilla.hpp"


using namespace std;


int main(){
    ronda* rondita;

    unsigned int pos[3];
    rondita= new ronda;
    
    rondita->agregarJugador(new jugador("player_1"));
    rondita->agregarJugador(new jugador("player_2"));
    rondita->agregarJugador(new jugador("player_3"));

    rondita->iniciarRonda();

    for (int i = 0; i < 8; i++)
    {
        pos[0]=i;
        pos[1]=i;
        pos[2]=i;

        rondita->tomarCarta(TiposCarta_T (i));
        rondita->jugarCarta(pos);
        cout<<rondita->getJugadorEnTurno()<<endl;
        cout<<rondita->getCardType(pos)<<endl;
        rondita->avanzarTurno();
    }

    rondita->iniciarRonda();
    pos[0]=0;
    pos[1]=0;
    pos[2]=0;

    cout<<rondita->getCardType(pos)<<endl;
    
    delete rondita;

    return 0;
}