#ifndef GAME_CONFIG_H
#define GAME_CONFIG_H

#include <string>
#include <sstream>
#include <fstream>
#include <iostream>


#include "mapa.hpp"

//---------------------------------------------------------------------------------------------------------------------
//                                   CONTESSI TOMAS 99199 ALORITMOS Y PROGRAMACION II
//---------------------------------------------------------------------------------------------------------------------
//--------------------------------------------      BATALLA CAMPAL 2      ---------------------------------------------
//---------------------------------------------------------------------------------------------------------------------
//                                       DEFINICION DE LA CLASE GAME CONFIG V2.3
//---------------------------------------------------------------------------------------------------------------------

// si tengo tiempo implemento que se pueda cambiar la configuracion desde el programa y guardarla

class gameConfig
{
private:
    int nJugadores; // cantidad de jugadores
    std::vector<int> nCasillas; // dimension del tablero
    int nSoldados; //cantidad de soldados por jugador
    TipoMapa_T tipoMapa; // en cual de los mapas jugar
    std::vector<std::string>nombres; // los nombres de los jugadores
    std::string rutaGraficas;
    std::string rutaTableros;
    std::string rutaConfig;
    std::string idioma;

public:

    //pre:
    //pos:
    gameConfig();

    //pre:
    //pos:
    ~gameConfig();

    //pre:
    //pos: carga la configuracion desde el path pasado como argumento
    void loadConfig(std::string);

    //pre:
    //pos: devuelve el numero de jugadores
    int getPlayerNumber();

    //pre:
    //pos: devuelve la cantidad de tropas
    int getTroopsNumber();

    //pre:
    //pos: devuelve la dimension del mapa
    std::vector<int> getDimXYZ ();

    //pre:
    //pos: devuelve el tipo de mapa
    TipoMapa_T getMapType();

    //pre:
    //pos: devuelve los nombres de los jugadores
    std::vector<std::string> getPlayerNames();

    //pre:
    //pos: devuelve el path para las graficas
    std::string getGraficsPath();

    //pre:
    //pos: devuelve el path de salida de los tableros
    std::string getOutPath();

    //pre:
    //pos: devuelve el lengueje del juego
    std::string getLanguage();
};




#endif /* GAME_CONFIG_H*/