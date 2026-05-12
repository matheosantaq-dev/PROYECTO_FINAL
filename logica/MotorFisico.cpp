#include "MotorFisico.h"

bool MotorFisico::detectarColision(
        Entidad* a,
        Entidad* b)
{
    float ax = a->getX();
    float ay = a->getY();

    float bx = b->getX();
    float by = b->getY();

    // Colisión 

    if(ax < bx + 50 &&
       ax + 50 > bx &&
       ay < by + 50 &&
       ay + 50 > by)
    {
        return true;
    }

    return false;
}
