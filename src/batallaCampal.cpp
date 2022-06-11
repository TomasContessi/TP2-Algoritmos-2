#include <iostream>
#include <string>
#include <vector>

#include "batallaCampal.hpp"

using namespace std;

//---------------------------------------------------------------------------------------------------------------------
//                                   CONTESSI TOMAS 99199 ALORITMOS Y PROGRAMACION II
//---------------------------------------------------------------------------------------------------------------------
//--------------------------------------------      BATALLA CAMPAL 2      ---------------------------------------------
//---------------------------------------------------------------------------------------------------------------------
//                                    IMPLEMENTACION DE LA CLASE BATALLA CAMPAL V2.3
//---------------------------------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------------------------------
//                                              CONSTRUCTOR Y DESTRUCTOR
//---------------------------------------------------------------------------------------------------------------------


batallaCampal::batallaCampal(){
    this->estado = iniciando;
    this->configuracion = NULL;
    this->map = NULL;
    this->rondita = NULL;
    this->printer = NULL;

    this->cargarConfiguracion(); // muy importante que esto sea lo primero que hace el tda

    this->rondita->iniciarRonda();
}

//---------------------------------------------------------------------------------------------------------------------

batallaCampal::~batallaCampal(){
    delete this->printer;
    delete this->rondita;
    delete this->map;
    delete this->configuracion;
}

//---------------------------------------------------------------------------------------------------------------------
//                                                  METODOS PRIVADOS
//---------------------------------------------------------------------------------------------------------------------

//                                              METODOS DE CONFIGURACION
//---------------------------------------------------------------------------------------------------------------------

void batallaCampal::generarMapa(){
    if (this->map != NULL)
    {
        delete this->map;
    }

    this->map  = new mapa(this->configuracion->getMapType(),this->configuracion->getDimXYZ());
}

//---------------------------------------------------------------------------------------------------------------------

void batallaCampal::generarRonda(){
    if (this->rondita != NULL)
    {
        delete this->rondita;
    }

    this->rondita = new ronda(); // pido memoria para la ronda

    for (int i = 0; i < this->configuracion->getPlayerNames().size(); i++) //cargo los jugadores en la ronda
    {
        this->rondita->agregarJugador(new jugador (this->configuracion->getPlayerNames()[i]));// voy agregando el nuevo jugador con el nombre que tengo
    }   
}

//---------------------------------------------------------------------------------------------------------------------

void batallaCampal::generarImpresora(){
    if (this->printer != NULL)
    {
        delete this->printer;
    }

    this->printer = new graficador(this->map,this->rondita);

    this->printer->selecRutaGraficas(this->configuracion->getGraficsPath());
    this->printer->selecRutaSalida(this->configuracion->getOutPath());
    this->printer->cargarGraficas();
}

//---------------------------------------------------------------------------------------------------------------------

void batallaCampal::cargarConfiguracion(){

    this->cargarConfiguracion("../config/default_config.ini");
}

//---------------------------------------------------------------------------------------------------------------------

void batallaCampal::cargarConfiguracion(std::string path){

    if (this->configuracion != NULL)
    {
        delete this->configuracion;
    }

    this->configuracion = new gameConfig();

    this->configuracion->loadConfig(path);

    this->generarMapa();
    this->generarRonda();
    this->generarImpresora();

    this->cargarIdioma();
}

//                                                  METODOS DE LOGICA
//---------------------------------------------------------------------------------------------------------------------

bool batallaCampal::playerReady(){
    string nombre;
    string entrada;

    nombre = this->rondita->getJugadorEnTurno();

    cout << nombre << " " << this->mensaje.listo << endl;
    cout << this->mensaje.Y_N << endl;

    cin >> entrada;

    cout << endl;

    if (entrada == "Y" || entrada == "y")
    {
        return true;
    }

    return false;
    
}

//---------------------------------------------------------------------------------------------------------------------

