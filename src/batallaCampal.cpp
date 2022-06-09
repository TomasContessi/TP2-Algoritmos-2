#include <iostream>
#include <string>

#include "batallaCampal.hpp"

using namespace std;

//---------------------------------------------------------------------------------------------------------------------
//                                   CONTESSI TOMAS 99199 ALORITMOS Y PROGRAMACION II
//---------------------------------------------------------------------------------------------------------------------
//-----------------------------------------------BATALLA CAMPAL 2 V2.2-------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------
//                                       IMPLEMENTACION DE LA CLASE BATALLA CAMPAL
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

    this->cargarConfiguracion("../config/default_config");
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
    vector<unsigned int> pos;
    string entrada;

    cout << this->mensaje.deseaAtacar << endl; 
    cout << this->mensaje.Y_N << endl;

    cout << endl;

    cin >> entrada;

    cout << endl;

    if (entrada == "n" || entrada == "N") // si no se desea atacar retorno operacion exitosa y vuelvo
    {
        return true;
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
    vector<unsigned int> pos;

    cout << this->mensaje.deseaMover << endl; 
    cout << this->mensaje.Y_N << endl;

    cout << endl;

    cin >> entrada;

    cout << endl;

    if (entrada == "n" || entrada == "N") // si no se desea mover retorno operacion exitosa
    {
        return true;
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
    vector<unsigned int> pos;

    cout << this->mensaje.conservarCarta << endl; 
    cout << this->mensaje.Y_N << endl;

    cout << endl;

    cin >> entrada;

    cout << endl;

    if (entrada == "n" || entrada == "N") // pregunto si se desea la carta y si no la tiro y devuelvo operacion exitosa
    {
        this->rondita->tirarCarta();
        return true;
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

    this->rondita->jugarCarta(pos.data()); // si si se podia la agrego a la partida y retorno que la operacion fue exitosa
    this->map->takeCasilla(pos,this->rondita->getJugadorEnTurno());
    return true;
}


//---------------------------------------------------------------------------------------------------------------------

bool batallaCampal::cardSelectionStage(vector<unsigned int>* pos){

    cout << this->mensaje.elegirCarta << endl; 
    while (this->ingresarPosicion(pos) == false){}
    return this->rondita->verificarCartaExistente(*pos);
}

//---------------------------------------------------------------------------------------------------------------------

bool batallaCampal::moveStage(vector<unsigned int> posA){

    string entrada;
    vector<unsigned int> posB;

    cout << this->mensaje.aunDeseaMover << endl; 
    cout << this->mensaje.Y_N << endl;

    cout << endl;

    cin >> entrada;

    cout << endl;

    if (entrada == "n" || entrada == "N") // si no se desea mover retorno operacion exitosa
    {
        return true;
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

bool batallaCampal::targetStrikeStage(vector<unsigned int> posA){
    string entrada;
    vector<unsigned int> posB;

    while (this->rondita->getCardAmmo(posA.data()) > 0)
    {
        cout << this->rondita->getCardAmmo(posA.data()) << this->mensaje.municionesRestantes << endl;
        cout << this->mensaje.aunDeseaAtacar << endl; 
        cout << this->mensaje.Y_N << endl;

        cout << endl;

        cin >> entrada;

        cout << endl;

        if (entrada == "n" || entrada == "N") // si no se desea mover retorno operacion exitosa
        {
            return true;
        }

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
    vector<unsigned int> pos;
    while (this->rondita->getTotalAmmo() > 0)
    {
        cout << this->rondita->getTotalAmmo() << this->mensaje.municionesRestantes << endl;
        cout << this->mensaje.deseaAtacar << endl; 
        cout << this->mensaje.Y_N << endl;

        cout << endl;

        cin >> entrada;

        cout << endl;

        if (entrada == "n" || entrada == "N") // si no se desea mover retorno operacion exitosa
        {
            return true;
        }

        if (this->cardSelectionStage(&pos) == true) // si se deseaba atacar pido seleccionar la carta con la cual se va a atacar
        {
            if (this->rondita->getCardType(pos.data()) == soldado)
            {
                cout << this->mensaje.noSoldados << endl; // si la casilla tenia un soldado devuelvo operacion fracasada y vuelvo a empezar
                cout << endl;
                return false;
            }
            
            while (this->targetStrikeStage(pos) == false){} // si la carta era valida paso a la parte de ataque
            return true;
        }
    
        cout << this->mensaje.casillaInvalida << endl; // si la casilla era invalida devuelvo operacion fracasada y vuelvo a empezar
        cout << endl;

        return false;
    }

    return true; // si no tengo mas municion restante
    
}

//---------------------------------------------------------------------------------------------------------------------

bool batallaCampal::ingresarPosicion(std::vector<unsigned int> * pos){
    unsigned int entrada;

    for (size_t i = 0; i < this->mensaje.coordenadas.size(); i++)
    {
        cout << this->mensaje.ingreseCoordenada << " " << this->mensaje.coordenadas[i] << endl;

        cout << this->mensaje.Y_N << endl;

        cout << endl;

        cin >> entrada;

        cout << endl;

        if (entrada > this->configuracion->getDimXYZ()[i])
        {
            cout << this->mensaje.coordenadaInvalida << endl;
            return false;
        }    
        (*pos)[i]=entrada; 
    }
    return true;
}

//---------------------------------------------------------------------------------------------------------------------

void batallaCampal::buryBodies(){
    for (size_t i = 0; i < this->configuracion->getPlayerNames().size(); i++)
    {
        if (this->rondita->contarCartas(this->configuracion->getPlayerNames()[i],soldado) < 1) //si no tiene soldados afuera
        {
            this->rondita->eliminarJugador(this->configuracion->getPlayerNames()[i]);
        }       
    }    
}

//---------------------------------------------------------------------------------------------------------------------

bool batallaCampal::ejecuarMecanica(){
    vector<unsigned int> pos={0,0,0};
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
                    if (this->rondita->getCardType(this->map->getPropietario(pos),pos.data()) != soldado) // si matara los soldados seria muy op
                    {
                        this->rondita->tirarCarta(this->map->getPropietario(pos),pos.data());
                        this->map->leaveCasilla(pos);
                    }                    
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
//                                                  METODOS PUBLICOS
//---------------------------------------------------------------------------------------------------------------------


void batallaCampal::ejecutarTurno(){

    while (this->playerReady() == false){} //hago asi para poder volver atras en los menus sin anidar una infinidad de ifs

    while (this->atackStage() == false){}

    while (this->regroupStage() == false){}

    while (this->aditionalAtacksStage() == false){}

    this->rondita->tomarCarta();

    while (this->cardChoiceStage() == false){}

    this->printPlayersScreens();

    this->buryBodies();

    this->rondita->avanzarTurno();
    
}

//---------------------------------------------------------------------------------------------------------------------

void batallaCampal::saludarGanador(){

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
        
        this->printer->graficarPantalla(this->configuracion->getPlayerNames()[i]);
    }
    
}