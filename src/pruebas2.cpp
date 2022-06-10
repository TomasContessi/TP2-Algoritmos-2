// cambie a usar este archivo para las pruebas para no perder el otro que andaba

#include <iostream>
#include <string>
#include <cstdlib>


#include "carta.hpp"
#include "jugador.hpp"
#include "ronda.hpp"
#include "casilla.hpp"
#include "mapa.hpp"
#include "graficador.hpp"
#include "gameConfig.hpp"
#include "batallaCampal.hpp"


#include "EasyBMP.h"

using namespace std;

int main(){
    batallaCampal * juego;

    cout << "iniciando" << endl;
    juego=new batallaCampal();

    juego->iniciarPartida();

    while (juego->getState() == jugando)
    {
        juego->ejecutarTurno();
    }
    cout << "terminado" << endl;

    delete juego;
    return 0;
}