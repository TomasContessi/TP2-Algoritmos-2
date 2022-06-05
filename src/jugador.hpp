#ifndef JUGADOR_H
#define JUGADOR_H

#include <string>

#include "estadoJugador.hpp"
#include "carta.hpp"

class carta;

//---------------------------------------------------------------------------------------------------------------------
//                                   CONTESSI TOMAS 99199 ALORITMOS Y PROGRAMACION II
//---------------------------------------------------------------------------------------------------------------------
//-----------------------------------------------BATALLA CAMPAL 2 V2.0-------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------
//                                           DEFINICION DE LA CLASE JUGADOR
//---------------------------------------------------------------------------------------------------------------------


class jugador
{
private:
    std::string nombre; //nombre del jugador
    carta* cartas; //lista de cartas que tiene el jugador
    EstadoJugador_T estado; //estado actual del jugador
    jugador * siguienteJugador; //puntero al siguiente jugador en la ronda
public:
    //pre:
    //pos:
    jugador(std::string nombre);

    //pre:
    //pos:
    ~jugador();

    //pre:
    //pos:
    void agregarCarta(carta*);

    //pre:
    //pos:
    void retirarCarta(carta*);

    //pre:
    //pos:
    void setSiguiente(jugador*);

    //pre:
    //pos:
    void setState(EstadoJugador_T);

    //pre:
    //pos:
    EstadoJugador_T getState();

    //pre:
    //pos:
    std::string getName();

    //pre:
    //pos:
    jugador* getSig();

    //pre:
    //pos:
    unsigned int contarCartas(TiposCarta_T);
    
};


#endif /* JUGADOR_H */