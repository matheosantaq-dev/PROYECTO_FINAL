#include "Nivel.h"

Nivel::Nivel()
    : jugador(nullptr),
    estado(JUGANDO),
    ticksTransicion(0)
{}

Nivel::~Nivel()
{
    delete jugador;
    jugador = nullptr;

    for (Enemigo* e : enemigos)
        delete e;
    enemigos.clear();
}

void Nivel::iniciarTransicion(int duracionTicks)
{
    estado = TRANSICION;
    ticksTransicion = duracionTicks;
}

void Nivel::actualizarTransicion()
{
    if (estado == TRANSICION)
    {
        --ticksTransicion;
        if (ticksTransicion <= 0)
            estado = TERMINADO;
    }
}

bool        Nivel::estaTerminado()  const { return estado == TERMINADO; }
bool        Nivel::enTransicion()   const { return estado == TRANSICION; }
EstadoNivel Nivel::getEstado()      const { return estado; }

Jugador* Nivel::getJugador() const { return jugador; }

const std::vector<Enemigo*>& Nivel::getEnemigos() const { return enemigos; }

int Nivel::getPuntaje() const { return puntaje.getPuntosTotal(); }
