#include "jugador.h"

//---------------------------------------------------------------------------------------------------------------------
//                                   CONTESSI TOMAS 99199 ALORITMOS Y PROGRAMACION II
//---------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------
//                                             METODOS DE LA CLASE JUGADOR
//---------------------------------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------------------------------
//                                              CONSTRUCTOR Y DESTRUCTOR
//---------------------------------------------------------------------------------------------------------------------

jugador::jugador(std::string nombre)
{
    this->nombre=nombre;
    this->siguienteJugador=NULL;
    this->estado=activo;
    this->cartas=NULL;
}

//---------------------------------------------------------------------------------------------------------------------

jugador::~jugador()
{
    while (this->cartas !=NULL)
    {
        this->retirarCarta(this->cartas);
    }
    
}

//---------------------------------------------------------------------------------------------------------------------
//                                                METODOS SOBRE CARTAS
//---------------------------------------------------------------------------------------------------------------------

void jugador::agregarCarta(carta* nueva){
    if (nueva == NULL)
    {
        throw "carta invalida";
    }
    
    nueva->setNext(this->cartas);
    this->cartas=nueva;
}

//---------------------------------------------------------------------------------------------------------------------

void jugador::retirarCarta(carta* vieja){
    carta* aux;

    if (vieja == NULL)
    {
        throw "carta invalida";
    }

    if (this->cartas==NULL)
    {
        return;
    }

    aux=this->cartas;

    if (aux == vieja)
    {
        this->cartas=vieja->getNext();
        delete vieja;
        return;
    }   

    while (aux->getNext() != NULL && aux->getNext() != vieja)
    {
        aux=aux->getNext();
    }

    if (aux->getNext() == vieja)
    {
        aux->setNext(vieja->getNext());
        delete vieja;
    } 
}

//---------------------------------------------------------------------------------------------------------------------

unsigned int jugador::contarCartas(TiposCarta_T tipo){
    carta* aux;
    unsigned int cuenta=0;

    aux=this->cartas; 

    while (aux != NULL)
    {
        if (aux->getType() == tipo)
        {
            cuenta++;
        }

        aux=aux->getNext();
    }

    return cuenta;
}

//---------------------------------------------------------------------------------------------------------------------
//                                            METODOS DE SETEO DE DATOS
//---------------------------------------------------------------------------------------------------------------------

void jugador::setSiguiente(jugador* siguiente){
    this->siguienteJugador=siguiente;
}

//---------------------------------------------------------------------------------------------------------------------

void jugador::setState(EstadoJugador_T estado){
    this->estado=estado;
}

//---------------------------------------------------------------------------------------------------------------------
//                                            METODOS DE LECTURA DE DATOS
//---------------------------------------------------------------------------------------------------------------------

EstadoJugador_T jugador::getState(){
    return this->estado;
}

//---------------------------------------------------------------------------------------------------------------------

std::string jugador::getName(){
    return this->nombre;
}

//---------------------------------------------------------------------------------------------------------------------

jugador* jugador::getSig(){
    return this->siguienteJugador;
}