bool batallaCampal::atackStage(){
    std::vector<int> pos;
    string entrada;

    cout << this->mensaje.deseaAtacar << endl; 
    cout << this->mensaje.Y_N << endl;

    cout << endl;

    cin >> entrada;

    cout << endl;

    if (entrada != "y" && entrada != "Y") // si no se desea mover retorno operacion exitosa
        {
            if (entrada == "n" || entrada == "N")
            {
                return true;
            }    
            return false;
        }

    // con este tipo de logica segun yo puedo ir anidando todas las decisiones
    if (this->cardSelectionStage(&pos) == true) // si se deseaba atacar pido seleccionar la carta con la cual se va a atacar
    {
        while (this->targetStrikeStage(pos) == false){} // si la carta era valida paso a la parte de ataque
        return true;
    }
    
    cout << this->mensaje.casillaInvalida << endl; // si la casilla era invalida devuelvo operacion fracasada y vuelvo a empezar
    cout << endl;

    return false;
}

//---------------------------------------------------------------------------------------------------------------------

bool batallaCampal::regroupStage(){
    string entrada;
    std::vector<int> pos;

    cout << this->mensaje.deseaMover << endl; 
    cout << this->mensaje.Y_N << endl;

    cout << endl;

    cin >> entrada;

    cout << endl;

    if (entrada != "y" && entrada != "Y") // si no se desea mover retorno operacion exitosa
        {
            if (entrada == "n" || entrada == "N")
            {
                return true;
            }    
            return false;
        }


    if (this->cardSelectionStage(&pos) == true) // podo la casilla de la carta a mover
    {
        while (this->moveStage(pos) == false){} // si la casilla era valida muevo la carta
        return true;
    }
    
    cout << this->mensaje.casillaInvalida << endl; // si la casilla era invalida retorno operacion fracasada, lo que me hace volver a empezar la operacion
    cout << endl;

    return false;
}

//---------------------------------------------------------------------------------------------------------------------

bool batallaCampal::cardChoiceStage(){
    string entrada;
    int coordenada;
    std::vector<int> pos;

    cout << "se levanto una carta de tipo" << " " << this->mensaje.tiposDeCartas[this->rondita->getCardType()] << endl; 


    cout << this->mensaje.conservarCarta << endl; 
    cout << this->mensaje.Y_N << endl;

    cout << endl;

    cin >> entrada;

    cout << endl;

    if (entrada != "y" && entrada != "Y") // si no se desea mover retorno operacion exitosa
        {
            if (entrada == "n" || entrada == "N")
            {
                return true;
            }    
            return false;
        }

    if (this->ejecuarMecanica() == true) // si es una carta de mecanicas y no de unidades
    {
        this->rondita->tirarCarta();
        return true;
    }
    
    while (this->ingresarPosicion(&pos) == false){} // si era una carta de unidades pido la posicion para colocar
    
    if (this->verificarPosicionCarta(this->rondita->getCardType(),pos) == false) // si esa carta no se podia colocar en esa posicion aviso y retorno que fallo la operacion
    {
        cout << this->mensaje.cartaPosInvalid << endl;
        cout << endl;
        return false;
    }

    switch (this->map->getStateCasilla(pos))
    {
    case libre:
        cout << this->mensaje.moviendoTropas << endl;
        cout << endl;


        this->rondita->jugarCarta(pos.data()); // si si se podia la agrego a la partida y retorno que la operacion fue exitosa
        this->map->takeCasilla(pos,this->rondita->getJugadorEnTurno());
        break;

    case ocupada:
        cout << this->mensaje.casillaOcupada << endl;
        cout << this->mensaje.tropasPerdidas << endl;
        cout << endl;

        this->rondita->tirarCarta(); // el jugador en turno pierde su carta

        this->map->leaveCasilla(pos);
        this->rondita->tirarCarta(this->map->getPropietario(pos),pos.data()); // el otro jugador tambien pierde la suya
        break;

    case destruida:
        cout << this->mensaje.casillaDestruida << endl;
        cout << this->mensaje.tropasPerdidas << endl;
        cout << endl;

        this->rondita->tirarCarta(); // el jugador en turno pierde su carta
        break;
    
    default:
        throw "estado invalido";
        break;
    }
    return true;
}


