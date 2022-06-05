#include "jugador.hpp"

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
        this->retirarCarta(this->cartas->getPos());
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

void jugador::retirarCarta(unsigned int posVieja []){
    carta* aux;
    carta* aux2;

    if (posVieja == NULL)
    {
        throw "carta invalida";
    }

    if (this->cartas==NULL)
    {
        return;
    }

    aux=this->cartas;

    if (aux->getPos() == posVieja)
    {
        this->cartas=aux->getNext(); // si la carta a eliminar es la primera del mazo la cambio por la que le sigue y la borro
        delete aux;
        return;
    }   

    while (aux->getNext() != NULL && aux->getPos() != posVieja) // voy buscando la carta en esa posicion hasta terminar el monton
    {
        aux2=aux;
        aux=aux->getNext();
    }

    if (aux->getPos() == posVieja)
    {
        aux2->setNext(aux->getNext()); // cuando encontre la carta en dicha posicion la saco de la lista
        delete aux;
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