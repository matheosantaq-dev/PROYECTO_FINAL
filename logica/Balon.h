#ifndef BALON_H
#define BALON_H

#include "Proyectil.h"


// FISICA 2: Trayectoria parabolica ascendente.
// Modelo: y(t) = y0 + vy0*t - 0.5*g*t^2  (vy0 negativo = sube)
// La gravedad reduce gradualmente la velocidad ascendente.
class Balon : public Proyectil
{
private:
    float gravedad;
    bool esFuerte; // si el jugador estaba en modo Fortachon al lanzar

public:
    Balon(float x, float y, float velocidadX, bool fuerte = false);
    void actualizar() override;

    int getDanioReal() const; // Fortachon duplica el danio
};

#endif
