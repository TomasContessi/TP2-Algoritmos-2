#include "ronda.hpp"

//---------------------------------------------------------------------------------------------------------------------
//                                   CONTESSI TOMAS 99199 ALORITMOS Y PROGRAMACION II
//---------------------------------------------------------------------------------------------------------------------
//---------------------------------------------    BATALLA CAMPAL 2    ------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------
//                                       IMPLEMENTACION DE LA CLASE RONDA V2.2
//---------------------------------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------------------------------
//                                              CONSTRUCTOR Y DESTRUCTOR
//---------------------------------------------------------------------------------------------------------------------

ronda::ronda()
{
    this->jugadores=NULL;
    this->jugadorEnTurno=this->jugadores;
    this->nuevaCarta=NULL;
    srand(time(NULL)); // inicio una semilla aleatoria con la hora de mi maquina (hago esto porque sino siempre baraja igual)
}

ronda::~ronda()
{
    while (this->jugadores != NULL) // mientras haya jugadores
    {
        this->eliminarJugador(this->jugadores->getName()); // elimino al primer jugador de la lista
    }
    this->tirarCarta();
}

//---------------------------------------------------------------------------------------------------------------------
//                                              METODOS SOBRE JUGADORES
//---------------------------------------------------------------------------------------------------------------------

void ronda::agregarJugador(jugador* player){
    jugador* aux;

    if (this->jugadores == NULL) // si la ronda estaba vacia la inicio con este jugador
    {
        this->jugadores= player;
        player->setSiguiente(this->jugadores);
        this->iniciarRonda();
        return;
    }
    
    aux=this->jugadores;

    while (aux->getSig() != this->jugadores && aux != NULL) // voy recorriendo la ronda hasta encontrar el ultimo, o que se rompa la cadena circular
    {
        aux=aux->getSig();
    }
    
    if (aux->getSig() == this->jugadores) // si salio porque encontro al ultimo jugador agrego el nuevo
    {
        aux->setSiguiente(player);
        player->setSiguiente(this->jugadores);
        this->iniciarRonda();
        return;
    }

    throw "error en la estructura de la ronda"; // si llego hasta aca es que la ronda estaba cortada en algun lado

}

//---------------------------------------------------------------------------------------------------------------------

void ronda::eliminarJugador(std::string nombre){
    jugador* aux;
    jugador* aux2;


    if (this->jugadores == NULL)
    {
        this->iniciarRonda(); 
        return;
    }

    aux2=this->jugadores;
    aux=aux2->getSig();

    if (aux == this->jugadores) //si habia solo un jugador en la lista
    {
        if (aux->getName() == nombre) // si el nombre concuerda lo borro
        {
            this->jugadores=NULL; 
            delete aux;
            this->iniciarRonda();
        }
        return;
    }
    
    
    while (aux != this->jugadores) // hasta dar la vuelta a la ronda
    {
        if (aux->getName() == nombre) // si encuentro el nombre en la lista
        {
            aux2->setSiguiente(aux->getSig()); // saco al jugador con ese nombre
            delete aux;
            this->jugadorEnTurno = aux2;
            return;
        }

        aux2=aux2->getSig(); // avanzo los dos cursores en 1
        aux=aux2->getSig();

        if (aux == NULL)
        {
            throw "error en la continuidad de la ronda";
        }
              
    }

    if (aux->getName() == nombre) // si er el primero de la lista
    {
        aux2->setSiguiente(aux->getSig()); // saco al jugador con ese nombre
        this->jugadores=aux->getSig();
        delete aux;
        this->jugadorEnTurno = aux2;
        return;
    }
    
}

//---------------------------------------------------------------------------------------------------------------------

void ronda::eliminarJugador(){
    this->eliminarJugador(this->getJugadorEnTurno());
}

//---------------------------------------------------------------------------------------------------------------------

