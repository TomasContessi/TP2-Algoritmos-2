#ifndef TIPOS_CARTA
#define TIPOS_CARTA

//---------------------------------------------------------------------------------------------------------------------
//                                   CONTESSI TOMAS 99199 ALORITMOS Y PROGRAMACION II
//---------------------------------------------------------------------------------------------------------------------
//-----------------------------------------------BATALLA CAMPAL 2 V2.0-------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------
//                                          DEFINICION DE TIPOS DE LAS CARTAS
//---------------------------------------------------------------------------------------------------------------------

enum TiposCarta_T {
    misil,
    avion,
    barco,
    bomba_atomica, // si se tiene un avion se puede lanzar una bomba atomica que rompe 10x10x10
    dirigible,  // hace visible al enemigo, pero tambien es visible a el
    ciclon, // elimina TODAS las unidades aereas
    terremoto, // elimina TODAS las construcciones terrestres (los cilos de misiles)
    tsunami, // elimina TODAS las unidades navales
    soldado // el tipo de unidad por defecto
};

#endif /* TIPOS_CARTA */