#ifndef NIVELSELVA_H
#define NIVELSELVA_H

#include "Nivel.h"

class NivelSelva : public Nivel
{
private:

    int distanciaRecorrida;

public:

    NivelSelva();

    void actualizar() override;

    void cargarNivel() override;
};

#endif
