#include "Balon.h"

Balon::Balon(float x, float y)
    : Proyectil(x, y, 0, -8)
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
