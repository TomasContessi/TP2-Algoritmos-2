#ifndef BATALLA_CAMPAL_H
#define BATALLA_CAMPAL_H


#include "gameConfig.h"
#include "jugador.h"
#include "mapa.h"

enum EstadoPartida_T {
    iniciando,
    jugando,
    pausada,
    terminada
};

class batallaCampal
{
private:
    EstadoPartida_T estado; // estado de la partida
    gameConfig configuracion; // configuracion de la partida
    jugador * jugadorEnTurno; // puntero al jugador en turno
    jugador * ganador; // puntero al jugador que gano la partida
    mapa mapa; // mapa de la partida, es una lista de casillas
public:
    //pre
    //pos crea el objeto batalla campal cy carga la configuracion
    batallaCampal();
    //pre
    //pos destrulle el objeto batalla campal y libera la memoria del mapa y la lista de jugadores
    virtual ~batallaCampal();
    //pre
    //pos genera el mapa de la partida
    void generarMapa();
    //pre
    //pos ejecuta el turno del jugador en turno, cambia al siguiente jugador, modifica el mapa y el estado en consecuencia de lo que suceda
    void ejecutarTurno();
    //pre que haya un ganador
    //pos imprime un mensaje saludando al jugador ganador
    void saludarGanador();
};



#endif /* BATALLA_CAMPAL_H */