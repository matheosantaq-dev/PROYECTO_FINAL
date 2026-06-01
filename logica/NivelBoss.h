// =========================
// NivelBoss.h
// =========================

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

    int ultimoTiempoAtaque;

public:

    NivelBoss();

    ~NivelBoss();

    void actualizar() override;

    void cargarNivel() override;

    void lanzarBalon() override;

    void lanzarDardo();

    int getPuntaje() const;

    int getTiempo() const;

    JefeFinal* getJefe() const;

    std::vector<Dardo*>&
    getDardos();

    std::vector<Balon*>&
    getBalones();
};

#endif
