#include "jugador.hpp"

//---------------------------------------------------------------------------------------------------------------------
//                                   CONTESSI TOMAS 99199 ALORITMOS Y PROGRAMACION II
//---------------------------------------------------------------------------------------------------------------------
//-----------------------------------------------BATALLA CAMPAL 2 V2.1-------------------------------------------------
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

    if (compararPos(aux->getPos() , posVieja))
    {
        this->cartas=aux->getNext(); // si la carta a eliminar es la primera del mazo la cambio por la que le sigue y la borro
        delete aux;
        return;
    }   

    while (aux->getNext() != NULL && compararPos(aux->getPos(),posVieja) !=true) // voy buscando la carta en esa posicion hasta terminar el monton
    {
        aux2=aux;
        aux=aux->getNext();
    }

    if (compararPos(aux->getPos() , posVieja))
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

CardStats jugador::getCardStats (unsigned int pos []){
    carta* aux;
    CardStats empy_stats;

    if (this->cartas==NULL)
    {
        return empy_stats;
    }

    aux=this->cartas;

    while (aux->getNext() != NULL && compararPos(aux->getPos(),pos) != true) // voy buscando la carta en esa posicion hasta terminar el monton
    {
        aux=aux->getNext();
    }

    if (compararPos(aux->getPos(),pos))
    {
        return aux->getStats();
    }

    return empy_stats;
    
}

//---------------------------------------------------------------------------------------------------------------------

int jugador::getCardAmmo (unsigned int pos []){
    carta* aux;
    CardStats empy_stats;

    if (this->cartas==NULL)
    {
        return 0;
    }

    aux=this->cartas;

    while (aux->getNext() != NULL && compararPos(aux->getPos(),pos) != true) // voy buscando la carta en esa posicion hasta terminar el monton
    {
        aux=aux->getNext();
    }

    if (compararPos(aux->getPos(),pos))
    {
        return aux->getAmmo();
    }

    return 0;
    
}

//---------------------------------------------------------------------------------------------------------------------

int jugador::getCardAmmo (){
    carta* aux;
    int ammo;
    ammo=0;
    if (this->cartas==NULL)
    {
        return 0;
    }

    aux=this->cartas;

    while (aux != NULL) // mientras tenga cartas las hago recargar
    {
        if (aux->getType() != soldado) // no cuento los soldados porque estos no dan ataques extra
        {
            ammo = ammo + aux->getAmmo();
            aux = aux->getNext();
        }
    } 
    return ammo;
}

//---------------------------------------------------------------------------------------------------------------------

int jugador::shoot(unsigned int pos[3]){
    carta* aux;
    if (this->cartas==NULL)
    {
        return 0;
    }

    aux=this->cartas;

    while (aux != NULL) // mientras tenga cartas busco
    {
        if (compararPos(aux->getPos(),pos) == true) // cuando la enfuentro disparo
        {
            return aux->shoot();
        }
        aux = aux->getNext();
    } 
    return 0;
}

//---------------------------------------------------------------------------------------------------------------------

TiposCarta_T jugador::getCardType (unsigned int pos []){
    carta* aux;

    if (this->cartas==NULL)
    {
        throw "no hay cartas";
    }

    aux=this->cartas;

    while (aux->getNext() != NULL && compararPos(aux->getPos(),pos) != true) // voy buscando la carta en esa posicion hasta terminar el monton
    {
        aux=aux->getNext();
    }

    if (compararPos(aux->getPos(),pos))
    {
        return aux->getType();
    }

    throw "no hay cartas en esa posicion";
    
}

//---------------------------------------------------------------------------------------------------------------------

void jugador::reloadCardAmmo (unsigned int pos []){
    carta* aux;
    if (this->cartas==NULL)
    {
        return;
    }

    aux=this->cartas;

    while (aux->getNext() != NULL && compararPos(aux->getPos(),pos) != true) // voy buscando la carta en esa posicion hasta terminar el monton
    {
        aux=aux->getNext();
    }

    if (compararPos(aux->getPos(),pos))
    {
        aux->reloadAmmo();
        return;
    }   
}

//---------------------------------------------------------------------------------------------------------------------

void jugador::reloadCardAmmo (){
    carta* aux;
    if (this->cartas==NULL)
    {
        return;
    }

    aux=this->cartas;

    while (aux != NULL) // mientras tenga cartas las hago recargar
    {
        aux->reloadAmmo();
        aux=aux->getNext();
    } 
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

//---------------------------------------------------------------------------------------------------------------------

bool jugador::verificarCarta (std::vector<unsigned int> pos){
    carta* aux;

    aux=this->cartas;
    while (aux != NULL)
    {
        if (compararPos(pos.data(),aux->getPos()) == true)
        {
            return true;
        }
        
    }
    return false;
}
