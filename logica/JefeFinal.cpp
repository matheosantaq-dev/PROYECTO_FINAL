

#include "JefeFinal.h"
#include <cmath>

JefeFinal::JefeFinal(float x, float y)
    : Enemigo(x, y),
    fase(1), tiempoAtaque(0),
    xCentro(x), amplitud(260.0f),
    omega(0.025f), ticksGlobales(0)
{
    vida = 100;
    vidaMaxima = 100;
    velocidadMovimiento = 0;

   

    // Hitbox física alineada correctamente al tamaño real de su sprite
    this->ancho = 128;
    this->alto = 128;
}

void JefeFinal::actualizar()
{
    if (!estaVivo()) return;

    ticksGlobales++;
    tiempoAtaque++;

    // Movimiento oscilatorio de la liana usando su nuevo origen superior 
    x = xCentro + amplitud * std::sin(omega * ticksGlobales);

    // Cambio de fase automático al llegar al 50% de HP o menos
    if (vida <= (vidaMaxima / 2) && fase == 1) {
        cambiarFase();
    }
}

void JefeFinal::cambiarFase()
{
    fase = 2;
    omega = 0.045f;
    amplitud = 300.0f;
}

void JefeFinal::setVida(int v)
{
    vida = v;
    if (vida < 0) vida = 0;
    if (vida == 0) vivo = false;
}

void JefeFinal::setDificultad(int dif)
{
    switch (dif)
    {
    case 0: // FACIL
        omega = 0.018f;
        vida = 70;
        vidaMaxima = 70;
        break;
    case 1: // INTERMEDIO
        omega = 0.025f;
        vida = 100;
        vidaMaxima = 100;
        break;
    case 2: // DIFICIL
        omega = 0.038f;
        vida = 140;
        vidaMaxima = 140;
        break;
    default:
        omega = 0.025f;
        vida = 100;
        vidaMaxima = 100;
    }
}
