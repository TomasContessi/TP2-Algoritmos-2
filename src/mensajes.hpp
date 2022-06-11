//---------------------------------------------------------------------------------------------------------------------
//                                   CONTESSI TOMAS 99199 ALORITMOS Y PROGRAMACION II
//---------------------------------------------------------------------------------------------------------------------
//--------------------------------------------      BATALLA CAMPAL 2      ---------------------------------------------
//---------------------------------------------------------------------------------------------------------------------
//                                       DEFINICION DE LA ESTRUCTURA MENSAJE V1
//---------------------------------------------------------------------------------------------------------------------
#include <vector>
#include <string>

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