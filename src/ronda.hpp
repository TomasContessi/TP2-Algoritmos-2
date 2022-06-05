#ifndef RONDA_H
#define RONDA_H

#include "jugador.hpp"

//---------------------------------------------------------------------------------------------------------------------
//                                   CONTESSI TOMAS 99199 ALORITMOS Y PROGRAMACION II
//---------------------------------------------------------------------------------------------------------------------
//-----------------------------------------------BATALLA CAMPAL 2 V2.1-------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------
//                                           DEFINICION DE LA CLASE RONDA
//---------------------------------------------------------------------------------------------------------------------

class ronda
{
private:
    jugador* jugadores; // primer jugador de la ronda
    jugador* jugadorEnTurno; // jugador que actualmente esta en turno

    carta* nuevaCarta; //la nueva carta que toma el jugador

public:

    //pre:
    //pos: crea un objeto de ronda vacio con los jugadores inicializados a NULL
    ronda();

    //pre:
    //pos: desocupa la memoria de los jugadores y elimina la ronda
    virtual ~ronda();

    //pre:
    //pos: agrega el jugador al final de la ronda
    void agregarJugador(jugador*);

    //pre:
    //pos: elimina el jugador especificado
    void eliminarJugador(std::string);

    //pre:
    //pos: elimina el jugador en turno
    void eliminarJugador();

    //pre:
    //pos: cuenta la cantidad de jugadores activos
    int contarJugadores();

    //pre:
    //pos: inicia el jugador en turno como el primero de la ronda
    void iniciarRonda();

    //pre:
    //pos: avanza un turno la ronda
    void avanzarTurno();

    //pre:
    //pos: el jugador en turno toma una carta y lee que tipo de carta es
    TiposCarta_T tomarCarta();

    //pre:
    //pos: el jugador en turno toma una carta de un tipo especifico y lee que tipo de carta es
    TiposCarta_T tomarCarta(TiposCarta_T);

    //pre:
    //pos: el jugado en turno posiciona en el mapa y su mano la nueva carta que tomo
    void jugarCarta(unsigned int [3]);

    //pre:
    //pos: el jugador especificado tira la carta especificada
    void tirarCarta(std::string,unsigned int [3]);

    //pre:
    //pos: el jugado en turno tira la carta especificada
    void tirarCarta(unsigned int [3]);

    //pre:
    //pos: el jugador en turno devuelve la carta que aun no jugo
    void tirarCarta();

    //pre:
    //pos: el jugador en turno mueve una carta de la posicion A a la B
    void moverCarta(unsigned int posA[3] , unsigned int posB[3]);

    //pre:
    //pos: el jugador especificado cuenta la cantidad de cartas de cierto tipo
    int contarCartas(std::string,TiposCarta_T);

    //pre:
    //pos: el jugador en turno cuenta la cantidad de cartas de cierto tipo
    int contarCartas(TiposCarta_T);

    //pre:
    //pos: el jugador en turno lee las stats de la carta en cierta posicion
    CardStats getCardStats(unsigned int [3]);

    //pre:
    //pos: el jugador en turno lee el tipo de carta en la posicion especifica
    TiposCarta_T getCardType(unsigned int [3]);
};



#endif /* RONDA_H */