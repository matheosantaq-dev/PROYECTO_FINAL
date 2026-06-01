#include "Balon.h"

Balon::Balon(
    float x,
    float y,
    float velocidadX
)
    : Proyectil(
        x,
        y,
        velocidadX,
        -8
    )
{
}
void Balon::actualizar()
{
    mover();

    // Sale por arriba
    if(y < -100)
    {
        activo = false;
    }
}
