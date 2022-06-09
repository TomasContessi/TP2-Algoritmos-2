// cambie a usar este archivo para las pruebas para no perder el otro que andaba

#include <iostream>
#include <string>
#include <cstdlib>


#include "carta.hpp"
#include "jugador.hpp"
#include "ronda.hpp"
#include "casilla.hpp"
#include "mapa.hpp"
#include "graficador.hpp"
#include "gameConfig.hpp"


#include "EasyBMP.h"

using namespace std;

void fun(std::vector<int> * valor){
    (*valor)[0]=27;
}

int main(){
vector<int> n={0};
fun(&n);
cout << n[0] << endl;
}