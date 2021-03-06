#ifndef BATALLA_CAMPAL_H
#define BATALLA_CAMPAL_H

#include <iostream>
//#include <cstdlib>
#include <vector>

#include "gameConfig.hpp"
#include "ronda.hpp"
#include "mapa.hpp"
#include "graficador.hpp"
#include "estadoPartida.hpp"
#include "mensajes.hpp"

//---------------------------------------------------------------------------------------------------------------------
//                                   CONTESSI TOMAS 99199 ALORITMOS Y PROGRAMACION II
//---------------------------------------------------------------------------------------------------------------------
//--------------------------------------------      BATALLA CAMPAL 2      ---------------------------------------------
//---------------------------------------------------------------------------------------------------------------------
//                                     DEFINICION DE LA CLASE BATALLA CAMPAL V1.0.3
//---------------------------------------------------------------------------------------------------------------------




class batallaCampal
{
private:
    mensaje_t mensaje;
    EstadoPartida_T estado; // estado de la partida
    gameConfig* configuracion; // configuracion de la partida
    ronda* rondita;
    mapa* map; // mapa de la partida, es una lista de casillas
    graficador* printer;




    //pre haber cargado previamente la configuracion
    //pos genera el mapa de la partida
    void generarMapa();

    //pre haber cargado previamente la configuracion
    //pos genera la ronda de jugadores
    void generarRonda();

    //pre haber cargado previamente el mapa y la ronda
    //pos genera la clase que se va a usar para graficar
    void generarImpresora();

    //pre que el path de la configuracion tenga un archivo de configuracion valido
    //pos carga la configuracion del path default
    void cargarConfiguracion();

    //pre que el path de la configuracion tenga un archivo de configuracion valido
    //pos carga la configuracion del path especifico
    void cargarConfiguracion(std::string path);

    //pre haber cargado la configuracion y que el idioma sea esp o eng
    //pos carga los mensajes del idioma especificado en la configuracion
    void cargarIdioma();

    //pre haber generado antes la ronda y cargado el idioma
    //pos pregunta si el jugador esta listo
    bool playerReady();

    //pre haber generado antes el mapa, la ronda y cargado el idioma
    //pos realiza la etapa de ataque
    bool atackStage();

    //pre haber generado antes el mapa, la ronda y cargado el idioma
    //pos realiza la etapa de mover tropas
    bool regroupStage();

    //pre haber generado antes el mapa, la ronda y cargado el idioma
    //pos pregunta si queres concervar la carta nueva y tambien realiza la mecanica de las cartas de desastre
    bool cardChoiceStage();

    //pre haber generado antes el mapa, la ronda y cargado el idioma
    //pos carga las coordenadas ingresadas por el usuario
    bool cardSelectionStage(std::vector<int>* pos);

    //pre haber generado antes el mapa, la ronda y cargado el idioma
    //pos usando la carta de la posicion A pide la nueva posicion y realiza el ataque
    bool targetStrikeStage(std::vector<int> posA);

    //pre haber generado antes el mapa, la ronda y cargado el idioma
    //pos similar a targetStrike pero esta mueve la carta a la nueva posicion
    bool moveStage(std::vector<int> posA);

    //pre haber generado antes el mapa, la ronda y cargado el idioma
    //pos similar a atackStage, pero esta no permite seleccionar soldados porque estos no dan ataques adicionales
    bool aditionalAtacksStage();//

    //pre
    //pos pide las coordenadas y las carga en la variable pasada como puntero, devuelve true cuando la operacion termino y false cuando fallo
    bool ingresarPosicion(std::vector<int>*);//

    //pre
    //pos verifica que la carta pueda ser posicionada en la posicion pasada por argumento
    bool verificarPosicionCarta(TiposCarta_T,std::vector<int>);//

    //pre
    //pos verifica que la carta pueda pasar de la posicion A a la posicion B
    bool verificarPosicionCarta(TiposCarta_T,std::vector<int> posA,std::vector<int> posB);//

    //pre
    //pos verifica que la posicion A y la B se encuentren mas cerca que el rango pasado
    bool verificarRange(int range,std::vector<int> posA,std::vector<int> posB);//

    //pre
    //pos elimina a los jugadores que no tienen mas soldados
    void buryBodies();//

    //pre
    //pos ataca a la posicion pasada por argumento con el area de efecto indicada
    void atacarPosicion(int Aoe , std::vector<int> pos);//

    //pre
    //pos ejecuta la mecanica de la carta que se acaba de levantar
    bool ejecuarMecanica();//

public:

    //pre
    //pos crea el objeto batalla campal cy carga la configuracion
    batallaCampal();

    //pre
    //pos destrulle el objeto batalla campal y libera la memoria del mapa y la lista de jugadores
    virtual ~batallaCampal();

    //pre
    //pos inicializa la partida pidiendole a los jugadores que posicionen los soldados iniciales
    void iniciarPartida();

    //pre
    //pos ejecuta el turno del jugador en turno, cambia al siguiente jugador, modifica el mapa y el estado en consecuencia de lo que suceda
    void ejecutarTurno();

    //pre
    //pos verifica el numero de jugadores que aun tienen soldados
    int verificarJugadores();

    //pre que haya un ganador
    //pos imprime un mensaje saludando al jugador ganador
    void saludarGanador();

    //pre
    //pos devuelve el estado de la partida
    EstadoPartida_T getState();

    //pre
    //pos imprime las pantallas de los jugadores
    void printPlayersScreens();
};



#endif /* BATALLA_CAMPAL_H */