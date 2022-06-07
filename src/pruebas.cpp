#include <iostream>
#include <string>
#include <cstdlib>


#include "carta.hpp"
#include "jugador.hpp"
#include "ronda.hpp"
#include "casilla.hpp"
#include "mapa.hpp"

#include "EasyBMP.h"

using namespace std;


int main(){
    mapa* mapita;
    BMP tierra;
    tierra.ReadFromFile("../graphics_20/land.bmp");

    BMP tablero;
    tablero.SetBitDepth( 24 );

    std::vector<unsigned int> dim ={3,2,1};
    tablero.SetSize(20*dim[0],20*dim[1]);

    RangedPixelToPixelCopy( tierra, 0,tierra.TellWidth()-1,
                         tierra.TellHeight()-1 , 0, 
                         tablero, 0,0 );	
    
    RangedPixelToPixelCopy( tierra, 0,tierra.TellWidth()-1,
                         tierra.TellHeight()-1 , 0, 
                         tablero, 0,20 );

    Rescale(tablero,'H',400);
    tablero.WriteToFile("../tableros/tablero_tst.bmp");


    mapita= new mapa(costa,dim);

    delete mapita;

    return 0;
}