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
    this->mapaVisible=false;
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
            }else{
                RangedPixelToPixelCopy( graficas.land, 0,graficas.land.TellWidth()-1,graficas.land.TellHeight()-1 , 0, imagen, 0, 0); 
            }
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
    int res;
    int dimX;
    int dimY;
    BMP imagen;
    TiposCarta_T tipo;
    CasillaEstado_T estado;
    std::string ocupante;

    RGBApixel transparencia;
    transparencia.Red=255;
    transparencia.Green=255;
    transparencia.Blue=255;

    bool graficar; // flag que me dice si tengo o no que graficar en una casilla

    res=this->graficas.air.TellHeight(); // uso la dimension de las casillas

    
    dimX=this->mapita->getDim().data()[0];
    dimY=this->mapita->getDim().data()[1];
    

    imagen.SetSize(res,res);

    this->mapita->iniciarCursor();

    do // para toda la dimension x
    {   
        do // para toda la dimension y
        {
            estado=this->mapita->getStateCasilla(this->mapita->getCursor()); // me fijo el estado de la casilla

            if (estado == ocupada)
            {
                ocupante=this->mapita->getPropietario(this->mapita->getCursor()); // busco su pcupante

                if (observador==ocupante || this->mapaVisible == true) // si el ocupante es quien mira, o quien mira tiene un zeppelin
                {
                    tipo=this->rondita->getCardType(ocupante,this->mapita->getCursor().data()); // en ese lugar voy a graficar el tipo de carta

                    // cargo la imagen que voy a graficar, de vuelta el selector que habia pensado no anda
                    graficar=true;
                    switch (tipo)
                    {
                    case misil:
                        RangedPixelToPixelCopy( graficas.misil, 0,graficas.misil.TellWidth()-1,graficas.misil.TellHeight()-1 , 0, imagen, 0, 0); 
                        break;

                    case avion:
                        RangedPixelToPixelCopy( graficas.avion, 0,graficas.avion.TellWidth()-1,graficas.avion.TellHeight()-1 , 0, imagen, 0, 0);  
                        break;

                    case barco:
                        RangedPixelToPixelCopy( graficas.barco, 0,graficas.barco.TellWidth()-1,graficas.barco.TellHeight()-1 , 0, imagen, 0, 0); 
                        break;

                    case bomba_atomica:
                        RangedPixelToPixelCopy( graficas.bomba, 0,graficas.bomba.TellWidth()-1,graficas.bomba.TellHeight()-1 , 0, imagen, 0, 0); 
                        break;
                    case dirigible:
                        RangedPixelToPixelCopy( graficas.dirigible, 0,graficas.dirigible.TellWidth()-1,graficas.dirigible.TellHeight()-1 , 0, imagen, 0, 0); 
                        break;
                    case soldado:
                        RangedPixelToPixelCopy( graficas.soldado, 0,graficas.soldado.TellWidth()-1,graficas.soldado.TellHeight()-1 , 0, imagen, 0, 0); 
                        break;
    
                    default:
                        graficar=false;
                        break;
                    }

                    if (ocupante != observador)
                    {
                        RangedPixelToPixelCopyTransparent(graficas.enemyGrid, 0,graficas.enemyGrid.TellWidth()-1,graficas.enemyGrid.TellHeight()-1 , 0, imagen, 0, 0, transparencia);
                    }else{
                        RangedPixelToPixelCopyTransparent(graficas.allyGrid, 0,graficas.allyGrid.TellWidth()-1,graficas.allyGrid.TellHeight()-1 , 0, imagen, 0, 0, transparencia);                       
                    }                    
                }                
            }
            // con todo eso genere la imagen que va a ir en la casilla, ahora reviso el flag y la grafico

            if (graficar==true)
            {
                //imagen.WriteToFile("tst.bmp");
                dimX=this->mapita->getCursor().data()[0];
                dimY=this->mapita->getCursor().data()[1];

                //en el comando kilometrico de abajo pego la imagen en el lugar del tablero de la casilla apuntada por el cursor
                RangedPixelToPixelCopyTransparent( imagen, 0,imagen.TellWidth()-1,imagen.TellHeight()-1 , 0, this->tablero, int(dimX*res), int(dimY*res), transparencia);
                graficar=false;
            }
                        
            //ahora avanzo el cursor
        }while(this->mapita->avanzarCursorY());      
        while (this->mapita->retrocederCursorY()){}
    }while(this->mapita->avanzarCursorX());
}

//---------------------------------------------------------------------------------------------------------------------

void graficador::agregarFondo(){// voy a hardcodear feo esto para tener ya una visualizacion
    this->pantalla.SetSize(this->tablero.TellWidth(),this->tablero.TellHeight());
    RangedPixelToPixelCopy( this->tablero, 0,this->tablero.TellWidth()-1,this->tablero.TellHeight()-1 , 0, this->pantalla, 0, 0);
    Rescale(this->pantalla,'H',800);
}

//---------------------------------------------------------------------------------------------------------------------
// no anda por alguna razon que desconozco

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
    // cargo los nombres de las imagenes
    std::vector<std::string> nombre={"land.bmp",
                                    "sky.bmp",
                                    "water.bmp",
                                    "destroyed_land.bmp",
                                    "misil.bmp",
                                    "plane.bmp",
                                    "ship.bmp",
                                    "bomb.bmp",
                                    "zeppelin.bmp",
                                    "cursed_troop.bmp",
                                    "ally_grid.bmp",
                                    "enemy_grill.bmp",
                                    };
    std::string ruta;

    for (int i = 0; i < nombre.size(); i++)
    {
        ruta=this->rutaGraficas;
        ruta+=nombre[i];

        switch (i) // creia que las estructuras se podian acceder secuencialmente como en matlab, pero nope
        {

        case 0:
            this->graficas.land.ReadFromFile(ruta.c_str());
            break;
        case 1:
            this->graficas.air.ReadFromFile(ruta.c_str());
            break;
        case 2:
            this->graficas.water.ReadFromFile(ruta.c_str());
            break;
        case 3:
            this->graficas.landDestroyed.ReadFromFile(ruta.c_str());
            break;
        case 4:
            this->graficas.misil.ReadFromFile(ruta.c_str());
            break;
        case 5:
            this->graficas.avion.ReadFromFile(ruta.c_str());
            break;
        case 6:
            this->graficas.barco.ReadFromFile(ruta.c_str());
            break;
        case 7:
            this->graficas.bomba.ReadFromFile(ruta.c_str());
            break;
        case 8:
            this->graficas.dirigible.ReadFromFile(ruta.c_str());
            break;
        case 9:
            this->graficas.soldado.ReadFromFile(ruta.c_str());
            break;
        case 10:
            this->graficas.allyGrid.ReadFromFile(ruta.c_str());
            break;
        case 11:
            this->graficas.enemyGrid.ReadFromFile(ruta.c_str());
            break;

        default:

        throw "caso invalido, posiblemente conte mal";
            break;
        }
    }
    
}

//---------------------------------------------------------------------------------------------------------------------

void graficador::enmascarar(bool opcion){
    this->mapaVisible= !opcion; // si, que la logica invierta es feo pero no se me ocurrian mejores nombres
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