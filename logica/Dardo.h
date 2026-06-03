#ifndef DARDO_H
#define DARDO_H

#include "Proyectil.h"

// Cae verticalmente con aceleracion ligera (no puramente rectilineo).
class Dardo : public Proyectil
{
public:
    Dardo(float x, float y, int dificultad = 1);
    void actualizar() override;
};

#endif
