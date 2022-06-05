#include "mapa.h"


//---------------------------------------------------------------------------------------------------------------------
//                                   CONTESSI TOMAS 99199 ALORITMOS Y PROGRAMACION II
//---------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------
//                                              METODOS DE LA CLASE MAPA
//---------------------------------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------------------------------
//                                              CONSTRUCTOR Y DESTRUCTOR
//---------------------------------------------------------------------------------------------------------------------

mapa::mapa(TipoMapa_T tipoMapa,unsigned int* dimension){
    this->seed=new casilla(tierra); // creo la primera casilla
    this->iniciarCursor();

    // ahora creo un mapa de las dimensiones que me piden
    for (int i = 0; i < dimension[0]; i++)
    {
        this->xGrow();
    }
    for (int i = 0; i < dimension[1]; i++)
    {
        this->yGrow();
    }
    for (int i = 0; i < dimension[2]; i++)
    {
        this->zGrow();
    }

}

//---------------------------------------------------------------------------------------------------------------------

mapa::~mapa(){
    while (this->seed != NULL)
    {
        this->zDecay();
    }
    
}


//---------------------------------------------------------------------------------------------------------------------
//                                                  METODOS PRIVADOS
//---------------------------------------------------------------------------------------------------------------------

void mapa::xGrow(){
    casilla* nueva;

    this->iniciarCursor(); // inicio el cursor en el 0 0 0

    while (this->cursor->getE()!=NULL)
    {
        this->avanzarCursorX(); // voy avanzando en x hasta llegar a la frontera
    }
    
    do{ // hasta que llegue completamente al norte del mapa
        do{ // hasta que llegue completamente arriba en el mapa
            unsigned int * nuevaPosicion = this->cursor->getPos();
            nuevaPosicion[0]++;
            nueva= new casilla(this->setCasillaType(this->tipoMapa,nuevaPosicion)); //creo una nueva casilla
            nueva->setW(this->cursor); //conecto la nueva casilla con el cursor al sur

            if (this->cursor->getInf()!=NULL)
            {
                nueva->setInf(this->cursor->getInf()->getE());// si tengo una capa abajo conecto la nueva con la que esta abajo
            }

            if (this->cursor->getS()!=NULL)
            {
                nueva->setS(this->cursor->getS()->getE());// si tengo una capa al sur conecto la nueva con la que esta al sur
            }

            this->avanzarCursorZ();// una vez conectada la nueva casilla avanzo 1 en z el cursor
        }while(this->cursor->getSup()!=NULL);

        this->avanzarCursorY();// una vez avanzado todo el cursor en z avanzo 1 en y

        while(this->cursor->getInf()!=NULL)
        {
            this->retrocederCursorZ(); // y devuelvo el carro a z=0
        }

    }while (this->cursor->getN()!=NULL);
}

//---------------------------------------------------------------------------------------------------------------------

void mapa::yGrow(){
    casilla* nueva;

    this->iniciarCursor(); // inicio el cursor en el 0 0 0

    while (this->cursor->getN()!=NULL)
    {
        this->avanzarCursorY(); // voy avanzando en y hasta llegar a la frontera
    }
    
    do{ // hasta que llegue completamente al este del mapa
        do{ // hasta que llegue completamente arriba en el mapa
            unsigned int * nuevaPosicion = this->cursor->getPos();
            nuevaPosicion[1]++;
            nueva= new casilla(this->setCasillaType(this->tipoMapa,nuevaPosicion)); //creo una nueva casilla
            nueva->setS(this->cursor); //conecto la nueva casilla con el cursor al oeste

            if (this->cursor->getInf()!=NULL)
            {
                nueva->setInf(this->cursor->getInf()->getN());// si tengo una capa abajo conecto la nueva con la que esta abajo
            }

            if (this->cursor->getW()!=NULL)
            {
                nueva->setW(this->cursor->getW()->getN());// si tengo una capa al oeste conecto la nueva con la que esta al oeste
            }

            this->avanzarCursorZ();// una vez conectada la nueva casilla avanzo 1 en z el cursor
        }while(this->cursor->getSup()!=NULL);

        this->avanzarCursorX();// una vez avanzado todo el cursor en z avanzo 1 en x

        while(this->cursor->getInf()!=NULL)
        {
            this->retrocederCursorZ(); // y devuelvo el carro a z=0
        }

    }while (this->cursor->getE()!=NULL);
}

//---------------------------------------------------------------------------------------------------------------------

