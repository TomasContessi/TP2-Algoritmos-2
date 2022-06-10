#ifndef BATALLA_CAMPAL_H
#define BATALLA_CAMPAL_H

#include <iostream>
#include <cstdlib>
#include <vector>

#include "gameConfig.hpp"
#include "ronda.hpp"
#include "mapa.hpp"
#include "graficador.hpp"

//---------------------------------------------------------------------------------------------------------------------
//                                   CONTESSI TOMAS 99199 ALORITMOS Y PROGRAMACION II
//---------------------------------------------------------------------------------------------------------------------
//-----------------------------------------------BATALLA CAMPAL 2 V2.2-------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------
//                                        DEFINICION DE LA CLASE BATALLA CAMPAL
//---------------------------------------------------------------------------------------------------------------------

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
    std::string listo;
    std::string Y_N;
    std::string casillaInvalida;
    std::string deseaAtacar;
    std::string deseaMover;
    std::string aunDeseaMover;
    std::string aunDeseaAtacar;


    std::string moviendoTropas;
    std::string casillaOcupada;
    std::string casillaDestruida;
    std::string municionesRestantes;
    std::string tropasPerdidas;

    std::string noSoldados;

    std::string ataqueExitoso;

    std::string conservarCarta;
    std::string ingreseCoordenada;
    std::vector<std::string> coordenadas;
    std::vector<std::string> tiposDeCartas;
    std::string coordenadaInvalida;
    std::string cartaPosInvalid;
    std::string elegirCarta;

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
    ronda* rondita;
    mapa* map; // mapa de la partida, es una lista de casillas
    graficador* printer;




    //pre
    //pos genera el mapa de la partida
    void generarMapa();//

    //pre
    //pos
    void generarRonda();//

    //pre
    //pos
    void generarImpresora();//

    //pre
    //pos
    void cargarConfiguracion();//

    //pre
    //pos
    void cargarConfiguracion(std::string);//

    //pre
    //pos
    void cargarIdioma();

    //pre
    //pos
    bool playerReady();//

    //pre
    //pos
    bool atackStage();//

    //pre
    //pos
    bool regroupStage();//

    //pre
    //pos
    bool cardChoiceStage();//

    //pre
    //pos
    bool cardSelectionStage(std::vector<int>*);//

    //pre
    //pos
    bool targetStrikeStage(std::vector<int>);//

    //pre
    //pos
    bool moveStage(std::vector<int>);//

    //pre
    //pos
    bool aditionalAtacksStage();//

    //pre
    //pos
    bool ingresarPosicion(std::vector<int>*);//

    //pre
    //pos
    bool verificarPosicionCarta(TiposCarta_T,std::vector<int>);//

    //pre
    //pos
    bool verificarPosicionCarta(TiposCarta_T,std::vector<int> posA,std::vector<int> posB);//

    //pre
    //pos
    bool verificarRange(int range,std::vector<int> posA,std::vector<int> posB);//

    //pre
    //pos
    void buryBodies();//

    //pre
    //pos
    void atacarPosicion(int Aoe , std::vector<int> pos);//

    //pre
    //pos
    bool ejecuarMecanica();//

public:

    //pre
    //pos crea el objeto batalla campal cy carga la configuracion
    batallaCampal();

    //pre
    //pos destrulle el objeto batalla campal y libera la memoria del mapa y la lista de jugadores
    virtual ~batallaCampal();

    //pre
    //pos
    void iniciarPartida();

    //pre
    //pos ejecuta el turno del jugador en turno, cambia al siguiente jugador, modifica el mapa y el estado en consecuencia de lo que suceda
    void ejecutarTurno();

    //pre
    //pos
    int verificarJugadores();

    //pre que haya un ganador
    //pos imprime un mensaje saludando al jugador ganador
    void saludarGanador();

    //pre
    //pos
    EstadoPartida_T getState();

    //pre
    //pos
    void printPlayersScreens();
};



#endif /* BATALLA_CAMPAL_H */