#ifndef CARTA_H
#define CARTA_H

#include "jugador.h"
#include "tiposCarta.h"


//---------------------------------------------------------------------------------------------------------------------
//                                   CONTESSI TOMAS 99199 ALORITMOS Y PROGRAMACION II
//---------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------
//                                             DEFINICION DE LA CLASE CARTA
//---------------------------------------------------------------------------------------------------------------------

class jugador;

enum EstadoCarta_T {
    mano,
    juego
};

class carta
{
private:
    jugador* propieario;

    TiposCarta_T tipo; // de que tipo es esta carta
    EstadoCarta_T estado; // si la carta esta en mano o en juego
    int AoE; // area de efecto de la carta, esta en la notacion de todos los juegos
    int alcance; // alcance del ataque
    int disparos; // cantidad de disparos por turno que tiene la carta
    int movimiento [3]; // distancia que se puede mover una carta en un turno en cada terreno. 0 tierra, 1 aire, 2 agua

    carta* siguienteCarta; // siguiente carta de la lista

    //pre: el tipo de carta debe ser valido
    //pos: carga todos los datos referentes a ese tipo de carta en la carta
    void setType (TiposCarta_T);

public:
    //pre: el jugador y el tipo de carta deben ser validos
    //pos: crea una carta perteneciente al jugador especificado y con el tipo especificado
    carta(jugador*,TiposCarta_T);

    //pre:
    //pos: elimina la carta
    virtual ~carta();

    //pre:
    //pos: devuelve el propietario de la casilla
    jugador* getPropietario();

    //pre: el estado debe ser valido
    //pos: carga el estado a la carta
    void setState (EstadoCarta_T);

    //pre: 
    //pos: carga el puntero pasado en el valor next
    void setNext (carta*);

    //pre:
    //pos: devuelve el tipo de carta
    TiposCarta_T getType ();

    //pre:
    //pos: devuelve el estado de la carta
    EstadoCarta_T getState ();

    //pre:
    //pos: devuelve el area de efecto de la carta
    int getAoE();

    //pre:
    //pos: devuelve el rango de la carta
    int getRange();

    //pre:
    //pos: devuelve la siguiene carta
    carta* getNext();
    
};

#endif /* CARTA_H */