#include "Entidad.h"

Entidad::Entidad(float x, float y, int ancho, int alto)
{
    if (ancho <= 0 || alto <= 0)
        throw std::invalid_argument("Entidad: dimensiones invalidas (deben ser > 0)");

    this->x = x;
    this->y = y;
    this->ancho = ancho;
    this->alto = alto;
    this->velocidadX = 0;
    this->velocidadY = 0;
}

Entidad::~Entidad() {}

// Colision AABB: usa el ancho/alto real de cada entidad
bool Entidad::colisionaCon(const Entidad* otra) const
{
    if (!otra) return false;

    return (x < otra->x + otra->ancho) &&
           (x + ancho > otra->x) &&
           (y < otra->y + otra->alto) &&
           (y + alto > otra->y);
}

float Entidad::getX() const { return x; }
float Entidad::getY() const { return y; }
float Entidad::getVelocidadX() const { return velocidadX; }
float Entidad::getVelocidadY() const { return velocidadY; }
int   Entidad::getAncho() const { return ancho; }
int   Entidad::getAlto() const  { return alto; }

void Entidad::setX(float v)           { x = v; }
void Entidad::setY(float v)           { y = v; }
void Entidad::setVelocidadX(float v)  { velocidadX = v; }
void Entidad::setVelocidadY(float v)  { velocidadY = v; }
void Entidad::setAncho(int v)         { ancho = v; }
void Entidad::setAlto(int v)          { alto = v; }
