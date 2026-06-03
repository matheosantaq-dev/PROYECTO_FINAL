#include "MotorFisico.h"

bool MotorFisico::detectarColision(const Entidad* a, const Entidad* b)
{
    if (!a || !b) return false;
    return a->colisionaCon(b);
}
