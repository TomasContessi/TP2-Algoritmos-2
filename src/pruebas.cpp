#include <iostream>
#include <string>
#include <cstdlib>


#include "carta.hpp"
#include "jugador.hpp"
#include "ronda.hpp"
#include "casilla.hpp"
#include "mapa.hpp"


using namespace std;


int main(){
    mapa* mapita;
    std::vector<unsigned int> dim ={3,3,1};

    mapita= new mapa(costa,dim);

    delete mapita;

    return 0;
}