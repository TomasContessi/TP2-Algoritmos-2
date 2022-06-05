#ifndef GAME_CONFIG_H
#define GAME_CONFIG_H

#include <string>

#include "mapa.h"


class gameConfig
{
private:
    int nJugadores; // cantidad de jugadores
    int nCasillas [3]; // dimension del tablero
    int nSoldados; //cantidad de soldados por jugador
    TipoMapa_T tipoMapa; // en cual de los mapas jugar
    int nCartasIniciales; // cantidad de cartas inicial por jugador
    std::string *nombres; // los nombres de los jugadores
public:
    gameConfig(/* args */);
    ~gameConfig();
};

gameConfig::gameConfig(/* args */)
{
}

gameConfig::~gameConfig()
{
}


#endif /* GAME_CONFIG_H*/