//---------------------------------------------------------------------------------------------------------------------

bool batallaCampal::cardSelectionStage(std::vector<int>* pos){

    cout << this->mensaje.elegirCarta << endl; 
    while (this->ingresarPosicion(pos) == false){}
    return this->rondita->verificarCartaExistente(*pos);
}

//---------------------------------------------------------------------------------------------------------------------

bool batallaCampal::moveStage(std::vector<int> posA){

    string entrada;
    std::vector<int> posB;

    cout << this->mensaje.aunDeseaMover << endl; 
    cout << this->mensaje.Y_N << endl;

    cout << endl;

    cin >> entrada;

    cout << endl;

    if (entrada != "y" && entrada != "Y") // si no se desea mover retorno operacion exitosa
        {
            if (entrada == "n" || entrada == "N")
            {
                return true;
            }    
            return false;
        }

    while (this->ingresarPosicion(&posB) == false){}

    if (this->verificarPosicionCarta(this->rondita->getCardType(posA.data()),posA,posB) == false) // si esa carta no se podia colocar en esa posicion aviso y retorno que fallo la operacion
    {
        cout << this->mensaje.cartaPosInvalid << endl;
        cout << endl;
        return false;
    }

    // si si se podia mover a esa posicion tengo que verificar si la casilla estaba ocupada

    switch (this->map->getStateCasilla(posB))
    {
    case libre:
        cout << this->mensaje.moviendoTropas << endl;
        cout << endl;

        this->map->leaveCasilla(posA);
        this->map->takeCasilla(posB,this->rondita->getJugadorEnTurno());
        this->rondita->moverCarta(posA.data(),posB.data());
        break;

    case ocupada:
        cout << this->mensaje.casillaOcupada << endl;
        cout << this->mensaje.tropasPerdidas << endl;
        cout << endl;

        this->map->leaveCasilla(posA);
        this->rondita->tirarCarta(posA.data()); // el jugador en turno pierde su carta

        this->map->leaveCasilla(posB);
        this->rondita->tirarCarta(this->map->getPropietario(posB),posB.data()); // el otro jugador tambien pierde la suya
        break;

    case destruida:
        cout << this->mensaje.casillaDestruida << endl;
        cout << this->mensaje.tropasPerdidas << endl;
        cout << endl;

        this->map->leaveCasilla(posA);
        this->rondita->tirarCarta(posA.data()); // el jugador en turno pierde su carta
        break;
    
    default:
        throw "estado invalido";
        break;
    } 

    return true; // despues de mover retorno operacion exitosa para que salga de todos los while
}

//---------------------------------------------------------------------------------------------------------------------

bool batallaCampal::targetStrikeStage(std::vector<int> posA){
    string entrada;
    std::vector<int> posB;

    while (this->rondita->getCardAmmo(posA.data()) > 0)
    {
        cout << this->rondita->getCardAmmo(posA.data()) << " " << this->mensaje.municionesRestantes << endl;
        cout << this->mensaje.aunDeseaAtacar << endl; 
        cout << this->mensaje.Y_N << endl;

        cout << endl;

        cin >> entrada;

        cout << endl;

        if (entrada != "y" && entrada != "Y") // si no se desea mover retorno operacion exitosa
        {
            if (entrada == "n" || entrada == "N")
            {
                return true;
            }    
            return false;
        }

        cout << "seleccione coordenadas del objetivo" << endl;

        while (this->ingresarPosicion(&posB) == false){}

        if (this->verificarRange(this->rondita->getCardStats(posA.data()).alcance,posA,posB) == false) // si esa carta no tenia el rango suficiente aviso y retorno que fallo la operacion
        {
            cout << this->mensaje.cartaPosInvalid << endl;
            cout << endl;
            return false;
        }

        this->rondita->shoot(posA.data());
        this->atacarPosicion(this->rondita->getCardStats(posA.data()).AoE,posB);
        cout << this->mensaje.ataqueExitoso << endl; 
    }
    return true;
}

