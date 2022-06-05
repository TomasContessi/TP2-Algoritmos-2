#ifndef TROPA_H
#define TROPA_H

class tropa
{
private:
    int regimiento; // numero del regimiento
    int posicion[3]; // posicion del soldado
    tropa * siguienteTropa; // puntero al siguiente soldado
public:
    tropa(/* args */);
    ~tropa();
};

tropa::tropa(/* args */)
{
}

tropa::~tropa()
{
}


#endif /* TROPA_H */