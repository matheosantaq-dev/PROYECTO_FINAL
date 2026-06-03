#include "Dardo.h"

Dardo::Dardo(float x, float y, int dificultad)
    : Proyectil(x, y, 0.0f, 4.0f + dificultad * 2.0f, 10)
{
    ancho = 8;
    alto  = 24;
}

void Dardo::actualizar()
{
    // Ligera aceleracion descendente (no puramente rectilineo)
    velocidadY += 0.08f;
    mover();
    if (y > 950) activo = false;
}
