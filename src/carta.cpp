#include "carta.hpp"

//---------------------------------------------------------------------------------------------------------------------
//                                   CONTESSI TOMAS 99199 ALORITMOS Y PROGRAMACION II
//---------------------------------------------------------------------------------------------------------------------
//-----------------------------------------------BATALLA CAMPAL 2 V2.1-------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------
//                                              METODOS DE LA CLASE CARTA
//---------------------------------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------------------------------
//                                              CONSTRUCTOR Y DESTRUCTOR
//---------------------------------------------------------------------------------------------------------------------

carta::carta(std::string propietario,TiposCarta_T tipo)
{
    this->propieario=propieario;
    this->setType(tipo);

    this->siguienteCarta=NULL;

    for (int i = 0; i < 3; i++)
    {
        this->posicion[i] = 0;
    }
}

//---------------------------------------------------------------------------------------------------------------------

carta::~carta()
{ 
}

//---------------------------------------------------------------------------------------------------------------------
//                                                   METODOS PRIVADOS
//---------------------------------------------------------------------------------------------------------------------

void carta::setType(TiposCarta_T tipo){
    switch (tipo)
    {
    case misil:
        this->stats.alcance=30;
        this->stats.AoE=3;
        this->stats.disparos=1;
        this->stats.movimiento[0]=0;
        this->stats.movimiento[1]=0;
        this->stats.movimiento[2]=0;
        break;
    case avion:
        this->stats.alcance=10;
        this->stats.AoE=1;
        this->stats.disparos=2;
        this->stats.movimiento[0]=1;
        this->stats.movimiento[1]=10;
        this->stats.movimiento[2]=0;
        break;
    case barco:
        this->stats.alcance=30;
        this->stats.AoE=3;
        this->stats.disparos=1;
        this->stats.movimiento[0]=0;
        this->stats.movimiento[1]=0;
        this->stats.movimiento[2]=1;
        break;
    case bomba_atomica:
        this->stats.alcance=0;
        this->stats.AoE=30;
        this->stats.disparos=1;
        this->stats.movimiento[0]=0;
        this->stats.movimiento[1]=0;
        this->stats.movimiento[2]=0;
        break;
    case dirigible:
        this->stats.alcance=0;
        this->stats.AoE=0;
        this->stats.disparos=0;
        this->stats.movimiento[0]=0;
        this->stats.movimiento[1]=1;
        this->stats.movimiento[2]=0;
        break;
    case ciclon:
        this->stats.alcance=0;
        this->stats.AoE=0;
        this->stats.disparos=0;
        this->stats.movimiento[0]=0;
        this->stats.movimiento[1]=0;
        this->stats.movimiento[2]=0;
        break;
    case terremoto:
        this->stats.alcance=0;
        this->stats.AoE=0;
        this->stats.disparos=0;
        this->stats.movimiento[0]=0;
        this->stats.movimiento[1]=0;
        this->stats.movimiento[2]=0;
        break;
    case tsunami:
        this->stats.alcance=0;
        this->stats.AoE=0;
        this->stats.disparos=0;
        this->stats.movimiento[0]=0;
        this->stats.movimiento[1]=0;
        this->stats.movimiento[2]=0;
        break;
    case soldado:
        this->stats.alcance=10;
        this->stats.AoE=1;
        this->stats.disparos=1;
        this->stats.movimiento[0]=1;
        this->stats.movimiento[1]=0;
        this->stats.movimiento[2]=1;
        break;
    
    default:

        throw "tipo de carta invalido";
        break;
    }

    this->tipo=tipo;

}

//---------------------------------------------------------------------------------------------------------------------
//                                              METODOS DE SETEO DE DATOS
//---------------------------------------------------------------------------------------------------------------------

void carta::setState(EstadoCarta_T estado){
    this->estado=estado;
}

//---------------------------------------------------------------------------------------------------------------------

void carta::setNext(carta* siguiente){
    this->siguienteCarta=siguiente;
}

//---------------------------------------------------------------------------------------------------------------------

void carta::setPos (unsigned int pos[]){
    if (pos == NULL)
    {
        throw "posicion invalida para la carga";
    }

    for (int i = 0; i < 3; i++)
    {
        this->posicion[i] = pos[i];
    }
    
}

//---------------------------------------------------------------------------------------------------------------------
//                                            METODOS DE OBTENCION DE DATOS
//---------------------------------------------------------------------------------------------------------------------

std::string carta::getPropietario(){
    return this->propieario;
}

//---------------------------------------------------------------------------------------------------------------------

TiposCarta_T carta::getType (){
    return this->tipo;
}

//---------------------------------------------------------------------------------------------------------------------

EstadoCarta_T carta::getState (){
    return this->estado;
}

//---------------------------------------------------------------------------------------------------------------------

int carta::getAoE(){
    return this->stats.AoE;
}

//---------------------------------------------------------------------------------------------------------------------

int carta::getRange(){
    return this->stats.alcance;
}

//---------------------------------------------------------------------------------------------------------------------

carta* carta::getNext(){
    return this->siguienteCarta;
}

//---------------------------------------------------------------------------------------------------------------------

unsigned int* carta::getPos(){
    return this->posicion;
}

CardStats carta::getStats(){
    return this->stats;
}