//---------------------------------------------------------------------------------------------------------------------

bool batallaCampal::aditionalAtacksStage(){
    string entrada;
    std::vector<int> pos;
    while (this->rondita->getTotalAmmo() > 0)
    {
        cout << this->rondita->getTotalAmmo() << " " << this->mensaje.municionesRestantes << endl;
        cout << this->mensaje.deseaAtacar << endl; 
        cout << this->mensaje.Y_N << endl;

        cout << endl;

        cin >> entrada;

        cout << endl;

        if (entrada != "y" && entrada != "Y") // si no se desea mover retorno operacion exitosa
        {
            if (entrada == "n" || entrada == "N")
            {
                return true;
            }    
            return false;
        }

        if (this->cardSelectionStage(&pos) == true) // si se deseaba atacar pido seleccionar la carta con la cual se va a atacar
        {
            if (this->rondita->getCardType(pos.data()) == soldado)
            {
                cout << this->mensaje.noSoldados << endl; // si la casilla tenia un soldado devuelvo operacion fracasada y vuelvo a empezar
                cout << endl;
                return false;
            }

            if (this->rondita->getCardAmmo(pos.data()) < 1)
            {
                cout << "La carta no tiene municion restante" << endl; // si la casilla tenia un soldado devuelvo operacion fracasada y vuelvo a empezar
                cout << endl;
                return false;
            }
            
            
            while (this->targetStrikeStage(pos) == false){} // si la carta era valida paso a la parte de ataque
            //return true;
        }else
        {
    
            cout << this->mensaje.casillaInvalida << endl; // si la casilla era invalida devuelvo operacion fracasada y vuelvo a empezar
            cout << endl;

            return false;
        }

        //this->printPlayersScreens();
    }

    return true; // si no tengo mas municion restante
    
}

//---------------------------------------------------------------------------------------------------------------------

bool batallaCampal::ingresarPosicion(std::vector<int> * pos){
    int entrada;

    (*pos).resize(3);

    for (size_t i = 0; i < this->mensaje.coordenadas.size(); i++)
    {
        cout << this->mensaje.ingreseCoordenada << " " << this->mensaje.coordenadas.data()[i] << endl;

        cout << endl;

        cin >> entrada;

        cout << endl;

        if (entrada > this->configuracion->getDimXYZ()[i] || entrada < 1)
        {
            cout << this->mensaje.coordenadaInvalida << endl;
            return false;
        }    
        (*pos)[i]=entrada - 1; 
    }
    return true;
}

//---------------------------------------------------------------------------------------------------------------------

void batallaCampal::buryBodies(){
    if (this->rondita->contarJugadores()<1)
    {
        return;
    }
    
    for (size_t i = 0; i < this->configuracion->getPlayerNames().size(); i++)
    {
        if (this->rondita->contarCartas(this->configuracion->getPlayerNames()[i],soldado) < 1) //si no tiene soldados afuera
        {
            this->rondita->eliminarJugador(this->configuracion->getPlayerNames()[i]);
        }       
    }       
}

//---------------------------------------------------------------------------------------------------------------------

