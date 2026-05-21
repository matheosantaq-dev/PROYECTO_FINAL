

#include "Jugador.h"

Jugador::Jugador(float x, float y)
    : Entidad(x, y)
{
    vida = 100;

    saltando = false;

    agachado = false;

    tieneBalon = false;

    gravedad = 0.5f;

    fuerzaSalto = -12.0f;
}

void Jugador::mover()
{
    x += velocidadX;

    y += velocidadY;
}

void Jugador::actualizar()
{
    velocidadY += gravedad;

    mover();

    if(x < 0)
    {
        x = 0;
    }

    if(x > 1100)
    {
        x = 1100;
    }

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
        velocidadY = fuerzaSalto;

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

void Jugador::recibirDanio(int danio)
{
    vida -= danio;

    if(vida < 0)
    {
        vida = 0;
    }
}

bool Jugador::estaVivo() const
{
    return vida > 0;
}

int Jugador::getVida() const
{
    return vida;
}

bool Jugador::getSaltando() const
{
    return saltando;
}

bool Jugador::getAgachado() const
{
    return agachado;
}

bool Jugador::getTieneBalon() const
{
    return tieneBalon;
}

void Jugador::setTieneBalon(bool valor)
{
    tieneBalon = valor;
}
