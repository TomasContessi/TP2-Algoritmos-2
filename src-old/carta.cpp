#include "carta.h"

//---------------------------------------------------------------------------------------------------------------------
//                                   CONTESSI TOMAS 99199 ALORITMOS Y PROGRAMACION II
//---------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------
//                                              METODOS DE LA CLASE CARTA
//---------------------------------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------------------------------
//                                              CONSTRUCTOR Y DESTRUCTOR
//---------------------------------------------------------------------------------------------------------------------

carta::carta(jugador* propietario,TiposCarta_T tipo)
{
        this->propieario=propieario;
        this->setType(tipo);
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
        this->alcance=30;
        this->AoE=3;
        this->disparos=1;
        this->movimiento[0]=0;
        this->movimiento[1]=0;
        this->movimiento[2]=0;
        break;
    case avion:
        this->alcance=10;
        this->AoE=1;
        this->disparos=2;
        this->movimiento[0]=1;
        this->movimiento[1]=10;
        this->movimiento[2]=0;
        break;
    case barco:
        this->alcance=30;
        this->AoE=3;
        this->disparos=1;
        this->movimiento[0]=0;
        this->movimiento[1]=0;
        this->movimiento[2]=1;
        break;
    case bomba_atomica:
        this->alcance=0;
        this->AoE=30;
        this->disparos=1;
        this->movimiento[0]=0;
        this->movimiento[1]=0;
        this->movimiento[2]=0;
        break;
    case dirigible:
        this->alcance=0;
        this->AoE=0;
        this->disparos=0;
        this->movimiento[0]=0;
        this->movimiento[1]=1;
        this->movimiento[2]=0;
        break;
    case ciclon:
        this->alcance=0;
        this->AoE=0;
        this->disparos=0;
        this->movimiento[0]=0;
        this->movimiento[1]=0;
        this->movimiento[2]=0;
        break;
    case terremoto:
        this->alcance=0;
        this->AoE=0;
        this->disparos=0;
        this->movimiento[0]=0;
        this->movimiento[1]=0;
        this->movimiento[2]=0;
        break;
    case tsunami:
        this->alcance=0;
        this->AoE=0;
        this->disparos=0;
        this->movimiento[0]=0;
        this->movimiento[1]=0;
        this->movimiento[2]=0;
        break;
    case soldado:
        this->alcance=10;
        this->AoE=1;
        this->disparos=1;
        this->movimiento[0]=1;
        this->movimiento[1]=0;
        this->movimiento[2]=1;
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
//                                            METODOS DE OBTENCION DE DATOS
//---------------------------------------------------------------------------------------------------------------------

jugador* carta::getPropietario(){
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
    return this->AoE;
}

//---------------------------------------------------------------------------------------------------------------------

int carta::getRange(){
    return this->alcance;
}

//---------------------------------------------------------------------------------------------------------------------

carta* carta::getNext(){
    return this->siguienteCarta;
}