bool batallaCampal::ejecuarMecanica(){// estos recorridos pueden tomar un tiempo si el mapa es demasiado grande
    std::vector<int> pos={0,0,0};
    switch (this->rondita->getCardType())
    {
    case terremoto:
        for (size_t i = 0; i < this->configuracion->getDimXYZ()[0]; i++) // para todas las casillas de x
        {
            for (size_t j = 0; j < this->configuracion->getDimXYZ()[1]; j++) // para todas las y
            {
                pos[0]=i;
                pos[1]=j;
                if (this->map->getTypeCasilla(pos) == tierra && this->map->getStateCasilla(pos) == ocupada)
                {
                    if (this->rondita->getCardType(this->map->getPropietario(pos),pos.data()) != soldado) // si matara los soldados seria muy op
                    {
                        this->rondita->tirarCarta(this->map->getPropietario(pos),pos.data());
                        this->map->leaveCasilla(pos);
                    }                    
                }
                
            }
            
        }
        
        break;
    case ciclon:
        for (size_t k = 1; k < this->configuracion->getDimXYZ()[3]; k++)
        {
            pos[2]=k;
            for (size_t i = 0; i < this->configuracion->getDimXYZ()[0]; i++) // para todas las casillas de x
            {
                pos[0]=i;
                for (size_t j = 0; j < this->configuracion->getDimXYZ()[1]; j++) // para todas las y
                {
                    pos[1]=j;
                    if (this->map->getTypeCasilla(pos) == mar && this->map->getStateCasilla(pos) == ocupada)
                    {
                        this->rondita->tirarCarta(this->map->getPropietario(pos),pos.data());
                        this->map->leaveCasilla(pos);                   
                    }
                
                }
            
            }
        }
        
        break;
    case tsunami:
        for (size_t i = 0; i < this->configuracion->getDimXYZ()[0]; i++) // para todas las casillas de x
        {
            for (size_t j = 0; j < this->configuracion->getDimXYZ()[1]; j++) // para todas las y
            {
                pos[0]=i;
                pos[1]=j;
                if (this->map->getTypeCasilla(pos) == mar && this->map->getStateCasilla(pos) == ocupada)
                {
                    //if (this->rondita->getCardType(this->map->getPropietario(pos),pos.data()) != soldado) // la hice matar a los soldados dela gua porque las casillas de agua no se rompen
                    //{
                        this->rondita->tirarCarta(this->map->getPropietario(pos),pos.data());
                        this->map->leaveCasilla(pos);
                   // }                    
                }
                
            }
            
        }

        break;
    default:
        return false;
        break;
    }
    return true; // despues de ejecutar la mecanica avisa que la ejecuto
}
//---------------------------------------------------------------------------------------------------------------------

bool batallaCampal::verificarPosicionCarta(TiposCarta_T tipo,std::vector<int> pos){
    CasillaTipo_T casilla;
    casilla = this->map->getTypeCasilla(pos);
    carta* cartaModelo = new carta(this->rondita->getJugadorEnTurno(),tipo); // asi no tengo que buscar la carta en particular en la mano del jugador
    for (size_t i = 0; i < cartaModelo->getStats().terrenoAfin.size(); i++)
    {
        if (cartaModelo->getStats().terrenoAfin[i] == casilla)
        {
            delete cartaModelo;
            return true;
        }     
    }
    delete cartaModelo;
    return false;
}

//---------------------------------------------------------------------------------------------------------------------

bool batallaCampal::verificarPosicionCarta(TiposCarta_T tipo,std::vector<int> posA,std::vector<int> posB){
    CasillaTipo_T casilla;
    CasillaTipo_T casilla2;
    int dist;
    casilla = this->map->getTypeCasilla(posA);
    casilla2 = this->map->getTypeCasilla(posB);
    carta* cartaModelo = new carta(this->rondita->getJugadorEnTurno(),tipo); // asi no tengo que buscar la carta en particular en la mano del jugador
    for (int i = 0; i < 3; i++)
    {
        dist = int(posA.data()[i]-posB.data()[i]);
        if (abs(dist) > cartaModelo->getStats().movimiento[casilla]) // si las casillas estan mas separadas que los movimientos posibles
        {
            delete cartaModelo;
            return false;
        }

        if (abs(dist) > cartaModelo->getStats().movimiento[casilla2])
        {
            delete cartaModelo;
            return false;
        }
    }
    delete cartaModelo;
    return true; // si tengo movimientos suficientes en todas las direcciones retorno true
}

