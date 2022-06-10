#include "mapa.hpp"


//---------------------------------------------------------------------------------------------------------------------
//                                   CONTESSI TOMAS 99199 ALORITMOS Y PROGRAMACION II
//---------------------------------------------------------------------------------------------------------------------
//-----------------------------------------------BATALLA CAMPAL 2 V2.2-------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------
//                                              METODOS DE LA CLASE MAPA
//---------------------------------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------------------------------
//                                              CONSTRUCTOR Y DESTRUCTOR
//---------------------------------------------------------------------------------------------------------------------

mapa::mapa(TipoMapa_T tipoDeMapa,std::vector<int>  dimension){
    CasillaTipo_T tipoDeCasilla;
    std::vector<int>  pos={0,0,0};

    this->tipoMapa=tipoDeMapa;
    this->dimensionXYZ=dimension;

    tipoDeCasilla=this->setCasillaType(tipoDeMapa,pos);

    this->seed=new casilla(tipoDeCasilla); // creo la primera casilla
    this->iniciarCursor();

    // ahora creo un mapa de las dimensiones que me piden
    for (int i = 1; i < dimension[0]; i++)
    {
        this->xGrow();
    }
    for (int i = 1; i < dimension[1]; i++)
    {
        this->yGrow();
    }
    for (int i = 1; i < dimension[2]; i++)
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
            std::vector<int>  nuevaPosicion = this->cursor->getPos();
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

            if (this->cursor->getSup()!=NULL)
            {
                nueva->setSup(this->cursor->getSup()->getE());// si tengo una capa abajo conecto la nueva con la que esta abajo
            }

            if (this->cursor->getN()!=NULL)
            {
                nueva->setN(this->cursor->getN()->getE());// si tengo una capa al sur conecto la nueva con la que esta al sur
            }

            // una vez conectada la nueva casilla avanzo 1 en z el cursor
        }while(this->avanzarCursorZ());

        // una vez avanzado todo el cursor en z avanzo 1 en y

        while(this->cursor->getInf()!=NULL)
        {
            this->retrocederCursorZ(); // y devuelvo el carro a z=0
        }

    }while (this->avanzarCursorY());
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
            std::vector<int>  nuevaPosicion = this->cursor->getPos();
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

            if (this->cursor->getSup()!=NULL)
            {
                nueva->setSup(this->cursor->getSup()->getN());// si tengo una capa abajo conecto la nueva con la que esta abajo
            }

            if (this->cursor->getE()!=NULL)
            {
                nueva->setE(this->cursor->getE()->getN());// si tengo una capa al oeste conecto la nueva con la que esta al oeste
            }

            // una vez conectada la nueva casilla avanzo 1 en z el cursor
        }while(this->avanzarCursorZ());

        // una vez avanzado todo el cursor en z avanzo 1 en x

        while(this->cursor->getInf()!=NULL)
        {
            this->retrocederCursorZ(); // y devuelvo el carro a z=0
        }

    }while (this->avanzarCursorX());
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
            std::vector<int>  nuevaPosicion = this->cursor->getPos();
            nuevaPosicion[2]++;
            nueva= new casilla(this->setCasillaType(this->tipoMapa,nuevaPosicion)); //creo una nueva casilla
            nueva->setInf(this->cursor); //conecto la nueva casilla con el cursor abajo

            if (this->cursor->getS()!=NULL)
            {
                nueva->setS(this->cursor->getS()->getSup());// si tengo una capa al sur conecto la nueva con la que esta al sur
            }

            if (this->cursor->getW()!=NULL)
            {
                nueva->setW(this->cursor->getW()->getSup());// si tengo una capa a la izquierda conecto la nueva con la que esta a la izquierda
            }

            if (this->cursor->getN()!=NULL)
            {
                nueva->setN(this->cursor->getN()->getSup());// si tengo una capa al sur conecto la nueva con la que esta al sur
            }

            if (this->cursor->getE()!=NULL)
            {
                nueva->setE(this->cursor->getE()->getSup());// si tengo una capa a la izquierda conecto la nueva con la que esta a la izquierda
            }

            // una vez conectada la nueva casilla avanzo 1 en x el cursor
        }while(this->avanzarCursorX());

        // una vez avanzado todo el cursor en z avanzo 1 en y

        while(this->cursor->getW()!=NULL)
        {
            this->retrocederCursorX(); // y devuelvo el carro a x=0
        }

    }while (this->avanzarCursorY());
}

//---------------------------------------------------------------------------------------------------------------------

