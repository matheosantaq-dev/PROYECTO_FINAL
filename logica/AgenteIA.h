#ifndef AGENTEIA_H
#define AGENTEIA_H

#include "Jugador.h"
#include "JefeFinal.h"

class AgenteIA
{
private:

    Jugador* jugador;

    JefeFinal* jefe;

    int dificultad;

public:

    AgenteIA(Jugador* jugador,
             JefeFinal* jefe,
             int dificultad);

    void actualizarIA();
};

#endif
