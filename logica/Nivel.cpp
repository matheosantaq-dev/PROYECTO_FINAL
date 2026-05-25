#include "Nivel.h"

Nivel::Nivel()
{
    jugador = nullptr;

    terminado = false;
}

Nivel::~Nivel()
{
    delete jugador;

    for(Enemigo* enemigo : enemigos)
    {
        delete enemigo;
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

std::vector<Enemigo*>& Nivel::getEnemigos()
{
    return enemigos;
    
}
void Nivel::lanzarBalon()
{

}
