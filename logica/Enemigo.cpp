#include "Enemigo.h"
#include <stdexcept>

Enemigo::Enemigo(float x, float y, float limIzq, float limDer)
    : Entidad(x, y, 64, 64),
    vida(100),
    velocidadMovimiento(3.0f),
    vivo(true), moviendoDerecha(true),
    limiteIzq(limIzq), limiteDer(limDer)
{
    velocidadX = velocidadMovimiento;
}

Enemigo::~Enemigo() {}

void Enemigo::mover()
{
    x += velocidadX;
}

void Enemigo::actualizar()
{
    if (!vivo) return;
    mover();

    if (x <= limiteIzq)
    {
        moviendoDerecha = true;
        velocidadX = velocidadMovimiento;
    }
    if (x >= limiteDer)
    {
        moviendoDerecha = false;
        velocidadX = -velocidadMovimiento;
    }
}

// ÚNICA DEFINICIÓN DE LA FUNCIÓN
void Enemigo::recibirDanio(int cantidad)
{
    if (cantidad < 0)
        throw std::invalid_argument("Enemigo::recibirDanio: valor negativo");

    vida -= cantidad;

    if (vida <= 0) {
        vida = 0;
        vivo = false;
    }
}

bool Enemigo::estaVivo() const { return vivo; }
int  Enemigo::getVida()  const { return vida; }
