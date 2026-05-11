#ifndef DARDO_H
#define DARDO_H

#include "Proyectil.h"

class Dardo : public Proyectil
{
public:

    Dardo(float x, float y);

    void actualizar() override;
};

#endif
