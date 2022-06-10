#ifndef CASILLA_H
#define CASILLA_H

#include <string>
#include <vector>

#include "casillaEstado.hpp"
#include "casillaTipo.hpp"
#include "direccion.hpp"

//---------------------------------------------------------------------------------------------------------------------
//                                   CONTESSI TOMAS 99199 ALORITMOS Y PROGRAMACION II
//---------------------------------------------------------------------------------------------------------------------
//-----------------------------------------------BATALLA CAMPAL 2 V2.2-------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------
//                                           DEFINICION DE LA CLASE CASILLA
//---------------------------------------------------------------------------------------------------------------------


class casilla
{
private:
    std::vector<int> posicionXYZ;
    CasillaEstado_T estado;
    std::string ocupante;
    CasillaTipo_T tipo;
    casilla * cSup; // mi vida hubiera sido mas facil si esto hubiera sido un vector de punteros, pero ya lo implemente todo
    casilla * cInf;
    casilla * cN;
    casilla * cS;
    casilla * cE;
    casilla * cW;

    bool verificarContinuidad(casilla *,direccion_T);

    //pre:
    //pos: asigna un tipo a la casilla actual
    void setTipo (CasillaTipo_T);

public:

    //pre:
    //pos: genera un objeto casilla del tipo especificado inicicializada todo en 0
    casilla(CasillaTipo_T);

    //pre:
    //pos: elimina el objeto casilla
    virtual ~casilla();

    //pre:
    //pos: devuelve la posicion de la casilla
    std::vector<int> getPos();

    //pre:
    //pos: devuelve un puntero a la casilla qde arriba (z+)
    casilla * getSup();

    //pre:
    //pos: devuelve un puntero a la casilla de abajo (z-)
    casilla * getInf();

    //pre:
    //pos: devuelve un puntero a la casilla de adelante (y+)
    casilla * getN();

    //pre:
    //pos: devuelve un puntero a la casilla de atras (y-)
    casilla * getS();

    //pre:
    //pos: devuelve un puntero a la casilla de la derecha (x+)
    casilla * getE();

    //pre:
    //pos: devuelve un puntero a la casilla de la izquierda (x-)
    casilla * getW();

    //pre:
    //pos:  devuelve el vecino en la direccion indicada
    casilla * getNeighbor(direccion_T);

    //pre:
    //pos: devuelve el estado de la casilla
    CasillaEstado_T getEstado();

    //pre:
    //pos: devuelve el tipo de casilla
    CasillaTipo_T getTipo();

    //pre:
    //pos:
    std::string getOcupante();

    //pre: que la casilla nueva exista y su posicion sea concordante con las otras casillas limitrofes
    //pos: asigna la nueva casilla como superior a la actual y modifica la posicion de la actual para quedar abajo de la nueva
    void setSup (casilla *);

    //pre: que la casilla nueva exista y su posicion sea concordante con las otras casillas limitrofes
    //pos: asigna la nueva casilla como inferior a la actual y modifica la posicion de la actual para quedar encima de la nueva
    void setInf (casilla *);

    //pre: que la casilla nueva exista y su posicion sea concordante con las otras casillas limitrofes
    //pos: asigna la nueva casilla adelante de la actual y modifica la posicion de la actual para quedar detras de la nueva
    void setN (casilla *);

    //pre: que la casilla nueva exista y su posicion sea concordante con las otras casillas limitrofes
    //pos: asigna la nueva casilla atras de la actual y modifica la poscion de la actual para quedar delante de la nueva
    void setS (casilla *);

    //pre: que la casilla nueva exista y su posicion sea concordante con las otras casillas limitrofes
    //pos: asigna la nueva casilla a la derecha de la actual y modifca la posicion de la casilla actual para quedar a la izquierda de la nueva
    void setE (casilla *);

    //pre: que la casilla nueva exista y su posicion sea concordante con las otras casillas limitrofes
    //pos: asigna la nueva casilla a la izquierda de la actual y modifica la posicion de la casilla actual para queda a la derecha de la nueva
    void setW (casilla *);

    //pre: que la casilla nueva exista y su posicion sea concordante con las otras casillas limitrofes
    //pos: asigna la nueva casilla en la direccion indicada respecto de la actual y modifica la posicion de la casilla actual para acomodarse a la nueva
    void  setNeighbor(casilla *,direccion_T);

    //pre: 
    //pos: asigna un estado a la casilla actual y en el caso de estar ocupada le asigna el card
    void setEstado (CasillaEstado_T,std::string);

    //pre:
    //pos:
    void setOcupante (std::string);
};




#endif /* CASILLA_H*/