#include "Proyectil.h"

Proyectil::Proyectil(float x, float y, float vx, float vy, int danio)
    : Entidad(x, y, 24, 24),
    danio(danio), activo(true)
{
    velocidadX = vx;
    velocidadY = vy;
}

Proyectil::~Proyectil() {}

void Proyectil::mover()
{
    x += velocidadX;
    y += velocidadY;
}

void Proyectil::actualizar()
{
    mover();
    if (y < -100 || y > 950 || x < -100 || x > 1350)
        activo = false;
}

bool Proyectil::estaActivo() const { return activo; }
void Proyectil::desactivar()       { activo = false; }
int  Proyectil::getDanio()   const { return danio; }
