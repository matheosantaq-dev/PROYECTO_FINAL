#include "PuntajeJuego.h"
#include <stdexcept>

PuntajeJuego::PuntajeJuego() : puntos(0), puntosNivelAnterior(0) {}

void PuntajeJuego::agregarPuntos(int cantidad)
{
    if (cantidad < 0)
        throw std::invalid_argument("PuntajeJuego: cantidad negativa no permitida");
    puntos += cantidad;
}

void PuntajeJuego::guardarNivel()
{
    puntosNivelAnterior += puntos;
    puntos = 0;
}

int PuntajeJuego::getPuntos()      const { return puntos; }
int PuntajeJuego::getPuntosTotal() const { return puntos + puntosNivelAnterior; }
