#ifndef RONDA_H
#define RONDA_H

#include <cstdlib>

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
    //pos: devuelve el nombre del jugador en turno
    std::string getJugadorEnTurno();

    //pre:
    //pos: el jugador en turno toma una carta y lee que tipo de carta es
    TiposCarta_T tomarCarta();

    //pre:
    //pos: el jugador en turno toma una carta de un tipo especifico y lee que tipo de carta es
    TiposCarta_T tomarCarta(TiposCarta_T);

    //pre:
    //pos: el jugado en turno posiciona en su mano la nueva carta que tomo
    void jugarCarta(int [3]);

    //pre:
    //pos: el jugador especificado tira la carta especificada
    void tirarCarta(std::string,int [3]);

    //pre:
    //pos: el jugado en turno tira la carta especificada
    void tirarCarta(int [3]);

    //pre:
    //pos: el jugador en turno devuelve la carta que aun no jugo
    void tirarCarta();

    //pre:
    //pos: el jugador en turno mueve una carta de la posicion A a la B
    void moverCarta(int posA[3] , int posB[3]);

    //pre:
    //pos: el jugador especificado cuenta la cantidad de cartas de cierto tipo
    int contarCartas(std::string,TiposCarta_T);

    //pre:
    //pos: el jugador en turno cuenta la cantidad de cartas de cierto tipo
    int contarCartas(TiposCarta_T);

    //pre:
    //pos: el jugador en turno lee las stats de la carta en cierta posicion
    CardStats getCardStats(int [3]);

    //pre:
    //pos: devuelve la municion restante de la carta especifica del jugador en turno
    int getCardAmmo(int [3]);

    //pre:
    //pos: devuelve toda la municion restante del jgador en turno
    int getTotalAmmo();

    //pre:
    //pos: recarga toda la municion del jugador en turno
    void reloadAmmo();

    //pre:
    //pos: el municion efectua un disparo con la carta especificada
    int shoot(int [3]);

    //pre:
    //pos: el jugador en turno lee el tipo de carta en la posicion especifica
    TiposCarta_T getCardType(int [3]);

    //pre:
    //pos: el jugador en turno lee el tipo de carta en la posicion especifica
    TiposCarta_T getCardType(std::string,int [3]);

    //pre:
    //pos: el jugador en turno lee el tipo de carta que tiene en la mano sin jugar
    TiposCarta_T getCardType();

    //pre:
    //pos:
    EstadoJugador_T getPlayerState(std::string);

    //pre:
    //pos:
    bool verificarCartaExistente(std::vector<int>);
};



#endif /* RONDA_H */