#include "Jugador.h"

Jugador::Jugador(float x, float y)
    : Entidad(x, y)
{
    vida = 100;

    saltando = false;

    agachado = false;

    tieneBalon = false;

    mirandoDerecha = true;

    gravedad = 0.5f;

    fuerzaSalto = -12.0f;
}

void Jugador::curar(int cantidad)
{
    vida += cantidad;

    if(vida > 100)
    {
        vida = 100;
    }
}

void Jugador::mover()
{
    x += velocidadX;

    y += velocidadY;
}

void Jugador::actualizar()
{
    if(velocidadX > 0)
    {
        velocidadX -= 0.2f;
    
        if(velocidadX < 0)
        {
            velocidadX = 0;
        }
    }

    if(velocidadX < 0)
    {
        velocidadX += 0.2f;
    
        if(velocidadX > 0)
        {
            velocidadX = 0;
        }
    }
    velocidadY += gravedad;

    if(velocidadY < -20)
    {
        velocidadY = -20;
    }
    
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
    mirandoDerecha = false;
    velocidadX -= 1.0f;

    if(velocidadX < -5.0f)
    {
        velocidadX = -5.0f;
    }
}

void Jugador::moverDerecha()
{
    mirandoDerecha = true;
    velocidadX += 1.0f;

    if(velocidadX > 5.0f)
    {
        velocidadX = 5.0f;
    }
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
