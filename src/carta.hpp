#ifndef CARTA_H
#define CARTA_H

#include <string>

#include "tiposCarta.hpp"
#include "estadoCarta.hpp"
#include "cardStats.hpp"


//---------------------------------------------------------------------------------------------------------------------
//                                   CONTESSI TOMAS 99199 ALORITMOS Y PROGRAMACION II
//---------------------------------------------------------------------------------------------------------------------
//-----------------------------------------------BATALLA CAMPAL 2 V2.1-------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------
//                                           DEFINICION DE LA CLASE CARTA
//---------------------------------------------------------------------------------------------------------------------



class carta
{
private:
    std::string propieario;

    TiposCarta_T tipo; // de que tipo es esta carta
    CardStats stats; // stats de ataque y movimiento de la carta
    EstadoCarta_T estado; // si la carta esta en mano o en juego

    int municionRestante;

    unsigned int posicion [3]; // posicion de la carta en el tablero

    carta* siguienteCarta; // siguiente carta de la lista

    //pre: el tipo de carta debe ser valido
    //pos: carga todos los datos referentes a ese tipo de carta en la carta
    void setType (TiposCarta_T);

public:
    //pre: el jugador y el tipo de carta deben ser validos
    //pos: crea una carta perteneciente al jugador especificado y con el tipo especificado
    carta(std::string,TiposCarta_T);

    //pre:
    //pos: elimina la carta
    virtual ~carta();

    //pre:
    //pos: devuelve el propietario de la casilla
    std::string getPropietario();

    //pre: el estado debe ser valido
    //pos: carga el estado a la carta
    void setState (EstadoCarta_T);

    //pre: 
    //pos: carga el puntero pasado en el valor next
    void setNext (carta*);

    //pre: la posicion debe ser un vector de 3 unsigned int
    //pos: carga el estado a la carta
    void setPos (unsigned int [3]);

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

    //pre:
    //pos: devuelve la posicion de la carta en el mapa
    unsigned int* getPos();

    //pre:
    //pos: devuelve las estadisticas de la carta
    CardStats getStats();

    //pre:
    //pos: devuelve la municion restante
    int getAmmo();

    //pre:
    //pos: efectua un disparo y devuelve la municion restante
    int shoot();

    //pre:
    //pos: recarga la municion
    void reloadAmmo();
        
};

#endif /* CARTA_H */