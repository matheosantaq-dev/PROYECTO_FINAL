#include "PuntajeJuego.h"

PuntajeJuego::PuntajeJuego()
{
    puntos = 0;
}

void PuntajeJuego::agregarPuntos(int cantidad)
{
    puntos += cantidad;
}

int PuntajeJuego::getPuntos() const
{
    return puntos;
}
