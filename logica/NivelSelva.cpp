#include "NivelSelva.h"

NivelSelva::NivelSelva()
{
    distanciaRecorrida = 0;

    tiempoNivel = 0;

    puntos = 0;

    enemigosDerrotados = 0;

    cargarNivel();
}

void NivelSelva::cargarNivel()
{
    jugador = new Jugador(
        100,
        620
        );

    // enemigos más lejos
    enemigos.push_back(
        new Enemigo(
            800,
            620
            )
        );

    enemigos.push_back(
        new Enemigo(
            1200,
            620
            )
        );

    enemigos.push_back(
        new Enemigo(
            1600,
            620
            )
        );
}

void NivelSelva::actualizar()
{
    jugador->actualizar();

    for(Enemigo* enemigo : enemigos)
    {
        enemigo->actualizar();

        // colisión MUCHO más pequeña
        float dx =
            jugador->getX()
            -
            enemigo->getX();

        float dy =
            jugador->getY()
            -
            enemigo->getY();

        if(
           dx<25 && dx>-25 &&
           dy<25 && dy>-25
           )
        {
            jugador->recibirDanio(
                1
                );
        }
    }

    distanciaRecorrida =
        jugador->getX();

    puntos =
        distanciaRecorrida/10;

    tiempoNivel++;

    if(
       !jugador->estaVivo()
       )
    {
        terminado=true;
    }

    if(
       distanciaRecorrida>=1500
       )
    {
        terminado=true;
    }
}

int NivelSelva::getDistancia() const
{
    return distanciaRecorrida;
}

int NivelSelva::getTiempo() const
{
    return tiempoNivel/60;
}

int NivelSelva::getPuntos() const
{
    return puntos;
}

int NivelSelva::getEnemigosDerrotados() const
{
    return enemigosDerrotados;
}