//---------------------------------------------------------------------------------------------------------------------

bool batallaCampal::verificarRange(int range,std::vector<int> posA,std::vector<int> posB){
    int dist;
    for (int i = 0; i < 3; i++)
    {
        dist=int(posA.data()[i]-posB.data()[i]);
        if (abs(dist) > range) // si las casillas estan mas separadas que el rango de ataque
        {
            return false;
        }
    }
    return true; // si tengo el alcance necesario
}

//---------------------------------------------------------------------------------------------------------------------

void batallaCampal::atacarPosicion(int AoE , std::vector<int> pos){    
    vector<int> posDestruida = pos;
  
    for (int x = 0; x < AoE; x++)
    {
        posDestruida[0] = pos[0] - AoE/2 + x; 
        for (int y = 0; y < AoE; y++)
        {
            posDestruida[1] = pos[1] - AoE/2 + y; 
            for (int z = 0; z < AoE; z++)
            {
                posDestruida[2] = pos[2] - AoE/2 + z;
                if (posDestruida[0] >= 0 && posDestruida[0] < this->configuracion->getDimXYZ()[0]) // si la casilla esta dentro del mapa
                {
                    if (posDestruida[1] >= 0 && posDestruida[1] < this->configuracion->getDimXYZ()[1])
                    {
                        if (posDestruida[2] >= 0 && posDestruida[2] < this->configuracion->getDimXYZ()[2])
                        {
                            if (this->map->getStateCasilla(posDestruida) == ocupada)
                            {
                                cout << "Impacto conseguido" << endl; 
                            }
                            
                            this->rondita->tirarCarta(this->map->getPropietario(posDestruida),posDestruida.data());
                            this->map->attackCasilla(posDestruida);
                        }
                        
                    }
                    
                }
                
            }
            
        }
        
    }

    this->printer->enmascarar(true);
    if (this->rondita->contarCartas(this->rondita->getJugadorEnTurno(),dirigible)>0)
    {
        this->printer->enmascarar(false);
    }
    
    this->printer->graficarPantalla(this->rondita->getJugadorEnTurno(),this->configuracion->getDimXYZ()[2]); // asi la pantalla se te actualiza despues de cada ataque
}

//---------------------------------------------------------------------------------------------------------------------
//                                                  SELECTOR DE IDIOMA
//---------------------------------------------------------------------------------------------------------------------

