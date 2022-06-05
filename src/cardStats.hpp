#ifndef CARDS_STATS_H
#define CARDS_STATS_H

//---------------------------------------------------------------------------------------------------------------------
//                                   CONTESSI TOMAS 99199 ALORITMOS Y PROGRAMACION II
//---------------------------------------------------------------------------------------------------------------------
//-----------------------------------------------BATALLA CAMPAL 2 V2.1-------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------
//                                   DEFINICION DE LA ESTRUCTURA DE STATS DE LA CARTA
//---------------------------------------------------------------------------------------------------------------------

struct CardStats
{
    int AoE; // area de efecto de la carta, esta en la notacion de todos los juegos
    int alcance; // alcance del ataque
    int disparos; // cantidad de disparos por turno que tiene la carta
    int movimiento [3]; // distancia que se puede mover una carta en un turno en cada terreno. 0 tierra, 1 aire, 2 agua
};

#endif /* CARDS_STATS_H */