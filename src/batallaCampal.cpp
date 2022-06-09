#include <iostream>
#include <string>

#include "batallaCampal.hpp"

using namespace std;

//---------------------------------------------------------------------------------------------------------------------
//                                   CONTESSI TOMAS 99199 ALORITMOS Y PROGRAMACION II
//---------------------------------------------------------------------------------------------------------------------
//-----------------------------------------------BATALLA CAMPAL 2 V2.2-------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------
//                                       IMPLEMENTACION DE LA CLASE BATALLA CAMPAL
//---------------------------------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------------------------------
//                                              CONSTRUCTOR Y DESTRUCTOR
//---------------------------------------------------------------------------------------------------------------------


batallaCampal::batallaCampal(){
    this->estado = iniciando;
    this->configuracion = NULL;
    this->map = NULL;
    this->rondita = NULL;
    this->printer = NULL;

    this->cargarConfiguracion(); // muy importante que esto sea lo primero que hace el tda

    this->rondita->iniciarRonda();
}

//---------------------------------------------------------------------------------------------------------------------

batallaCampal::~batallaCampal(){
    delete this->printer;
    delete this->rondita;
    delete this->map;
    delete this->configuracion;
}

//---------------------------------------------------------------------------------------------------------------------
//                                                  METODOS PRIVADOS
//---------------------------------------------------------------------------------------------------------------------

//                                              METODOS DE CONFIGURACION
//---------------------------------------------------------------------------------------------------------------------

void batallaCampal::generarMapa(){
    if (this->map != NULL)
    {
        delete this->map;
    }

    this->map  = new mapa(this->configuracion->getMapType(),this->configuracion->getDimXYZ());
}

//---------------------------------------------------------------------------------------------------------------------

void batallaCampal::generarRonda(){
    if (this->rondita != NULL)
    {
        delete this->rondita;
    }

    this->rondita = new ronda(); // pido memoria para la ronda

    for (int i = 0; i < this->configuracion->getPlayerNames().size(); i++) //cargo los jugadores en la ronda
    {
        this->rondita->agregarJugador(new jugador (this->configuracion->getPlayerNames()[i]));// voy agregando el nuevo jugador con el nombre que tengo
    }   
}

//---------------------------------------------------------------------------------------------------------------------

void batallaCampal::generarImpresora(){
    if (this->printer != NULL)
    {
        delete this->printer;
    }

    this->printer = new graficador(this->map,this->rondita);

    this->printer->selecRutaGraficas(this->configuracion->getGraficsPath());
    this->printer->selecRutaSalida(this->configuracion->getOutPath());
    this->printer->cargarGraficas();
}

//---------------------------------------------------------------------------------------------------------------------

void batallaCampal::cargarConfiguracion(){

    this->cargarConfiguracion("../config/default_config");
}

//---------------------------------------------------------------------------------------------------------------------

void batallaCampal::cargarConfiguracion(std::string path){

    if (this->configuracion != NULL)
    {
        delete this->configuracion;
    }

    this->configuracion = new gameConfig();

    this->configuracion->loadConfig(path);

    this->generarMapa();
    this->generarRonda();
    this->generarImpresora();
}

//                                                  METODOS DE LOGICA
//---------------------------------------------------------------------------------------------------------------------

bool batallaCampal::playerReady(){
    string nombre;
    string entrada;

    nombre = this->rondita->getJugadorEnTurno();

    cout << nombre << " " << this->mensaje.listo << endl;
    cout << this->mensaje.Y_N << endl;

    cin >> entrada;

    cout << endl;

    if (entrada == "Y" || entrada == "y")
    {
        return true;
    }

    return false;
    
}

//---------------------------------------------------------------------------------------------------------------------

bool batallaCampal::atackStage(){

    string entrada;

    cout << this->mensaje.deseaAtacar << endl; 
    cout << this->mensaje.Y_N << endl;

    cout << endl;

    cin >> entrada;

    cout << endl;

    if (entrada == "n" || entrada == "N")
    {
        return true;
    }


    if (this->cardSelectionStage() == true) // con este tipo de logica segun yo puedo ir anidando todas las decisiones
    {
        while (this->targetStrikeStage() == false){}
        return true;
    }
    
    cout << this->mensaje.casillaInvalida << endl;
    cout << endl;

    return false;
}

//---------------------------------------------------------------------------------------------------------------------

