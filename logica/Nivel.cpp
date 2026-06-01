#include "Nivel.h"

Nivel::Nivel()
{
    jugador = nullptr;

    terminado = false;
}

Nivel::~Nivel()
{
    delete jugador;
    jugador = nullptr;
    for(Enemigo* enemigo : enemigos)
    {
        delete enemigo;
    }
    for(Enemigo*& enemigo : enemigos)
    {
        enemigo = nullptr;
    }
    enemigos.clear();
}

bool Nivel::estaTerminado() const
{
    return terminado;
}

Jugador* Nivel::getJugador() const
{
    return jugador;
}

const std::vector<Enemigo*>& 
Nivel::getEnemigos() const
{
    return enemigos;
    
}
void Nivel::lanzarBalon()
{

}
