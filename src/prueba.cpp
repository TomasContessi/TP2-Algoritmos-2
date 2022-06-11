#include <string>
#include <sstream>
#include <fstream>
#include <iostream>

using namespace std;
    
int main(){
    std::ifstream entrada;
    std::string lineaSTR;
    entrada.open("default_config.ini");
    while(std::getline(entrada,lineaSTR)){
        if (lineaSTR[0] != '#') // le saco los comentarios
        {
            std::cout << lineaSTR << std::endl;
        }
    }

    int numerito = atoi( lineaSTR.c_str() );
    std::cout << numerito << std::endl;

    
}