void batallaCampal::cargarIdioma(){
    this->mensaje.coordenadas.resize(3);
    this->mensaje.tiposDeCartas.resize(9);//igual que estos numeros, deberia ser algo tipo CARD_NUMBER 9 y MAP_DIM_NUMBER 3
    if (this->configuracion->getLanguage() == "esp") // estos deberian ser macros en un .h de idiomas pero no me alcanzo el tiempo asi que los harcodeo 
    {
        this->mensaje.ataqueExitoso="Ataque exitoso";
        this->mensaje.aunDeseaAtacar="Aun desea atacar?";
        this->mensaje.aunDeseaMover="Aun desea mover?";
        this->mensaje.aviones="aviones";
        this->mensaje.barcos="barcos";
        this->mensaje.bienvenida="Bienvenidos a Batalla campal 2 V1.0.3";
        this->mensaje.cartaPosInvalid="Posicion invalida";
        this->mensaje.cartas="cartas";
        this->mensaje.casillaDestruida="casilla destruida";
        this->mensaje.casillaInvalida="casilla invalida";
        this->mensaje.casillaOcupada="casilla ocupada";
        this->mensaje.conservarCarta="Desea usar la carta?";
        this->mensaje.coordenadaInvalida="coordenada invalida";
        this->mensaje.coordenadas[0]="X";
        this->mensaje.coordenadas[1]="Y";
        this->mensaje.coordenadas[2]="Z";
        this->mensaje.tiposDeCartas[misil]="misil";
        this->mensaje.tiposDeCartas[avion]="avion";
        this->mensaje.tiposDeCartas[barco]="barco";
        this->mensaje.tiposDeCartas[bomba_atomica]="bomba atomica";
        this->mensaje.tiposDeCartas[dirigible]="dirigible";
        this->mensaje.tiposDeCartas[ciclon]="ciclon";
        this->mensaje.tiposDeCartas[terremoto]="terremoto";
        this->mensaje.tiposDeCartas[tsunami]="tsunami";
        this->mensaje.tiposDeCartas[soldado]="soldado";
        this->mensaje.deseaAtacar="Desea realizar un ataque?";
        this->mensaje.deseaMover="Desea mover una carta?";
        this->mensaje.dirigibles="dirigibles";
        this->mensaje.elegirCarta="Elija una carta";
        this->mensaje.ingreseCoordenada="Ingresar Coordenada";
        this->mensaje.ingreseNombre="Ingresar Nombre (esto lo use?)";
        this->mensaje.listo="listo?";
        this->mensaje.misiles="misiles";
        this->mensaje.moviendoTropas="Moviendo tropas";
        this->mensaje.municionesRestantes="Municiones restantes";
        this->mensaje.noSoldados="los soldados no dan ataques extra";
        this->mensaje.soldados="soldados";
        this->mensaje.tropasPerdidas="Tropas perdidas";
        this->mensaje.Y_N="Y/N";

        return;
    }

    if (this->configuracion->getLanguage() == "eng")
    {
        this->mensaje.ataqueExitoso="Atack complete";
        this->mensaje.aunDeseaAtacar="Still want to atack?";
        this->mensaje.aunDeseaMover="Still want to move?";
        this->mensaje.aviones="aviones";
        this->mensaje.barcos="barcos";
        this->mensaje.bienvenida="Bienvenidos a Batalla campal 2 V1.0.3";
        this->mensaje.cartaPosInvalid="Invalid position";
        this->mensaje.cartas="cards";
        this->mensaje.casillaDestruida="destroyed box";
        this->mensaje.casillaInvalida="invalid box";
        this->mensaje.casillaOcupada="occupied box";
        this->mensaje.conservarCarta="Want use this card?";
        this->mensaje.coordenadaInvalida="invalid coordinate";
        this->mensaje.coordenadas[0]="X";
        this->mensaje.coordenadas[1]="Y";
        this->mensaje.coordenadas[2]="Z";
        this->mensaje.tiposDeCartas[misil]="rocket";
        this->mensaje.tiposDeCartas[avion]="plane";
        this->mensaje.tiposDeCartas[barco]="ship";
        this->mensaje.tiposDeCartas[bomba_atomica]="atomic bomb";
        this->mensaje.tiposDeCartas[dirigible]="zeppelin";
        this->mensaje.tiposDeCartas[ciclon]="ciclon";
        this->mensaje.tiposDeCartas[terremoto]="earth quake";
        this->mensaje.tiposDeCartas[tsunami]="tsunami";
        this->mensaje.tiposDeCartas[soldado]="soiler";
        this->mensaje.deseaAtacar="Want to atack?";
        this->mensaje.deseaMover="Want to move a card?";
        this->mensaje.dirigibles="dirigibles";
        this->mensaje.elegirCarta="Chose a card";
        this->mensaje.ingreseCoordenada="enter a coordinate";
        this->mensaje.ingreseNombre="Ingresar Nombre (esto lo use?)";
        this->mensaje.listo="Ready?";
        this->mensaje.misiles="misiles";
        this->mensaje.moviendoTropas="Moving troops";
        this->mensaje.municionesRestantes="remaining ammo";
        this->mensaje.noSoldados="the soilders cant make an extra attack";
        this->mensaje.soldados="soldados";
        this->mensaje.tropasPerdidas="lost troops";
        this->mensaje.Y_N="Y/N";

        return;
    }

    throw "Idioma no soportado";
}

