#include "Proyectil.h"

Proyectil::Proyectil(float x, float y,
                     float velocidadX,
                     float velocidadY)
    : Entidad(x, y)
{
    this->velocidadX = velocidadX;
    this->velocidadY = velocidadY;

    danio = 10;

    activo = true;
}

Proyectil::~Proyectil()
{

}

void Proyectil::mover()
{
    x += velocidadX;
    y += velocidadY;
}

void Proyectil::actualizar()
{
    mover();

    // Sale de los limites visuales
    if(y < -100 || y > 900)
    {
        activo = false;
    }

    if(x < -100 || x > 1200)
    {
        activo = false;
    }
}

bool Proyectil::estaActivo() const
{
    return activo;
}

void Proyectil::desactivar()
{
    activo = false;
}

int Proyectil::getDanio() const
{
    return danio;
}
