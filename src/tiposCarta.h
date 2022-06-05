#ifndef TIPOS_CARTA
#define TIPOS_CARTA

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