CasillaTipo_T mapa::setCasillaType(TipoMapa_T tipo, std::vector<int> posicion){

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

        if (posicion[2]<1 && posicion[0] >= this->dimensionXYZ[0]/2)
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
        
        if (posicion[1] >= this->dimensionXYZ[1]/3 && posicion[0] >= this->dimensionXYZ[0]/3)
        {
            if (posicion[1] < 2*(this->dimensionXYZ[1])/3 && posicion[0] < 2*(this->dimensionXYZ[0])/3)
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
        
        if (posicion[1] >= this->dimensionXYZ[1]/3 && posicion[0] >= this->dimensionXYZ[0]/3)
        {
            if (posicion[1] < 2*(this->dimensionXYZ[1])/3 && posicion[0] < 2*(this->dimensionXYZ[0])/3)
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
        
        if (posicion[1] >= this->dimensionXYZ[1]/3 && posicion[1] < 2*(this->dimensionXYZ[1])/3)
        {
            return mar;
        }

        return tierra;
        
        break;
    
    default:
        throw "tipo de mapa invalido";

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

            delete this->cursor->getN(); // borro la casilla al norte del cursor
        }

        this->retrocederCursorX();

        delete this->cursor->getE(); // borro la casilla al este del cursor

        while (this->cursor->getN() != NULL) // mientras tengo casillas al norte
        {
            this->avanzarCursorY(); // levo el cursor hasta arriba todo al norte
        }
    }

    while (this->cursor->getS() != NULL)
     {
        this->retrocederCursorY();

        delete this->cursor->getN(); // borro la casilla al norte del cursor
    }

    if (cursor==seed)
    {
        seed=NULL;
    }
    
    delete this->cursor; // por ultimo mato la ultima casilla del nivel  
}

//---------------------------------------------------------------------------------------------------------------------
//                                          METODOS DE MODIFICACION DE CASILLAS
//---------------------------------------------------------------------------------------------------------------------

void mapa::attackCasilla(std::vector<int> pos){
    this->jumpCursor(pos);

    this->cursor->setOcupante("");

    if(this->cursor->getTipo() == tierra)
    {
        this->cursor->setEstado(destruida,"");
    }else
    {
        this->cursor->setEstado(libre,"");
    }
}

//---------------------------------------------------------------------------------------------------------------------

void mapa::leaveCasilla(std::vector<int> pos){
    this->jumpCursor(pos);

    this->cursor->setEstado(libre,"");
}

//---------------------------------------------------------------------------------------------------------------------

void mapa::takeCasilla(std::vector<int> pos,std::string nombre){
    if (nombre == "")
    {
        throw "nombre nulo";
    }

    this->jumpCursor(pos);

    switch (this->cursor->getEstado())
    {
    case libre:
        this->cursor->setEstado(ocupada , nombre);
        break;

    case ocupada:
        throw "la casilla estaba ocupada";
        break;

    case destruida:
        throw "la casilla estaba destruida";
        break;
    
    default:
        throw "estado invalido";
        break;
    }    
}

//---------------------------------------------------------------------------------------------------------------------
//                                          METODOS DE OBTENCION DE DATOS
//---------------------------------------------------------------------------------------------------------------------

CasillaEstado_T mapa::getStateCasilla(std::vector<int> pos){
    this->jumpCursor(pos);
    return this->cursor->getEstado();
}

//---------------------------------------------------------------------------------------------------------------------

CasillaTipo_T mapa::getTypeCasilla(std::vector<int> pos){
    this->jumpCursor(pos);
    return this->cursor->getTipo();
}



//---------------------------------------------------------------------------------------------------------------------

std::string mapa::getPropietario(std::vector<int> pos){
    this->jumpCursor(pos);
    return this->cursor->getOcupante();
}

//---------------------------------------------------------------------------------------------------------------------
std::vector<int> mapa::getCursor(){
    return this->cursor->getPos();
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

bool mapa::stepCursor(direccion_T dir){
    switch (dir)
    {
    case Sup:
        return this->avanzarCursorZ();
        break;

    case Inf:
        return this->retrocederCursorZ();
        break;

    case N:
        return this->avanzarCursorY();
        break;

    case S:
        return this->retrocederCursorY();
        break;

    case E:
        return this->avanzarCursorX();
        break;

    case W:
        return this->retrocederCursorX();
        break;
    
    default:
    throw "direccion invalida";
        break;
    }
}

//---------------------------------------------------------------------------------------------------------------------


void mapa::jumpCursor(std::vector<int> pos){
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

bool mapa::verificarCasilla(std::vector<int> pos){
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

//---------------------------------------------------------------------------------------------------------------------

std::vector<int> mapa::getDim(){
    return this->dimensionXYZ;
}