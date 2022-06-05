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
    //pos: crea un jugador con su nombre e inicializa su estado como activo y su mazo de cartas y siguiente en NULL
    jugador(std::string nombre);

    //pre:
    //pos: livera la memoria de la pila de cartas y elimina al jugador
    ~jugador();

    //pre:
    //pos: agrega la carta a la pila del jugador
    void agregarCarta(carta*);

    //pre:
    //pos: retira la carta de la pila del jugador
    void retirarCarta(unsigned int [3]);

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