#include "casilla.hpp"


//---------------------------------------------------------------------------------------------------------------------
//                                   CONTESSI TOMAS 99199 ALORITMOS Y PROGRAMACION II
//---------------------------------------------------------------------------------------------------------------------
//-----------------------------------------------BATALLA CAMPAL 2 V2.2-------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------
//                                              METODOS DE LA CLASE CASILLA
//---------------------------------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------------------------------
//                                              CONSTRUCTOR Y DESTRUCTOR
//---------------------------------------------------------------------------------------------------------------------

casilla::casilla(CasillaTipo_T tipo){
    this->posicionXYZ={0,0,0};
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

std::vector<int> casilla::getPos(){
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

casilla * casilla::getNeighbor(direccion_T dir){
    switch (dir)
    {
    case Sup:
        return this->getSup();
        break;

    case Inf:
        return this->getInf();
        break;

    case N:
        return this->getN();
        break;

    case S:
        return this->getS();
        break;

    case E:
        return this->getE();
        break;

    case W:
        return this->getW();
        break;
    
    default:
    throw "direccion invalida";
        break;
    }
}

//---------------------------------------------------------------------------------------------------------------------

CasillaEstado_T casilla::getEstado(){
    return this->estado;
}

//---------------------------------------------------------------------------------------------------------------------

CasillaTipo_T casilla::getTipo(){
    return this->tipo;
}

//---------------------------------------------------------------------------------------------------------------------

std::string casilla::getOcupante(){
    return this->ocupante;
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

        if (nueva->getInf() != this)
        {
            nueva->setInf(this);
        }
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

        if (nueva->getSup() != this)
        {
            nueva->setSup(this);
        }
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

        if (nueva->getS() != this)
        {
            nueva->setS(this);
        }
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

        if (nueva->getN() != this)
        {
            nueva->setN(this);
        }
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

        if (nueva->getW() != this)
        {
            nueva->setW(this);
        }
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

        if (nueva->getE() != this)
        {
            nueva->setE(this);
        }
    }
}

//---------------------------------------------------------------------------------------------------------------------

void  casilla::setNeighbor(casilla * nueva,direccion_T dir){
    switch (dir)
    {
    case Sup:
        this->setSup(nueva);
        break;

    case Inf:
        this->setInf(nueva);
        break;

    case N:
        this->setN(nueva);
        break;

    case S:
        this->setS(nueva);
        break;

    case E:
        this->setE(nueva);
        break;

    case W:
        this->setW(nueva);
        break;
    
    default:
    throw "direccion invalida";
        break;
    }
}

//---------------------------------------------------------------------------------------------------------------------

void casilla::setEstado(CasillaEstado_T estado,std::string nombre){

    this->estado=estado;
    this->ocupante="";

    if (estado==ocupada)
    {
        this->ocupante=nombre;
    }
    
}

//---------------------------------------------------------------------------------------------------------------------

void casilla::setOcupante (std::string nombre){
    this->ocupante=nombre;
}