//---------------------------------------------------------------------------------------------------------------------
//                                                  METODOS PUBLICOS
//---------------------------------------------------------------------------------------------------------------------


void batallaCampal::ejecutarTurno(){

    while (this->playerReady() == false){} //hago asi para poder volver atras en los menus sin anidar una infinidad de ifs

    while (this->atackStage() == false){}

    this->printPlayersScreens();

    this->buryBodies();

    if (this->getState() == terminada)
    {
        return;
    }
    
    while (this->regroupStage() == false){}

    this->printPlayersScreens();

    this->buryBodies();

    if (this->getState() == terminada)
    {
        return;
    }

    while (this->aditionalAtacksStage() == false){} 

    this->printPlayersScreens();

    this->buryBodies();

    if (this->getState() == terminada)
    {
        return;
    }

    this->rondita->tomarCarta();

    while (this->cardChoiceStage() == false){}

    this->printPlayersScreens();

    this->buryBodies();

    this->rondita->avanzarTurno();
    
}

//---------------------------------------------------------------------------------------------------------------------

void batallaCampal::iniciarPartida(){
    this->rondita->iniciarRonda();

    cout << this->mensaje.bienvenida << endl;

    cout << "etapa de preparacion" << endl;
    
    for (int i = 0; i < this->configuracion->getTroopsNumber(); i++) //los hago tomar la cantidad de soldados inicial
    {
        for (int n = 0; n < this->configuracion->getPlayerNumber(); n++) //para todos los jugadores
        {
            this->rondita->tomarCarta(soldado);
            this->printer->graficarPantalla(this->configuracion->getPlayerNames()[n],this->configuracion->getDimXYZ()[2]);
            //this->printPlayersScreens();
            cout << this->configuracion->getPlayerNames()[n] << " posicione un soldado" << endl;

            while (this->cardChoiceStage() == false){}

            this->rondita->avanzarTurno();//avanzo un turno cuando un jugador termino de agregar su soldado
            
        }
    }
    this->printPlayersScreens();
    cout << "etapa de preparacion terminada" << endl;
   
    this->estado = jugando; // cuando se agregan todos los soldados termine de iniciar
    this->buryBodies();
}

//---------------------------------------------------------------------------------------------------------------------

void batallaCampal::saludarGanador(){
    std::string ganador;
    this->buryBodies();
    ganador = this->rondita->getJugadorEnTurno();
    if (ganador == "")
    {
        cout << "La partida termino sin un ganador :(" << endl;
        return;
    }

    this->rondita->iniciarRonda();
    cout << "FELICIDADES " << ganador <<endl;
    cout << "GANASTE LA PARTIDA" << endl;
}

//---------------------------------------------------------------------------------------------------------------------

EstadoPartida_T batallaCampal::getState(){

    if (this->rondita->contarJugadores() <= 1)
    {
        this->estado = terminada;
    }else{
        this->estado = jugando;
    }
    
    return this->estado;
}

//---------------------------------------------------------------------------------------------------------------------

void batallaCampal::printPlayersScreens(){
    int n;
    for (size_t i = 0; i < this->configuracion->getPlayerNumber(); i++)
    {
        this->printer->enmascarar(true);

        n=this->rondita->contarCartas(this->configuracion->getPlayerNames()[i],dirigible); // si el jugador tiene almenos un dirigible le miestro todo el mapa

        if (n > 0)
        {
            this->printer->enmascarar(false);
        }

        if (this->rondita->getPlayerState(this->configuracion->getPlayerNames()[i]) == derrotado) //si el jugador esta derrotado le muestro el mapa final
        {
            this->printer->enmascarar(false);
        }
        

        // si quiero cambiar los fondos lo tendria que agregar aca
        
        this->printer->graficarPantalla(this->configuracion->getPlayerNames()[i],this->configuracion->getDimXYZ()[2]);
    }
    
}