int ronda::contarJugadores(){
    jugador* aux;
    int contador=0;

    if (this->jugadores == NULL) // si la ronda esta acia devuelvo el contador
    {
        return contador;
    }
    

    aux=this->jugadores;

    contador ++; // aumento el contador porque habia almenos una carta

    while (aux->getSig() != this->jugadores) // voy avanzando y con cada avance subo 1 al contador
    {
        contador++;
        aux=aux->getSig();
        if (aux == NULL)
        {
            throw "error en la continuidad de la ronda";
        }
        
    }
    return contador;
}

//---------------------------------------------------------------------------------------------------------------------

void ronda::iniciarRonda(){
    this->jugadorEnTurno=this->jugadores;
    this->tirarCarta();
}

//---------------------------------------------------------------------------------------------------------------------

void ronda::avanzarTurno(){
    this->reloadAmmo();
    this->jugadorEnTurno=this->jugadorEnTurno->getSig();
    this->tirarCarta();
}

//---------------------------------------------------------------------------------------------------------------------

std::string ronda::getJugadorEnTurno(){
    if (this->jugadorEnTurno == NULL)
    {
        return "";
    }
    
    return this->jugadorEnTurno->getName();
}

//---------------------------------------------------------------------------------------------------------------------

EstadoJugador_T ronda::getPlayerState(std::string nombre){
    jugador* aux;

    aux= this->jugadores;

    if (aux->getSig() == aux)// si solo hay un jugador en la lista
    {
        if (aux->getName() == nombre) // si el nombre coincide le digo que retire la carta
        {
            if(aux->contarCartas(soldado) < 1){
                aux->setState(derrotado);
            }
            return aux->getState();
        }
        return derrotado;
    }

    while (aux->getSig() != this->jugadores)
    {
        if (aux->getName() == nombre) // si el nombre coincide le digo que retire la carta
        {
            if(aux->contarCartas(soldado) < 1){
                aux->setState(derrotado);
            }
            return aux->getState();
        }

        aux=aux->getSig();

        if (aux == NULL)
        {
            throw "error de continuidad de la lista";
        }       
    } 

    if (aux->getName() == nombre) // si el nombre coincide le digo que retire la carta
    {
        if(aux->contarCartas(soldado) < 1){
            aux->setState(derrotado);
        }
        return aux->getState();
    }

    return derrotado;
}

//---------------------------------------------------------------------------------------------------------------------

int ronda::getTotalAmmo(){
    return this->jugadorEnTurno->getCardAmmo();
}

//---------------------------------------------------------------------------------------------------------------------

void ronda::reloadAmmo(){
    this->jugadorEnTurno->reloadCardAmmo();
}

//---------------------------------------------------------------------------------------------------------------------
//                                              METODOS SOBRE CARTAS
//---------------------------------------------------------------------------------------------------------------------

TiposCarta_T ronda::tomarCarta(){
    TiposCarta_T tipo;

    //srand(time(NULL)); // inicio una semilla aleatoria con la hora de mi maquina (hago esto porque sino siempre baraja igual)
    tipo=TiposCarta_T (rand() % (LAST_CARD_TYPE + 1)); // genero aleatoriamente el tipo de carta que voy a sacar
    return this->tomarCarta(tipo); // genero la carta y devuelvo su tipo
}

//---------------------------------------------------------------------------------------------------------------------

TiposCarta_T ronda::tomarCarta(TiposCarta_T tipo){
    this->nuevaCarta = new carta(this->getJugadorEnTurno(),tipo);
    return tipo;
}

//---------------------------------------------------------------------------------------------------------------------

void ronda::jugarCarta(int pos[3]){
    this->nuevaCarta->setPos(pos);
    this->jugadorEnTurno->agregarCarta(this->nuevaCarta);
    this->nuevaCarta=NULL;
}

//---------------------------------------------------------------------------------------------------------------------

void ronda::tirarCarta(std::string nombre,int pos[3]){
    jugador* aux;

    aux= this->jugadores;   

    while (aux != NULL)
    {
        if (aux->getName() == nombre)
        {
            aux->retirarCarta(pos);
            return;
        }

        aux=aux->getSig();

        if (aux == this->jugadores)
        {
            if (aux->getName() == nombre)
            {
                aux->retirarCarta(pos);
                return;
            }
            return;
        }
        
    }
    
}

