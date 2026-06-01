

#include "JefeFinal.h"

JefeFinal::JefeFinal(float x, float y)
    : Enemigo(x, y)
{
    vida = 200;

    fase = 1;

    velocidadMovimiento = 5;

    velocidadAtaque = 1.0;

    tiempoAtaque = 0;

    velocidadX = velocidadMovimiento;
}

void JefeFinal::actualizar()
{
    if(!estaVivo())
    {
        return;
    }
    
    mover();

    tiempoAtaque++;

    // Movimiento lateral
    if(x <= 100)
    {
        velocidadX = velocidadMovimiento;
    }

    if(x >= 700)
    {
        velocidadX = -velocidadMovimiento;
    }

    // Cambio de fase
    if(vida <= 100 && fase == 1)
    {
        cambiarFase();
    }
}

void JefeFinal::cambiarFase()
{
    fase = 2;

    velocidadMovimiento = 8;

    velocidadAtaque = 2.0;
}

int JefeFinal::getFase() const
{
    return fase;
}

int JefeFinal::getTiempoAtaque() const
{
    return tiempoAtaque;
}

void JefeFinal::setVida(int nuevaVida)
{
    vida = nuevaVida;
}

