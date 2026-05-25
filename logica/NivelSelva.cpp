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

    // JUGADOR
 

    jugador = new Jugador(100, 620);

    // ENEMIGOS

    enemigos.push_back(
        new Enemigo(500, 620)
        );

    enemigos.push_back(
        new Enemigo(900, 620)
        );

    enemigos.push_back(
        new Enemigo(1300, 620)
        );
}

void NivelSelva::actualizar()
{
    
    // ACTUALIZAR JUGADOR
  

    jugador->actualizar();


    // ACTUALIZAR ENEMIGOS


    for(Enemigo* enemigo : enemigos)
    {
        enemigo->actualizar();

        // COLISION BASICA
     

        float dx =
            jugador->getX()
            - enemigo->getX();

        float dy =
            jugador->getY()
            - enemigo->getY();

        if(dx < 60 && dx > -60
            && dy < 60 && dy > -60)
        {
            jugador->recibirDanio(1);
        }
    }

    // DISTANCIA


    distanciaRecorrida =
        jugador->getX();

    // PUNTOS


    puntos =
        distanciaRecorrida / 10;

    // TIEMPO


    tiempoNivel++;

    // DERROTA
 

    if(!jugador->estaVivo())
    {
        terminado = true;
    }

    // FINAL NIVEL


    if(distanciaRecorrida >= 1500)
    {
        terminado = true;
    }
}

int NivelSelva::getDistancia() const
{
    return distanciaRecorrida;
}

int NivelSelva::getTiempo() const
{
    return tiempoNivel / 60;
}

int NivelSelva::getPuntos() const
{
    return puntos;
}

int NivelSelva::getEnemigosDerrotados() const
{
    return enemigosDerrotados;
}
