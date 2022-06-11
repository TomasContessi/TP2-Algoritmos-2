#include "gameConfig.hpp"



//---------------------------------------------------------------------------------------------------------------------
//                                   CONTESSI TOMAS 99199 ALORITMOS Y PROGRAMACION II
//---------------------------------------------------------------------------------------------------------------------
//--------------------------------------------      BATALLA CAMPAL 2      ---------------------------------------------
//---------------------------------------------------------------------------------------------------------------------
//                                        METODOS DE LA CLASE GAME CONFIG V2.3
//---------------------------------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------------------------------
//                                              CONSTRUCTOR Y DESTRUCTOR
//---------------------------------------------------------------------------------------------------------------------

gameConfig::gameConfig()
{
    std::string defaultPath ="../config/default_config.ini";
    this->loadConfig(defaultPath);
}

gameConfig::~gameConfig()
{
}

//---------------------------------------------------------------------------------------------------------------------
//                                              CARGA DE CONFIGURACION
//---------------------------------------------------------------------------------------------------------------------

void gameConfig::loadConfig(std::string path){ // por ahora esta hardcodeado hasta que aprenda a leer archivos de configuracion
/*
    this->nCasillas={10,10,2};
    this->nombres={"Lucas","Bogda"};
    this->nJugadores=this->nombres.size();
    this->nSoldados=3;
    this->tipoMapa=isla;
    this->rutaGraficas="../graphics_20/";
    this->rutaTableros="../tableros/";
    this->idioma="esp";
*/
    std::ifstream entrada;
    std::string lineaSTR;
    std::vector<std::string> lineas;
    int campo=0;

    this->nCasillas.resize(3);

    entrada.open("../config/default_config.ini");

    // leo todo el archivo de configuracion
    while(std::getline(entrada,lineaSTR)){
        if (lineaSTR[0] != '#' && lineaSTR != "" ) // le saco los comentarios
        {
            campo++;
            lineas.resize(campo);
            lineas[campo-1]=lineaSTR;
        }
    }
    entrada.close();
    this->nJugadores=lineas.size()-9; // 9 es la cantidad de otros campos, asi que la antidad de lineas menos los campos es la cantidad de nombres
    this->nombres.resize(this->nJugadores); 
    this->nCasillas[0]=atoi(lineas[0].data());
    this->nCasillas[1]=atoi(lineas[1].data());
    this->nCasillas[2]=atoi(lineas[2].data());
    this->nSoldados=atoi(lineas[3].data());
    this->tipoMapa=costa; // opcion default
    if (lineas[4] == "rio")
    {
        this->tipoMapa=rio;
    }
    if (lineas[4] == "isla")
    {
        this->tipoMapa=isla;
    }
    if (lineas[4] == "lago")
    {
        this->tipoMapa=lago;
    } 
    this->idioma=lineas[5];
    this->rutaGraficas=lineas[6];
    this->rutaTableros=lineas[7];
    this->rutaConfig=lineas[8];
    // ahora cargo los jugadores
    for (size_t i = 0; i < this->nJugadores ; i++)
    {
        this->nombres[i]=lineas[i+9];
    }
    
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

std::vector<int> gameConfig::getDimXYZ (){
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