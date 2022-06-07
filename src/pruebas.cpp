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

    std::vector<unsigned int> dim ={21,21,1};
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
    cout<<"starting..."<<endl;
    mapita= new mapa(rio,dim);

    graficador* printer= new graficador(mapita,rondita);

    printer->selecRutaGraficas("../graphics_20/");
    printer->cargarGraficas();
    printer->selecRutaSalida("../tableros/");

    printer->graficarPantalla("tst");

    delete printer;
    delete mapita;

    cout<<"finish"<<endl;
    

    return 0;
}