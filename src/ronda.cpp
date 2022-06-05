#include "ronda.hpp"

//---------------------------------------------------------------------------------------------------------------------
//                                   CONTESSI TOMAS 99199 ALORITMOS Y PROGRAMACION II
//---------------------------------------------------------------------------------------------------------------------
//-----------------------------------------------BATALLA CAMPAL 2 V2.1-------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------
//                                          IMPLEMENTACION DE LA CLASE RONDA
//---------------------------------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------------------------------
//                                              CONSTRUCTOR Y DESTRUCTOR
//---------------------------------------------------------------------------------------------------------------------

ronda::ronda()
{
    this->jugadores=NULL;
    this->jugadorEnTurno=this->jugadores;
    this->nuevaCarta=NULL;
}

ronda::~ronda()
{
}

//---------------------------------------------------------------------------------------------------------------------
//                                              METODOS SOBRE JUGADORES
//---------------------------------------------------------------------------------------------------------------------

void ronda::agregarJugador(jugador* player){
    jugador* aux;

    if (this->jugadores == NULL) // si la ronda estaba vacia la inicio con este jugador
    {
        this->jugadores= player;
        player->setSiguiente(this->jugadores);
        this->iniciarRonda();
        return;
    }
    
    aux=this->jugadores;

    while (aux->getSig() != this->jugadores && aux != NULL) // voy recorriendo la ronda hasta encontrar el ultimo, o que se rompa la cadena circular
    {
        aux=aux->getSig();
    }
    
    if (aux->getSig() == this->jugadores) // si salio porque encontro al ultimo jugador agrego el nuevo
    {
        aux->setSiguiente(player);
        player->setSiguiente(this->jugadores);
        this->iniciarRonda();
        return;
    }

    throw "error en la estructura de la ronda"; // si llego hasta aca es que la ronda estaba cortada en algun lado

}

//---------------------------------------------------------------------------------------------------------------------

