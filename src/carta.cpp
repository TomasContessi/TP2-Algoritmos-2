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
    this->propieario=propietario;
    this->setType(tipo);
    this->municionRestante = this->stats.disparos;

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
        this->stats.alcance=10;
        this->stats.AoE=3;
        this->stats.disparos=1;
        this->stats.movimiento[0]=0;
        this->stats.movimiento[1]=0;
        this->stats.movimiento[2]=0;
        this->stats.terrenoAfin={tierra};
        break;
    case avion:
        this->stats.alcance=5;
        this->stats.AoE=1;
        this->stats.disparos=2;
        this->stats.movimiento[0]=1;
        this->stats.movimiento[1]=10;
        this->stats.movimiento[2]=0;
        this->stats.terrenoAfin={aire};
        break;
    case barco:
        this->stats.alcance=10;
        this->stats.AoE=3;
        this->stats.disparos=2;
        this->stats.movimiento[0]=0;
        this->stats.movimiento[1]=0;
        this->stats.movimiento[2]=2;
        this->stats.terrenoAfin={mar};
        break;
    case bomba_atomica:
        this->stats.alcance=0;
        this->stats.AoE=9;
        this->stats.disparos=1;
        this->stats.movimiento[0]=0;
        this->stats.movimiento[1]=0;
        this->stats.movimiento[2]=0;
        this->stats.terrenoAfin={tierra,aire,mar};
        break;
    case dirigible:
        this->stats.alcance=0;
        this->stats.AoE=0;
        this->stats.disparos=0;
        this->stats.movimiento[0]=0;
        this->stats.movimiento[1]=1;
        this->stats.movimiento[2]=0;
        this->stats.terrenoAfin={aire};
        break;
    case ciclon:
        this->stats.alcance=0;
        this->stats.AoE=0;
        this->stats.disparos=0;
        this->stats.movimiento[0]=0;
        this->stats.movimiento[1]=0;
        this->stats.movimiento[2]=0;
        this->stats.terrenoAfin={aire};
        break;
    case terremoto:
        this->stats.alcance=0;
        this->stats.AoE=0;
        this->stats.disparos=0;
        this->stats.movimiento[0]=0;
        this->stats.movimiento[1]=0;
        this->stats.movimiento[2]=0;
        this->stats.terrenoAfin={tierra};
        break;
    case tsunami:
        this->stats.alcance=0;
        this->stats.AoE=0;
        this->stats.disparos=0;
        this->stats.movimiento[0]=0;
        this->stats.movimiento[1]=0;
        this->stats.movimiento[2]=0;
        this->stats.terrenoAfin={mar};
        break;
    case soldado:
        this->stats.alcance=5;
        this->stats.AoE=1;
        this->stats.disparos=1;
        this->stats.movimiento[0]=1;
        this->stats.movimiento[1]=0;
        this->stats.movimiento[2]=1;
        this->stats.terrenoAfin={tierra,mar};
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

void carta::setPos (int pos[]){
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

int carta::shoot(){
    if (this->municionRestante < 1)
    {
        throw "no habia municion";
    }
    return this->municionRestante--;
}

//---------------------------------------------------------------------------------------------------------------------

void carta::reloadAmmo(){
    this->municionRestante = this->stats.disparos;
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

int* carta::getPos(){
    return this->posicion;
}

//---------------------------------------------------------------------------------------------------------------------

CardStats carta::getStats(){
    return this->stats;
}

//---------------------------------------------------------------------------------------------------------------------

int carta::getAmmo(){
    return this->municionRestante;
}