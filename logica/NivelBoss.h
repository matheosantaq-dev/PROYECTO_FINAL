#ifndef NIVELBOSS_H
#define NIVELBOSS_H

#include <vector>

#include "Nivel.h"
#include "JefeFinal.h"
#include "Dardo.h"
#include "Balon.h"

#include "AgenteIA.h"
#include "PuntajeJuego.h"
#include "TemporizadorJuego.h"

class NivelBoss : public Nivel
{
private:

    JefeFinal* jefe;

    AgenteIA* ia;

    std::vector<Dardo*> dardos;

    std::vector<Balon*> balones;

    PuntajeJuego puntaje;

    TemporizadorJuego temporizador;

    bool modoFuria;

public:

    NivelBoss();

    ~NivelBoss();

    void actualizar() override;

    void cargarNivel() override;

    void lanzarBalon();

    void lanzarDardo();

    int getPuntaje() const;

    int getTiempo() const;

    JefeFinal* getJefe() const;
};

#endif