void mapa::zGrow(){
    casilla* nueva;

    this->iniciarCursor(); // inicio el cursor en el 0 0 0

    while (this->cursor->getSup()!=NULL)
    {
        this->avanzarCursorZ(); // voy avanzando en z hasta llegar a la frontera
    }
    
    do{ // hasta que llegue completamente al norte del mapa
        do{ // hasta que llegue completamente al este en el mapa
            unsigned int * nuevaPosicion = this->cursor->getPos();
            nuevaPosicion[2]++;
            nueva= new casilla(this->setCasillaType(this->tipoMapa,nuevaPosicion)); //creo una nueva casilla
            nueva->setInf(this->cursor); //conecto la nueva casilla con el cursor al sur

            if (this->cursor->getS()!=NULL)
            {
                nueva->setS(this->cursor->getS()->getSup());// si tengo una capa al sur conecto la nueva con la que esta al sur
            }

            if (this->cursor->getW()!=NULL)
            {
                nueva->setW(this->cursor->getW()->getSup());// si tengo una capa a la izquierda conecto la nueva con la que esta a la izquierda
            }

            this->avanzarCursorX();// una vez conectada la nueva casilla avanzo 1 en x el cursor
        }while(this->cursor->getE()!=NULL);

        this->avanzarCursorY();// una vez avanzado todo el cursor en z avanzo 1 en y

        while(this->cursor->getInf()!=NULL)
        {
            this->retrocederCursorX(); // y devuelvo el carro a x=0
        }

    }while (this->cursor->getN()!=NULL);
}

//---------------------------------------------------------------------------------------------------------------------

CasillaTipo_T mapa::setCasillaType(TipoMapa_T tipo, unsigned int * posicion){

    if (this->verificarCasilla(posicion) == false)
    {
        throw "posicion invalida";
    }

    switch (tipo)
    {
    case costa:
        
        if (posicion[2]<1 && posicion[0] < this->dimensionXYZ[0]/2)
        {
            return tierra;
        }

        if (posicion[1]<1 && posicion[0] >= this->dimensionXYZ[0]/2)
        {
            return mar;
        }

        return aire;
        
        break;

    case isla:
        if (posicion[2]>0)
        {
            return aire;
        }
        
        if (posicion[1] > this->dimensionXYZ[1]/3 && posicion[0] > this->dimensionXYZ[0]/3)
        {
            if (posicion[1] <= 2*(this->dimensionXYZ[1])/3 && posicion[0] <= 2*(this->dimensionXYZ[0])/3)
            {
              return tierra;
            }
        }

        return mar;

        break;

    case lago:
        if (posicion[2]>0)
        {
            return aire;
        }
        
        if (posicion[1] > this->dimensionXYZ[1]/3 && posicion[0] > this->dimensionXYZ[0]/3)
        {
            if (posicion[1] <= 2*(this->dimensionXYZ[1])/3 && posicion[0] <= 2*(this->dimensionXYZ[0])/3)
            {
              return mar;
            }
        }

        return tierra;
        
        break;

    case rio:
        if (posicion[2]>0)
        {
            return aire;
        }
        
        if (posicion[1] > this->dimensionXYZ[1]/3 && posicion[1] <= 2*(this->dimensionXYZ[1])/3)
        {
            return mar;
        }

        return tierra;
        
        break;
    
    default:
        return tierra;

        break;
    }
}

//---------------------------------------------------------------------------------------------------------------------

void mapa::zDecay(){
    this->iniciarCursor();

    while (this->cursor->getSup() != NULL) // mientras tengo casillas arriba
    {
        this->avanzarCursorZ(); // levo el cursor hasta arriba del todo
    }

    while (this->cursor->getN() != NULL) // mientras tengo casillas al norte
    {
        this->avanzarCursorY(); // levo el cursor hasta arriba todo al norte
    }

    while (this->cursor->getE() != NULL) // mientras tengo casillas al este
    {
        this->avanzarCursorX(); // levo el cursor hasta arriba todo al este
    }

    while (this->cursor->getW() != NULL)
    {
        while (this->cursor->getS() != NULL)
        {
            this->retrocederCursorY();

            this->cursor->getN()->~casilla(); // borro la casilla al norte del cursor
        }

        this->retrocederCursorX();

        this->cursor->getE()->~casilla(); // borro la casilla al este del cursor

        while (this->cursor->getN() != NULL) // mientras tengo casillas al norte
        {
            this->avanzarCursorY(); // levo el cursor hasta arriba todo al norte
        }
    }

    this->cursor->~casilla(); // por ultimo mato la ultima casilla del nivel
    
}

//---------------------------------------------------------------------------------------------------------------------
//                                          METODOS DE MODIFICACION DE CASILLAS
//---------------------------------------------------------------------------------------------------------------------

void mapa::attackCasilla(unsigned int pos []){
    this->jumpCursor(pos);

    if(this->cursor->getEstado() == ocupada)
    {
        this->cursor->getCard()->~carta();
    }

    if(this->cursor->getTippo() == tierra)
    {
        this->cursor->setEstado(destruida,NULL);
    }else
    {
        this->cursor->setEstado(libre,NULL);
    }
}

