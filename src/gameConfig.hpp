#ifndef GAME_CONFIG_H
#define GAME_CONFIG_H

#include <string>

#include "mapa.hpp"

//---------------------------------------------------------------------------------------------------------------------
//                                   CONTESSI TOMAS 99199 ALORITMOS Y PROGRAMACION II
//---------------------------------------------------------------------------------------------------------------------
//-----------------------------------------------BATALLA CAMPAL 2 V2.2-------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------
//                                        DEFINICION DE LA CLASE GAME CONFIG
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
    //pos:
    void loadConfig(std::string);

    //pre:
    //pos:
    int getPlayerNumber();

    //pre:
    //pos:
    int getTroopsNumber();

    //pre:
    //pos:
    std::vector<int> getDimXYZ ();

    //pre:
    //pos:
    TipoMapa_T getMapType();

    //pre:
    //pos:
    std::vector<std::string> getPlayerNames();

    //pre:
    //pos:
    std::string getGraficsPath();

    //pre:
    //pos:
    std::string getOutPath();

    //pre:
    //pos:
    std::string getLanguage();
};




#endif /* GAME_CONFIG_H*/