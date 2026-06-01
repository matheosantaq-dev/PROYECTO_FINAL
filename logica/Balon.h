#ifndef BALON_H
#define BALON_H

#include "Proyectil.h"

class Balon : public Proyectil
{
public:

    Balon(
        float x,
        float y,
        float velocidadX
    );

    void actualizar() override;
};

#endif
