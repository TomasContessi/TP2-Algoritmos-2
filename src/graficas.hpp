#ifndef GRAFICAS_H
#define GRAFICAS_H

#include "EasyBMP.h"

//---------------------------------------------------------------------------------------------------------------------
//                                   CONTESSI TOMAS 99199 ALORITMOS Y PROGRAMACION II
//---------------------------------------------------------------------------------------------------------------------
//-----------------------------------------------BATALLA CAMPAL 2 V2.2-------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------
//                                       DEFINICION DE LA ESTRUCTURA DE GRAFICAS
//---------------------------------------------------------------------------------------------------------------------

struct graficas_t
{
    BMP land;
    BMP air;
    BMP water;
    BMP landDestroyed;

    BMP misil;
    BMP avion;
    BMP barco;
    BMP bomba;
    BMP dirigible;
    BMP soldado;

    BMP allyGrid;
    BMP enemyGrid;
   // BMP fondo;
};



#endif /* GRAFICAS_H */