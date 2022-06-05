#include "casilla.h"


//---------------------------------------------------------------------------------------------------------------------
//                                   CONTESSI TOMAS 99199 ALORITMOS Y PROGRAMACION II
//---------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------
//                                              METODOS DE LA CLASE CASILLA
//---------------------------------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------------------------------
//                                              CONSTRUCTOR Y DESTRUCTOR
//---------------------------------------------------------------------------------------------------------------------

casilla::casilla(CasillaTipo_T tipo){
    this->posicionXYZ[0]=0;
    this->posicionXYZ[1]=0;
    this->posicionXYZ[2]=0;
    this->estado=libre;
    this->setTipo(tipo);
    this->cSup=NULL;
    this->cInf=NULL;
    this->cN=NULL;
    this->cS=NULL;
    this->cE=NULL;
    this->cW=NULL;
}

//---------------------------------------------------------------------------------------------------------------------

casilla::~casilla(){
    if (this->cSup != NULL)
    {
        this->cSup->setInf(NULL);
    }
    
    if (this->cInf != NULL)
    {
        this->cInf->setSup(NULL);
    }

    if (this->cN != NULL)
    {
        this->cN->setS(NULL);
    }

    if (this->cS != NULL)
    {
        this->cS->setN(NULL);
    }

    if (this->cE != NULL)
    {
        this->cE->setW(NULL);
    }

    if (this->cW != NULL)
    {
        this->cW->setE(NULL);
    }
}

//---------------------------------------------------------------------------------------------------------------------
//                                                   METODOS PRIVADOS
//---------------------------------------------------------------------------------------------------------------------

void casilla::setTipo(CasillaTipo_T tipo){
    this->tipo=tipo;    
}

//---------------------------------------------------------------------------------------------------------------------

bool casilla::verificarContinuidad(casilla* nueva,direccion_T dir){ // esta bien hardcodeada por ahora
    return true;
}

//---------------------------------------------------------------------------------------------------------------------
//                                            METODOS DE OBTENCION DE DATOS
//---------------------------------------------------------------------------------------------------------------------

unsigned int * casilla::getPos(){
    return this->posicionXYZ;
}

//---------------------------------------------------------------------------------------------------------------------

casilla * casilla::getSup(){
    return this->cSup;
}

//---------------------------------------------------------------------------------------------------------------------

casilla * casilla::getInf(){
    return this->cInf;
}

//---------------------------------------------------------------------------------------------------------------------

casilla * casilla::getN(){
    return this->cN;
}

//---------------------------------------------------------------------------------------------------------------------

casilla * casilla::getS(){
    return this->cS;
}

//---------------------------------------------------------------------------------------------------------------------

casilla * casilla::getE(){
    return this->cE;
}

//---------------------------------------------------------------------------------------------------------------------

casilla * casilla::getW(){
    return this->cW;
}

//---------------------------------------------------------------------------------------------------------------------

CasillaEstado_T casilla::getEstado(){
    return this->estado;
}

//---------------------------------------------------------------------------------------------------------------------

CasillaTipo_T casilla::getTippo(){
    return this->tipo;
}

//---------------------------------------------------------------------------------------------------------------------

carta* casilla::getCard(){
    return this->card;
}

//---------------------------------------------------------------------------------------------------------------------
//                                              METODOS DE SETEO DE DATOS
//---------------------------------------------------------------------------------------------------------------------

void casilla::setSup(casilla * nueva){
    if (this->verificarContinuidad(nueva,Sup)==false)
    {
        throw "casilla nueva invalida";
    }   
    this->cSup=nueva;
    if (nueva != NULL)
    {
        this->posicionXYZ[0]=nueva->posicionXYZ[0];
        this->posicionXYZ[1]=nueva->posicionXYZ[1];
        this->posicionXYZ[2]=nueva->posicionXYZ[2]-1;

        nueva->setInf(this);
    }
    
}

//---------------------------------------------------------------------------------------------------------------------

void casilla::setInf(casilla * nueva){
    if (this->verificarContinuidad(nueva,Inf)==false)
    {
        throw "casilla nueva invalida";
    }
    this->cInf=nueva;
    if (nueva != NULL)
    {
        this->posicionXYZ[0]=nueva->posicionXYZ[0];
        this->posicionXYZ[1]=nueva->posicionXYZ[1];
        this->posicionXYZ[2]=nueva->posicionXYZ[2]+1;

        nueva->setSup(this);
    }
}

//---------------------------------------------------------------------------------------------------------------------

void casilla::setN(casilla * nueva){  
    if (this->verificarContinuidad(nueva,N)==false)
    {
        throw "casilla nueva invalida";
    } 
    this->cN=nueva;
    if (nueva != NULL)
    {
        this->posicionXYZ[0]=nueva->posicionXYZ[0];
        this->posicionXYZ[1]=nueva->posicionXYZ[1]-1;
        this->posicionXYZ[2]=nueva->posicionXYZ[2];

        nueva->setS(this);
    }
}

//---------------------------------------------------------------------------------------------------------------------

void casilla::setS(casilla * nueva){
    if (this->verificarContinuidad(nueva,S)==false)
    {
        throw "casilla nueva invalida";
    }
    this->cS=nueva;
    if (nueva != NULL)
    {
        this->posicionXYZ[0]=nueva->posicionXYZ[0];
        this->posicionXYZ[1]=nueva->posicionXYZ[1]+1;
        this->posicionXYZ[2]=nueva->posicionXYZ[2];

        nueva->setN(this);
    }
}

//---------------------------------------------------------------------------------------------------------------------

void casilla::setE(casilla * nueva){
    if (this->verificarContinuidad(nueva,E)==false)
    {
        throw "casilla nueva invalida";
    }
    this->cE=nueva;
    if (nueva != NULL)
    {
        this->posicionXYZ[0]=nueva->posicionXYZ[0]-1;
        this->posicionXYZ[1]=nueva->posicionXYZ[1];
        this->posicionXYZ[2]=nueva->posicionXYZ[2];

        nueva->setW(this);
    }
}

//---------------------------------------------------------------------------------------------------------------------

void casilla::setW(casilla * nueva){
    if (this->verificarContinuidad(nueva,W)==false)
    {
        throw "casilla nueva invalida";
    }
    this->cW=nueva;
    if (nueva != NULL)
    {
        this->posicionXYZ[0]=nueva->posicionXYZ[0]+1;
        this->posicionXYZ[1]=nueva->posicionXYZ[1];
        this->posicionXYZ[2]=nueva->posicionXYZ[2];

        nueva->setE(this);
    }
}

//---------------------------------------------------------------------------------------------------------------------

void casilla::setEstado(CasillaEstado_T estado,carta* card){
    if (estado==ocupada && card == NULL)
    {
        throw "no se puede cambiar a estado ocupado sin una carta";
    }

    this->estado=estado;
    this->card=NULL;

    if (estado==ocupada)
    {
        this->card=card;
    }
    
}

//---------------------------------------------------------------------------------------------------------------------

