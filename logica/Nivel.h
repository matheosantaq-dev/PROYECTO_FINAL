

#ifndef NIVEL_H
#define NIVEL_H

#include <vector>

#include "Jugador.h"
#include "Enemigo.h"

class Nivel
{
protected:

    Jugador* jugador;

    std::vector<Enemigo*> enemigos;

    bool terminado;

public:

    Nivel();

    virtual ~Nivel();

    virtual void actualizar() = 0;

    virtual void cargarNivel() = 0;

    virtual void lanzarBalon();

    bool estaTerminado() const;

    Jugador* getJugador() const;

    std::vector<Enemigo*>&
    getEnemigos();
};

#endif
