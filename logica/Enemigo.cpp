#include "Enemigo.h"

Enemigo::Enemigo(float x, float y)
    : Entidad(x, y)
{
    vida = 50;

    velocidadMovimiento = 3;

    vivo = true;

    moviendoDerecha = true;

    velocidadX = velocidadMovimiento;
}

Enemigo::~Enemigo()
{

}

void Enemigo::mover()
{
    x += velocidadX;
}

void Enemigo::actualizar()
{
    mover();

    // Movimiento automático

    if(x <= 0)
    {
        moviendoDerecha = true;
        velocidadX = velocidadMovimiento;
    }

    if(x >= 750)
    {
        moviendoDerecha = false;
        velocidadX = -velocidadMovimiento;
    }
}

void Enemigo::recibirDanio(int cantidad)
{
    vida -= cantidad;

    if(vida <= 0)
    {
        vida = 0;
        vivo = false;
    }
}

bool Enemigo::estaVivo() const
{
    return vivo;
}

int Enemigo::getVida() const
{
    return vida;
}
