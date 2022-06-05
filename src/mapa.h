#ifndef MAPA_H
#define MAPA_H

#include <new>

#include "casilla.h"

//---------------------------------------------------------------------------------------------------------------------
//                                   CONTESSI TOMAS 99199 ALORITMOS Y PROGRAMACION II
//---------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------
//                                              DEFINICION DE LA CLASE MAPA
//---------------------------------------------------------------------------------------------------------------------

enum TipoMapa_T {
    costa,
    isla,
    lago,
    rio,
};

class mapa
{
private:
    casilla *seed;
    casilla *cursor;
    unsigned int dimensionXYZ[3];
    TipoMapa_T tipoMapa;


    //pre:
    //pos: hace un crecimiento en x rellenando las casillas con nivel >0 con aire y las del nivel 0 con tierra
    void xGrow();

    //pre:
    //pos: hace un crecimiento en y rellenando las casillas con nivel >0 con aire y las del nivel 0 con tierra
    void yGrow();

    //pre:
    //pos: hace un crecimiento en z rellenando las casillas con aire
    void zGrow();

    //pre:
    //pos: setea el tipo de las casillas del mapa para construir el mapa elegido
    CasillaTipo_T setCasillaType(TipoMapa_T, unsigned int *);

    //pre:
    //pos: hace un decrecimiento en z 
    void zDecay();

public:
    //pre:
    //pos: crea un mapa de las dimensiones especificadas y del tipo especificada
    mapa(TipoMapa_T,unsigned int []);

    //pre:
    //pos: elimina el mapa
    virtual ~mapa();

    //pre: que la casilla sea valida
    //pos: obtiene el estado de la casilla seleccionada
    CasillaEstado_T getStateCasilla(unsigned int []);

    //pre: que la casilla sea valida
    //pos: obtiene el tipo de la casilla seleccionada
    CasillaTipo_T getTypeCasilla(unsigned int []);

    //pre: que la casilla sea valida
    //pos: devuelve el jugador propietario de la casilla
    jugador* getPropietario(unsigned int []);

    //pre: que la casilla sea valida
    //pos: devuelve la carta que se encuentra ocupando la casilla
    carta* getCard(unsigned int []);

    //pre: que la casilla sea valida
    //pos: ataca la casilla seleccionada y elimina la carta que la ocupe
    void attackCasilla(unsigned int []);

    //pre: que la casilla sea valida
    //pos: la unidad que se encuentre en la casilla la abandona
    void leaveCasilla(unsigned int []);

    //pre: que la casilla sea valida y que la carta tambien
    //pos: la carta toma la casilla seleccionada
    void takeCasilla(unsigned int [],carta*);

    //pre:
    //pos:
    bool verificarCasilla(unsigned int []);

    //pre:
    //pos:
    void iniciarCursor();

    //pre:
    //pos:
    bool avanzarCursorX();

    //pre:
    //pos:
    bool avanzarCursorY();

    //pre:
    //pos:
    bool avanzarCursorZ();

    //pre:
    //pos:
    bool retrocederCursorX();

    //pre:
    //pos:
    bool retrocederCursorY();

    //pre:
    //pos:
    bool retrocederCursorZ();

    //pre:
    //pos:
    void jumpCursor(unsigned int []);
    
    //pre:
    //pos:
    casilla* getCursor();
    
};




#endif /* MAPA_H */