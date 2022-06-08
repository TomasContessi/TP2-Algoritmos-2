#include "gameConfig.hpp"

//---------------------------------------------------------------------------------------------------------------------
//                                   CONTESSI TOMAS 99199 ALORITMOS Y PROGRAMACION II
//---------------------------------------------------------------------------------------------------------------------
//-----------------------------------------------BATALLA CAMPAL 2 V2.2-------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------
//                                          METODOS DE LA CLASE GAME CONFIG
//---------------------------------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------------------------------
//                                              CONSTRUCTOR Y DESTRUCTOR
//---------------------------------------------------------------------------------------------------------------------

gameConfig::gameConfig()
{
    std::string defaultPath ="../config/default_config";
    this->loadConfig(defaultPath);
}

gameConfig::~gameConfig()
{
}

//---------------------------------------------------------------------------------------------------------------------
//                                              CARGA DE CONFIGURACION
//---------------------------------------------------------------------------------------------------------------------

void gameConfig::loadConfig(std::string path){ // por ahora esta hardcodeado hasta que aprenda a leer archivos de configuracion
    this->nCasillas={10,10,1};
    this->nombres={"player_1","player_2"};
    this->nJugadores=this->nombres.size();
    this->nSoldados=3;
    this->tipoMapa=costa;
    this->rutaGraficas="../graphics_20/";
    this->rutaTableros="../tableros/";
    this->idioma="esp";
}

//---------------------------------------------------------------------------------------------------------------------
//                                                LECTURA DE DATOS
//---------------------------------------------------------------------------------------------------------------------

int gameConfig::getPlayerNumber(){
    return this->nJugadores;
}

//---------------------------------------------------------------------------------------------------------------------

int gameConfig::getTroopsNumber(){
    return this->nSoldados;
}

//---------------------------------------------------------------------------------------------------------------------

std::vector<unsigned int> gameConfig::getDimXYZ (){
    return this->nCasillas;
}

//---------------------------------------------------------------------------------------------------------------------

TipoMapa_T gameConfig::getMapType(){
    return this->tipoMapa;
}

//---------------------------------------------------------------------------------------------------------------------

std::vector<std::string> gameConfig::getPlayerNames(){
    return this->nombres;
}

//---------------------------------------------------------------------------------------------------------------------


std::string gameConfig::getGraficsPath(){
    return this->rutaGraficas;
}

//---------------------------------------------------------------------------------------------------------------------

std::string gameConfig::getOutPath(){
    return this->rutaTableros;
}

//---------------------------------------------------------------------------------------------------------------------

std::string gameConfig::getLanguage(){
    return this->idioma;
}