//---------------------------------------------------------------------------------------------------------------------

void ronda::tirarCarta(int pos[3]){
    this->jugadorEnTurno->retirarCarta(pos);
}

//---------------------------------------------------------------------------------------------------------------------

void ronda::tirarCarta(){
    if (this->nuevaCarta != NULL)
    {
        delete this->nuevaCarta;
        this->nuevaCarta=NULL;
    }
}

//---------------------------------------------------------------------------------------------------------------------

void ronda::moverCarta(int posA[3] , int posB[3]){
    TiposCarta_T tipo;

    tipo = this->jugadorEnTurno->getCardType(posA);

    this->tomarCarta(tipo);

    this->tirarCarta(posA);
    this->jugarCarta(posB);
}

//---------------------------------------------------------------------------------------------------------------------

int ronda::contarCartas(std::string nombre,TiposCarta_T tipo){
   jugador* aux;

    aux= this->jugadores;

    if (aux->getSig() == aux)// si solo hay un jugador en la lista
    {
        if (aux->getName() == nombre) // si el nombre coincide le digo que cuente las cartas
        {
            return int(aux->contarCartas(tipo));
        }
        return 0;
    }

    while (aux->getSig() != this->jugadores)
    {
        if (aux->getName() == nombre) // si el nombre coincide le digo que cuente las cartas
        {
            return int(aux->contarCartas(tipo));
        }

        aux=aux->getSig();

        if (aux == NULL)
        {
            throw "error de continuidad de la lista";
        }       
    } 
     
    if (aux->getName() == nombre) // si el nombre coincide le digo que cuente las cartas
    {
        return int(aux->contarCartas(tipo));
    }

    return 0;
}

//---------------------------------------------------------------------------------------------------------------------

int ronda::contarCartas(TiposCarta_T tipo){
    return int(this->jugadorEnTurno->contarCartas(tipo));
}

//---------------------------------------------------------------------------------------------------------------------

CardStats ronda::getCardStats(int pos[3]){
    return this->jugadorEnTurno->getCardStats(pos);
}

//---------------------------------------------------------------------------------------------------------------------

TiposCarta_T ronda::getCardType(int pos[3]){
    return this->jugadorEnTurno->getCardType(pos);
}

//---------------------------------------------------------------------------------------------------------------------

TiposCarta_T ronda::getCardType(std::string nombre,int pos[3]){
    jugador* aux;
    TiposCarta_T tipo;

    aux=this->jugadorEnTurno;

    if (this->jugadorEnTurno->getSig() == this->jugadorEnTurno)
    {
        if (this->getJugadorEnTurno() == nombre)
        {
            return this->getCardType(pos);
        } 

        throw "no hay un jugador con ese nombre";
    }
    

    while (this->jugadorEnTurno->getSig() != this->jugadorEnTurno)
    {
        if (this->getJugadorEnTurno() == nombre)
        {
            tipo=this->getCardType(pos);
            this->jugadorEnTurno=aux;
            return tipo;
        }       
        this->avanzarTurno(); 
    }

    if (this->getJugadorEnTurno() == nombre)
    {
        tipo=this->getCardType(pos);
        this->jugadorEnTurno=aux;
        return tipo;
    } 
    
    throw "no hay un jugador con ese nombre";
}

//---------------------------------------------------------------------------------------------------------------------

TiposCarta_T ronda::getCardType(){
    return this->nuevaCarta->getType();
}

//---------------------------------------------------------------------------------------------------------------------

bool ronda::verificarCartaExistente(std::vector<int> pos){
    return this->jugadorEnTurno->verificarCarta(pos);    
}

//---------------------------------------------------------------------------------------------------------------------

int ronda::getCardAmmo(int pos[3]){
    return this->jugadorEnTurno->getCardAmmo(pos);
}

//---------------------------------------------------------------------------------------------------------------------

int ronda::shoot(int pos[3]){
    return this->jugadorEnTurno->shoot(pos);
}