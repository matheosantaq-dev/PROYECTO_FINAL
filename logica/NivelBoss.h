#ifndef NIVELBOSS_H
#define NIVELBOSS_H

#include <vector>

#include "Nivel.h"
#include "JefeFinal.h"
#include "Dardo.h"
#include "Balon.h"

class NivelBoss : public Nivel
{
private:

    JefeFinal* jefe;

    std::vector<Dardo*> dardos;

    std::vector<Balon*> balones;

public:

    NivelBoss();

    ~NivelBoss();

    void actualizar() override;

    void cargarNivel() override;

    void lanzarBalon();

    void lanzarDardo();
};

#endif
