#include <iostream>
#include <string>
#include <cstdlib>


#include "carta.hpp"
#include "jugador.hpp"
#include "ronda.hpp"
#include "casilla.hpp"
#include "mapa.hpp"
#include "graficador.hpp"

#include "EasyBMP.h"

using namespace std;


int main(){
    mapa* mapita;
    ronda* rondita;

    std::vector<unsigned int> dim ={9,20,1};
    BMP tablero;
/*
    BMP tierra;
    tierra.ReadFromFile("../graphics_20/sky.bmp");

    
    tablero.SetBitDepth( 24 );

    tablero.SetSize(20*dim[0],20*dim[1]);

    RangedPixelToPixelCopy( tierra, 0,tierra.TellWidth()-1,
                         tierra.TellHeight()-1 , 0, 
                         tablero, 0,0 );	
    
    RangedPixelToPixelCopy( tierra, 0,tierra.TellWidth()-1,
                         tierra.TellHeight()-1 , 0, 
                         tablero, 0,20 );

    Rescale(tablero,'H',400);
    tablero.WriteToFile("../tableros/tablero_tst.bmp");
*/

    mapita= new mapa(costa,dim);

    graficador* printer= new graficador(mapita,rondita);

    //printer->selecRutaGraficas("../graphics_20/");
   // printer->cargarGraficas();
   // printer->selecRutaSalida("../tableros/");

    //printer->graficarPantalla("tst");
    int res;
    int dimX;
    int dimY;
    BMP imagen;
    CasillaTipo_T tipo;
    CasillaEstado_T estado;

    res=20; // uso la dimension de las casillas

    tablero.SetBitDepth( 24 );

    dimX=mapita->getDim().data()[0];
    dimY=mapita->getDim().data()[1];
    tablero.SetSize(dimX*res,dimY*res); //seteo las dimensiones del tablero

    mapita->iniciarCursor();

    do // para toda la dimension x
    {   
        do // para toda la dimension y
        {
            tipo=mapita->getTypeCasilla(mapita->getCursor());
            estado=mapita->getStateCasilla(mapita->getCursor());
            imagen.ReadFromFile("../graphics_20/sky.bmp");

            dimX=mapita->getCursor().data()[0];
            dimY=mapita->getCursor().data()[1];

            //en el comando kilometrico de abajo pego la imagen en el lugar del tablero de la casilla apuntada por el cursor
            RangedPixelToPixelCopy( imagen, 0,imagen.TellWidth()-1,imagen.TellHeight()-1 , 0, tablero, int(dimX*res), int(dimY*res)); 

            //ahora avanzo el cursor
        }while(mapita->avanzarCursorY());
        while (mapita->retrocederCursorY())
        {
        }
             
    }while(mapita->avanzarCursorX());

    tablero.WriteToFile("../tableros/tablero_tst.bmp");

    delete mapita;
    delete printer;

    return 0;
}