//---------------------------------------------------------------------------------------------------------------------

void mapa::leaveCasilla(unsigned int pos []){
    this->jumpCursor(pos);

    this->cursor->getCard()->setState(mano);

    this->cursor->setEstado(libre,NULL);
}

//---------------------------------------------------------------------------------------------------------------------

void mapa::takeCasilla(unsigned int pos [],carta* card){
    if (card == NULL)
    {
        throw "card nulo";
    }

    this->jumpCursor(pos);

    switch (this->cursor->getEstado())
    {
    case libre:
        this->cursor->setEstado(ocupada ,card);
        break;

    case ocupada:
        delete this->cursor->getCard();
        delete card; // tengo que cambiar para borrar las cartas usando al jugador
        this->cursor->setEstado(libre,NULL);
        break;

    case destruida:
        delete card;
        break;
    
    default:
        throw "estado invalido";
        break;
    }    
}

//---------------------------------------------------------------------------------------------------------------------
//                                          METODOS DE OBTENCION DE DATOS
//---------------------------------------------------------------------------------------------------------------------

CasillaEstado_T mapa::getStateCasilla(unsigned int pos[]){
    this->jumpCursor(pos);
    return this->cursor->getEstado();
}

//---------------------------------------------------------------------------------------------------------------------

CasillaTipo_T mapa::getTypeCasilla(unsigned int pos[]){
    this->jumpCursor(pos);
    return this->cursor->getTippo();
}

//---------------------------------------------------------------------------------------------------------------------

carta* mapa::getCard(unsigned int pos []){
    this->jumpCursor(pos);
    return this->cursor->getCard();
}

//---------------------------------------------------------------------------------------------------------------------

jugador* mapa::getPropietario(unsigned int pos []){
    return this->getCard(pos)->getPropietario();
}

//---------------------------------------------------------------------------------------------------------------------
casilla* mapa::getCursor(){
    return this->cursor;
}

//---------------------------------------------------------------------------------------------------------------------
//                                          METODOS DE MOVIMIENTO DEL CURSOR
//---------------------------------------------------------------------------------------------------------------------

void mapa::iniciarCursor(){
    this->cursor=this->seed;
}

//---------------------------------------------------------------------------------------------------------------------

bool mapa::avanzarCursorX(){
    if (this->cursor->getE() == NULL)
    {
        return false;
    }

    this->cursor=this->cursor->getE();
    return true;    
}

//---------------------------------------------------------------------------------------------------------------------

bool mapa::avanzarCursorY(){
    if (this->cursor->getN() == NULL)
    {
        return false;
    }

    this->cursor=this->cursor->getN();
    return true;    
}

//---------------------------------------------------------------------------------------------------------------------

bool mapa::avanzarCursorZ(){
    if (this->cursor->getSup() == NULL)
    {
        return false;
    }

    this->cursor=this->cursor->getSup();
    return true;    
}

//---------------------------------------------------------------------------------------------------------------------

bool mapa::retrocederCursorX(){
    if (this->cursor->getW() == NULL)
    {
        return false;
    }

    this->cursor=this->cursor->getW();
    return true;    
}

//---------------------------------------------------------------------------------------------------------------------

bool mapa::retrocederCursorY(){
    if (this->cursor->getS() == NULL)
    {
        return false;
    }

    this->cursor=this->cursor->getS();
    return true;    
}

//---------------------------------------------------------------------------------------------------------------------

bool mapa::retrocederCursorZ(){
    if (this->cursor->getInf() == NULL)
    {
        return false;
    }

    this->cursor=this->cursor->getInf();
    return true;    
}

//---------------------------------------------------------------------------------------------------------------------

void mapa::jumpCursor(unsigned int pos[]){
    if (this->verificarCasilla(pos) == false)
    {
        throw "posicion invalida";
    }

    this->iniciarCursor();

    while (this->cursor->getPos()[0] < pos[0])
    {
        this->avanzarCursorX();
    }

    while (this->cursor->getPos()[1] < pos[1])
    {
        this->avanzarCursorY();
    }

    while (this->cursor->getPos()[2] < pos[2])
    {
        this->avanzarCursorZ();
    }
}

//---------------------------------------------------------------------------------------------------------------------
//                                              METODOS DE UTILIDADES
//---------------------------------------------------------------------------------------------------------------------

bool mapa::verificarCasilla(unsigned int pos []){
    if (pos[0]>this->dimensionXYZ[0])
    {
        return false;
    }
    if (pos[1]>this->dimensionXYZ[1])
    {
        return false;
    }
    if (pos[2]>this->dimensionXYZ[2])
    {
        return false;
    }    

    return true;
}