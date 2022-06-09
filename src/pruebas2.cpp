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
    juego=new batallaCampal();

    juego->iniciarPartida();

    delete juego;
    return 0;
}