bool batallaCampal::regroupStage(){
    string entrada;

    cout << this->mensaje.deseaMover << endl; 
    cout << this->mensaje.Y_N << endl;

    cout << endl;

    cin >> entrada;

    cout << endl;

    if (entrada == "n" || entrada == "N")
    {
        return true;
    }


    if (this->cardSelectionStage() == true)
    {
        while (this->moveStage() == false){}
        return true;
    }
    
    cout << this->mensaje.casillaInvalida << endl;
    cout << endl;

    return false;
}

//---------------------------------------------------------------------------------------------------------------------

bool batallaCampal::cardChoiceStage(){
    string entrada;
    int coordenada;
    vector<unsigned int> pos;

    cout << this->mensaje.conservarCarta << endl; 
    cout << this->mensaje.Y_N << endl;

    cout << endl;

    cin >> entrada;

    cout << endl;

    if (entrada == "n" || entrada == "N")
    {
        this->rondita->tirarCarta();
        return true;
    }

    while (this->ingresarPosicion(&pos) == false){}
    
    if (this->verificarPosicionCarta(this->rondita->getCardType(),pos) == false)
    {
        cout << this->mensaje.cartaPosInvalid << endl;
        cout << endl;
        return false;
    }

    this->rondita->jugarCarta(pos.data());
    this->map->takeCasilla(pos,this->rondita->getJugadorEnTurno());
    return true;
}


//---------------------------------------------------------------------------------------------------------------------

bool batallaCampal::cardSelectionStage(){}

//---------------------------------------------------------------------------------------------------------------------

bool batallaCampal::targetStrikeStage(){}

//---------------------------------------------------------------------------------------------------------------------

bool batallaCampal::aditionalAtacksStage(){}

//---------------------------------------------------------------------------------------------------------------------

bool batallaCampal::ingresarPosicion(std::vector<unsigned int> * pos){
    unsigned int entrada;

    for (size_t i = 0; i < this->mensaje.coordenadas.size(); i++)
    {
        cout << this->mensaje.ingreseCoordenada << " " << this->mensaje.coordenadas[i] << endl;

        cout << this->mensaje.Y_N << endl;

        cout << endl;

        cin >> entrada;

        cout << endl;

        if (entrada > this->configuracion->getDimXYZ()[i])
        {
            cout << this->mensaje.coordenadaInvalida << endl;
            return false;
        }    
        (*pos)[i]=entrada; 
    }
    return true;
}

//---------------------------------------------------------------------------------------------------------------------

void batallaCampal::buryBodies(){}

//---------------------------------------------------------------------------------------------------------------------
//                                                  METODOS PUBLICOS
//---------------------------------------------------------------------------------------------------------------------


void batallaCampal::ejecutarTurno(){

    while (this->playerReady() == false){} //hago asi para poder volver atras en los menus sin anidar una infinidad de ifs

    while (this->atackStage() == false){}

    while (this->regroupStage() == false){}

    while (this->aditionalAtacksStage() == false){}

    this->rondita->tomarCarta();

    while (this->cardChoiceStage() == false){}

    this->printPlayersScreens();

    this->buryBodies();

    this->rondita->avanzarTurno();
    
}

//---------------------------------------------------------------------------------------------------------------------

void batallaCampal::saludarGanador(){

}

//---------------------------------------------------------------------------------------------------------------------

EstadoPartida_T batallaCampal::getState(){

    if (this->rondita->contarJugadores() <= 1)
    {
        this->estado = terminada;
    }else{
        this->estado = jugando;
    }
    
    return this->estado;
}

//---------------------------------------------------------------------------------------------------------------------

void batallaCampal::printPlayersScreens(){
    int n;
    for (size_t i = 0; i < this->configuracion->getPlayerNumber(); i++)
    {
        this->printer->enmascarar(true);

        n=this->rondita->contarCartas(this->configuracion->getPlayerNames()[i],dirigible); // si el jugador tiene almenos un dirigible le miestro todo el mapa

        if (n > 0)
        {
            this->printer->enmascarar(false);
        }

        if (this->rondita->getPlayerState(this->configuracion->getPlayerNames()[i]) == derrotado) //si el jugador esta derrotado le muestro el mapa final
        {
            this->printer->enmascarar(false);
        }
        

        // si quiero cambiar los fondos lo tendria que agregar aca
        
        this->printer->graficarPantalla(this->configuracion->getPlayerNames()[i]);
    }
    
}