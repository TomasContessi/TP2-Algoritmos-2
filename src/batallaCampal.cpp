#include "batallaCampal.hpp"

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

//---------------------------------------------------------------------------------------------------------------------
//                                                  METODOS PUBLICOS
//---------------------------------------------------------------------------------------------------------------------


void batallaCampal::ejecutarTurno(){

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