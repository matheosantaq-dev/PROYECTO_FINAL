#ifndef MOTORFISICO_H
#define MOTORFISICO_H

#include "Entidad.h"

class MotorFisico
{
public:

    static bool detectarColision(
            Entidad* a,
            Entidad* b);
};

#endif
