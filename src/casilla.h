#ifndef CASILLA_H
#define CASILLA_H


#include "carta.h"

//---------------------------------------------------------------------------------------------------------------------
//                                   CONTESSI TOMAS 99199 ALORITMOS Y PROGRAMACION II
//---------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------
//                                           DEFINICION DE LA CLASE CASILLA
//---------------------------------------------------------------------------------------------------------------------


enum CasillaEstado_T {
    libre,
    ocupada,
    destruida
};

enum CasillaTipo_T {
    aire,
    tierra,
    mar
};

enum direccion_T {
    Sup,
    Inf,
    N,
    S,
    E,
    W
};

class casilla
{
private:
    unsigned int posicionXYZ[3];
    CasillaEstado_T estado;
    carta* card;
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
    unsigned int * getPos();
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
    //pos: devuelve el estado de la casilla
    CasillaEstado_T getEstado();
    //pre:
    //pos: devuelve el tipo de casilla
    CasillaTipo_T getTippo();
    //pre:
    //pos:
    carta* getCard();
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
    //pre: 
    //pos: asigna un estado a la casilla actual y en el caso de estar ocupada le asigna el card
    void setEstado (CasillaEstado_T,carta*);
};




#endif /* CASILLA_H*/