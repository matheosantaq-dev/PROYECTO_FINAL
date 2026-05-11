#include "Dardo.h"

Dardo::Dardo(float x, float y)
    : Proyectil(x, y, 0, 6)
{

}

void Dardo::actualizar()
{
    mover();

   
    if(y > 900)
    {
        activo = false;
    }
}
