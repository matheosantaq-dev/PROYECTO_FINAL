#include "Jugador.h"

const float GRAVEDAD = 0.5;

Jugador::Jugador(float x, float y)
    : Entidad(x, y)
{
    vida = 100;

    saltando = false;
    agachado = false;

    tieneBalon = false;
}

void Jugador::mover()
{
    x += velocidadX;
    y += velocidadY;
}

void Jugador::actualizar()
{
    velocidadY += GRAVEDAD;

    mover();

    // Piso 
    if(y >= 500)
    {
        y = 500;

        velocidadY = 0;

        saltando = false;
    }
}

void Jugador::moverIzquierda()
{
    velocidadX = -5;
}

void Jugador::moverDerecha()
{
    velocidadX = 5;
}

void Jugador::detener()
{
    velocidadX = 0;
}

void Jugador::saltar()
{
    if(!saltando)
    {
        velocidadY = -12;

        saltando = true;
    }
}

void Jugador::agacharse()
{
    agachado = true;
}

void Jugador::levantarse()
{
    agachado = false;
}

int Jugador::getVida() const
{
    return vida;
}

bool Jugador::getTieneBalon() const
{
    return tieneBalon;
}

void Jugador::setTieneBalon(bool valor)
{
    tieneBalon = valor;
}
