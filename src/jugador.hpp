#ifndef JUGADOR_H
#define JUGADOR_H

#include <string>
#include <vector>

#include "estadoJugador.hpp"
#include "carta.hpp"
#include "compararPos.hpp"

class carta;

//---------------------------------------------------------------------------------------------------------------------
//                                   CONTESSI TOMAS 99199 ALORITMOS Y PROGRAMACION II
//---------------------------------------------------------------------------------------------------------------------
//-----------------------------------------------BATALLA CAMPAL 2 V2.1-------------------------------------------------
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
    //pos: establece el jugador pasado como argumento como el siguiente del actual
    void setSiguiente(jugador*);

    //pre:
    //pos: establece el estado del jugador
    void setState(EstadoJugador_T);

    //pre:
    //pos: devuelve el estado del jgador
    EstadoJugador_T getState();

    //pre:
    //pos: devuelve el nombre del jugador
    std::string getName();

    //pre:
    //pos: devuelve el siguiente jugador
    jugador* getSig();

    //pre:
    //pos: cuenta la cantidad de cartas de un tipo que tiene el jugador
    unsigned int contarCartas(TiposCarta_T);

    //pre:
    //pos: devuelve el tipo de carta que el jugador tiene en la posicion especifica
    TiposCarta_T getCardType (unsigned int [3]);

    //pre:
    //pos: devuelve las stats de la carta que el jugador tiene en la casilla especificada
    CardStats getCardStats (unsigned int [3]);
    
    //pre:
    //pos: devuelve la municion restante de la carta que el jugador tiene en la casilla especificada
    int getCardAmmo (unsigned int [3]);

    //pre:
    //pos: hace un disparo y devuelve la municion restante de la carta que el jugador tiene en la casilla especificada
    int shoot (unsigned int [3]);

    //pre:
    //pos: devuelve toda la municion restante
    int getCardAmmo ();

    //pre:
    //pos: recarga la municion de la carta que el jugador tiene en la casilla especificada
    void reloadCardAmmo (unsigned int [3]);

    //pre:
    //pos: recarga toda la municion
    void reloadCardAmmo ();

    //pre:
    //pos:
    bool verificarCarta (std::vector<unsigned int> pos);
    
};


#endif /* JUGADOR_H */