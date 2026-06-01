#include "AgenteIA.h"

AgenteIA::AgenteIA(Jugador* jugador,
                   JefeFinal* jefe,
                   int dificultad)
{
    this->jugador = jugador;

    this->jefe = jefe;

    this->dificultad = dificultad;
}

void AgenteIA::actualizarIA()
{
    int velocidadIA = 2;

    // Dificultad afecta IA
    if(dificultad == 0)
    {
        velocidadIA = 1;
    }

    if(dificultad == 1)
    {
        velocidadIA = 3;
    }

    if(dificultad == 2)
    {
        velocidadIA = 5;
    }

    // Boss sigue al jugador
    if(jugador->getX() < jefe->getX())
    {
        jefe->setVelocidadX(
            -velocidadIA
        );
    }

    if(jugador->getX() > jefe->getX())
    {
        jefe->setVelocidadX(
            velocidadIA
        );
    }
}
