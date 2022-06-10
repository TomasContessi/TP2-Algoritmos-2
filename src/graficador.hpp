#ifndef GRAFICADOR_H
#define GRAFICADOR_H

#include <vector>
#include <sstream>

#include "EasyBMP.h"

#include "mapa.hpp"
#include "ronda.hpp"
#include "graficas.hpp"

//---------------------------------------------------------------------------------------------------------------------
//                                   CONTESSI TOMAS 99199 ALORITMOS Y PROGRAMACION II
//---------------------------------------------------------------------------------------------------------------------
//--------------------------------------------      BATALLA CAMPAL 2      ---------------------------------------------
//---------------------------------------------------------------------------------------------------------------------
//                                       DEFINICION DE LA CLASE GRAFICADOR V2.3
//---------------------------------------------------------------------------------------------------------------------

class graficador
{
private:

    BMP tablero;
    BMP pantalla;
    graficas_t graficas;

    ronda* rondita;
    mapa* mapita;

    std::string observador;
    std::string rutaSalida;
    std::string rutaGraficas;

    bool mapaVisible;

    int lvl;



    //pre:
    //pos: construye el tablero que se va a mostrar sin las cartas y lo guarda en tablero
    void construirTablero();

    //pre:
    //pos: agrega las cartas al tablero y lo guarda en pantalla
    void agregarCartas();

    //pre:
    //pos: agrega el fondo al tablero y lo guarda en pantalla
    void agregarFondo();

    //pre:
    //pos: le agrega las cartas y el fondo al tablero y lo guarda en pantalla
    void contruirPantalla();

    //pre:
    //pos:
    void imgSelector(BMP,CasillaTipo_T,CasillaEstado_T);

    //pre:
    //pos:
    BMP imgSelector(TiposCarta_T);

    //pre:
    //pos: grafica la pantalla que ve el jugador especificado
    void graficarNivel(std::string);

    public:

    //pre:
    //pos: crea un objeto graficador
    graficador(mapa*,ronda*);

    //pre:
    //pos: destruye el graficador
    ~graficador();

    //pre:
    //pos: grafica la pantalla que ve el jugador especificado
    void graficarPantalla(std::string, int niveles);

    //pre:
    //pos: selecciona la ruta donde se van a buscar las graficas
    void selecRutaGraficas(std::string);

    //pre:
    //pos: selecciona la ruta donde se van a guardar las pantallas
    void selecRutaSalida(std::string);

    //pre:
    //pos: carga la estructura de graficas leyendolas de la ruta especifiada en rutaGraficas
    void cargarGraficas();

    //pre:
    //pos:
    void enmascarar(bool);

    //pre:
    //pos:
    void cargarMapa(mapa*,ronda*);

    //pre:
    //pos:
    void cambiarFondo(std::string);

};


#endif /* GRAFICADOR_H */