#ifndef BATALLA_CAMPAL_H
#define BATALLA_CAMPAL_H


#include "gameConfig.hpp"
#include "ronda.hpp"
#include "mapa.hpp"
#include "graficador.hpp"

enum EstadoPartida_T {
    iniciando,
    jugando,
    pausada,
    terminada
};

struct mensaje_t // aca voy a ir cargando los mensajes que voy a mostrar por consola y con un metodo puedo cambiar el idioma
{   
    std::string bienvenida;
    std::string ingreseNombre;
    std::string cartas;
    std::string aviones;
    std::string misiles;
    std::string barcos;
    std::string soldados;
    std::string dirigibles;

};


class batallaCampal
{
private:
    mensaje_t mensaje;
    EstadoPartida_T estado; // estado de la partida
    gameConfig* configuracion; // configuracion de la partida
    ronda* ronda;
    mapa* mapa; // mapa de la partida, es una lista de casillas
    graficador* printer;
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