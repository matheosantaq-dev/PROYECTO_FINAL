#include "TemporizadorJuego.h"

TemporizadorJuego::TemporizadorJuego()
{
    tiempoActual = 0;
}

void TemporizadorJuego::actualizar()
{
    tiempoActual++;
}

int TemporizadorJuego::getTiempoActual() const
{
    return tiempoActual;
}
