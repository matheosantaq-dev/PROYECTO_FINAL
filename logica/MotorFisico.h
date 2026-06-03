#ifndef MOTORFISICO_H
#define MOTORFISICO_H

#include "Entidad.h"

// Motor de colisiones AABB.
// Usa las dimensiones reales (ancho/alto) de cada entidad.
class MotorFisico
{
public:
    static bool detectarColision(const Entidad* a, const Entidad* b);
};

#endif
