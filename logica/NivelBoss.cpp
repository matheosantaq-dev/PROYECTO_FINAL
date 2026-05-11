#include "NivelBoss.h"

NivelBoss::NivelBoss()
{
    jefe = nullptr;

    cargarNivel();
}

NivelBoss::~NivelBoss()
{
    delete jefe;

    for(Dardo* dardo : dardos)
    {
        delete dardo;
    }

    for(Balon* balon : balones)
    {
        delete balon;
    }

    dardos.clear();
    balones.clear();
}

void NivelBoss::cargarNivel()
{
    
    jugador = new Jugador(400, 700);


    jefe = new JefeFinal(400, 100);
}

void NivelBoss::actualizar()
{
    jugador->actualizar();

    jefe->actualizar();

    // Actualizar dardos
    for(Dardo* dardo : dardos)
    {
        dardo->actualizar();
    }

    // Actualizar balones
    for(Balon* balon : balones)
    {
        balon->actualizar();
    }

    // Ataques automáticos del jefe
    if(jefe->getTiempoAtaque() % 120 == 0)
    {
        lanzarDardo();
    }

    // Verificar derrota del jefe
    if(!jefe->estaVivo())
    {
        terminado = true;
    }
}

void NivelBoss::lanzarBalon()
{
    Balon* nuevoBalon;

    nuevoBalon = new Balon(
        jugador->getX(),
        jugador->getY()
    );

    balones.push_back(nuevoBalon);
}

void NivelBoss::lanzarDardo()
{
    Dardo* nuevoDardo;

    nuevoDardo = new Dardo(
        jefe->getX(),
        jefe->getY()
    );

    dardos.push_back(nuevoDardo);
}
