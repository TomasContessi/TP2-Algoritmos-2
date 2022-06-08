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


#include "EasyBMP.h"

using namespace std;

int main(){
gameConfig* config;
mapa* map;
ronda* rondita;
graficador* printer;


config = new gameConfig;
map = new mapa(config->getMapType(),config->getDimXYZ());
rondita = new ronda ();
printer = new graficador(map,rondita);

rondita->agregarJugador(new jugador(config->getPlayerNames()[0]));
rondita->agregarJugador(new jugador(config->getPlayerNames()[1]));

printer->cargarMapa(map,rondita);

printer->selecRutaGraficas(config->getGraficsPath());
printer->cargarGraficas();
printer->selecRutaSalida(config->getOutPath());

printer->enmascarar(true);

printer->graficarPantalla(config->getPlayerNames()[0]);

cout<<"ok"<<endl;

}