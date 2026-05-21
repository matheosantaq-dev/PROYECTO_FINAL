#include "Entidad.h"

Entidad::Entidad(float x, float y)
{
    this->x = x;

    this->y = y;

    velocidadX = 0;

    velocidadY = 0;

    ancho = 64;

    alto = 64;
}

Entidad::~Entidad()
{

}

float Entidad::getX() const
{
    return x;
}

float Entidad::getY() const
{
    return y;
}

float Entidad::getVelocidadX() const
{
    return velocidadX;
}

float Entidad::getVelocidadY() const
{
    return velocidadY;
}

int Entidad::getAncho() const
{
    return ancho;
}

int Entidad::getAlto() const
{
    return alto;
}

void Entidad::setX(float x)
{
    this->x = x;
}

void Entidad::setY(float y)
{
    this->y = y;
}

void Entidad::setVelocidadX(float velocidad)
{
    velocidadX = velocidad;
}

void Entidad::setVelocidadY(float velocidad)
{
    velocidadY = velocidad;
}

void Entidad::setAncho(int ancho)
{
    this->ancho = ancho;
}

void Entidad::setAlto(int alto)
{
    this->alto = alto;
}
