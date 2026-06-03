#include "Balon.h"

Balon::Balon(float x, float y, float velocidadX, bool fuerte)
    : Proyectil(x, y, 24, 24), 
    gravedad(0.25f),        
    esFuerte(fuerte)
{
    this->velocidadX = velocidadX;
    this->velocidadY = -9.5f;   // Impulso vertical inicial hacia arriba (vy0 negativo)
    this->activo = true;        // Asegura que la bandera heredada inicie encendida
}

void Balon::actualizar()
{
    if (!activo) return;

    // ── FISICA 2: Trayectoria parabólica ascendente ──
    
    velocidadY += gravedad;

    // Actualización del modelo cinemático integrado
    x += velocidadX;
    y += velocidadY;
}

int Balon::getDanioReal() const
{
    // Si el jugador estaba en modo Fortachon (esFuerte == true) duplica el daño base
    return esFuerte ? 100 : 50;
}
