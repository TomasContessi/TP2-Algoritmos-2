#include "graficador.hpp"

//---------------------------------------------------------------------------------------------------------------------
//                                   CONTESSI TOMAS 99199 ALORITMOS Y PROGRAMACION II
//---------------------------------------------------------------------------------------------------------------------
//-----------------------------------------------BATALLA CAMPAL 2 V2.2-------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------
//                                       IMPLEMENTACION DE LA CLASE GRAFICADOR
//---------------------------------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------------------------------
//                                              CONSTRUCTOR Y DESTRUCTOR
//---------------------------------------------------------------------------------------------------------------------

graficador::graficador(mapa* map,ronda* ronda)
{
    this->mapita=map;
    this->rondita=ronda;
    this->observador="";
    this->rutaGraficas="";
    this->rutaSalida="";
}

//---------------------------------------------------------------------------------------------------------------------

graficador::~graficador()
{
}

//---------------------------------------------------------------------------------------------------------------------
//                                                  METODOS PRIVADOS
//---------------------------------------------------------------------------------------------------------------------

void graficador::construirTablero(){
    int res;
    int dimX;
    int dimY;
    BMP imagen;
    CasillaTipo_T tipo;
    CasillaEstado_T estado;

    res=this->graficas.air.TellHeight(); // uso la dimension de las casillas

    this->tablero.SetBitDepth( this->graficas.air.TellBitDepth() );

    dimX=this->mapita->getDim().data()[0];
    dimY=this->mapita->getDim().data()[1];
    this->tablero.SetSize(int(dimX*res),int(dimY*res)); //seteo las dimensiones del tablero
    imagen.SetSize(res,res);

    this->mapita->iniciarCursor();

    do // para toda la dimension x
    {   
        do // para toda la dimension y
        {
            tipo=this->mapita->getTypeCasilla(this->mapita->getCursor());
            estado=this->mapita->getStateCasilla(this->mapita->getCursor());
            //imagen.ReadFromFile("../graphics_20/sky.bmp");

            switch (tipo)
            {
            case aire:
                RangedPixelToPixelCopy( graficas.air, 0,graficas.air.TellWidth()-1,graficas.air.TellHeight()-1 , 0, imagen, 0, 0); 
                break;

            case tierra:
            if (estado==destruida)
            {
                RangedPixelToPixelCopy( graficas.landDestroyed, 0,graficas.landDestroyed.TellWidth()-1,graficas.landDestroyed.TellHeight()-1 , 0, imagen, 0, 0); 
            }
                RangedPixelToPixelCopy( graficas.land, 0,graficas.land.TellWidth()-1,graficas.land.TellHeight()-1 , 0, imagen, 0, 0); 
            break;

            case mar:
                RangedPixelToPixelCopy( graficas.water, 0,graficas.water.TellWidth()-1,graficas.water.TellHeight()-1 , 0, imagen, 0, 0); 
                break;
    
            default:

            throw "thipo no valido";
                break;
            }

            dimX=this->mapita->getCursor().data()[0];
            dimY=this->mapita->getCursor().data()[1];

            //en el comando kilometrico de abajo pego la imagen en el lugar del tablero de la casilla apuntada por el cursor
            RangedPixelToPixelCopy( imagen, 0,imagen.TellWidth()-1,imagen.TellHeight()-1 , 0, this->tablero, int(dimX*res), int(dimY*res)); 

            //ahora avanzo el cursor
        }while(this->mapita->avanzarCursorY());      
        while (this->mapita->retrocederCursorY()){}
    }while(this->mapita->avanzarCursorX());
    
}

//---------------------------------------------------------------------------------------------------------------------

void graficador::agregarCartas(){

}

//---------------------------------------------------------------------------------------------------------------------

void graficador::agregarFondo(){// voy a hardcodear feo esto para tener ya una visualizacion
    this->pantalla.SetSize(this->tablero.TellWidth(),this->tablero.TellHeight());
    RangedPixelToPixelCopy( this->tablero, 0,this->tablero.TellWidth()-1,this->tablero.TellHeight()-1 , 0, this->pantalla, 0, 0);
}

//---------------------------------------------------------------------------------------------------------------------

void graficador::imgSelector(BMP imagen, CasillaTipo_T tipo,CasillaEstado_T estado){
    switch (tipo)
    {
    case aire:
        RangedPixelToPixelCopy( graficas.air, 0,graficas.air.TellWidth()-1,graficas.air.TellHeight()-1 , 0, imagen, 0, 0); 
        break;

    case tierra:
        if (estado==destruida)
        {
            RangedPixelToPixelCopy( graficas.landDestroyed, 0,graficas.landDestroyed.TellWidth()-1,graficas.landDestroyed.TellHeight()-1 , 0, imagen, 0, 0); 
        }
        RangedPixelToPixelCopy( graficas.land, 0,graficas.land.TellWidth()-1,graficas.land.TellHeight()-1 , 0, imagen, 0, 0); 
        break;

    case mar:
        RangedPixelToPixelCopy( graficas.water, 0,graficas.water.TellWidth()-1,graficas.water.TellHeight()-1 , 0, imagen, 0, 0); 
        break;
    
    default:

    throw "thipo no valido";
        break;
    }
}

//---------------------------------------------------------------------------------------------------------------------
//                                               METODOS DE CONFIGURACION
//---------------------------------------------------------------------------------------------------------------------

void graficador::selecRutaGraficas(std::string ruta){
    this->rutaGraficas=ruta;
    this->cargarGraficas();
}

//---------------------------------------------------------------------------------------------------------------------

void graficador::selecRutaSalida(std::string ruta){
    this->rutaSalida=ruta;
}

//---------------------------------------------------------------------------------------------------------------------

void graficador::cargarGraficas(){
    std::string nombre;
    std::string ruta;

    nombre="sky.bmp";
    ruta=this->rutaGraficas;
    ruta+=nombre;
    
    this->graficas.air.ReadFromFile(ruta.c_str());

    nombre="land.bmp";
    ruta=this->rutaGraficas;
    ruta+=nombre;
    
    this->graficas.land.ReadFromFile(ruta.c_str());

    nombre="water.bmp";
    ruta=this->rutaGraficas;
    ruta+=nombre;
    
    this->graficas.water.ReadFromFile(ruta.c_str());

    nombre="destroyed_land.bmp";
    ruta=this->rutaGraficas;
    ruta+=nombre;
    
    this->graficas.landDestroyed.ReadFromFile(ruta.c_str());
}

//---------------------------------------------------------------------------------------------------------------------
//                                                METODOS PARA GRAFICAR
//---------------------------------------------------------------------------------------------------------------------

void graficador::graficarPantalla(std::string nombre){
    std::string ruta;
    std::string extencion= ".bmp";
    
    ruta=this->rutaSalida;
    ruta+=nombre;
    ruta+=extencion;
    this->observador=nombre;

    this->construirTablero();
    this->agregarCartas();
    this->agregarFondo();

    this->pantalla.WriteToFile(ruta.c_str());
}