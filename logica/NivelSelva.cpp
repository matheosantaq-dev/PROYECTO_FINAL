#include "NivelSelva.h"

NivelSelva::NivelSelva()
{
    distanciaRecorrida = 0;

    cargarNivel();
}

void NivelSelva::cargarNivel()
{
    jugador = new Jugador(100, 500);

    // enemigos  selva
    enemigos.push_back(new Enemigo(400, 500));
    enemigos.push_back(new Enemigo(700, 500));
    enemigos.push_back(new Enemigo(1000, 500));
}

void NivelSelva::actualizar()
{
  
    jugador->actualizar();

    
    for(Enemigo* enemigo : enemigos)
    {
        enemigo->actualizar();
    }

    distanciaRecorrida = jugador->getX();

    // Objetivo del nivel
    if(distanciaRecorrida >= 1500)
    {
        terminado = true;
    }
}
