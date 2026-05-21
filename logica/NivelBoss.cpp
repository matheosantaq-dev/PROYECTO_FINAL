


#include "NivelBoss.h"

#include <cmath>

NivelBoss::NivelBoss()
{
    jefe = nullptr;

    ia = nullptr;

    modoFuria = false;

    cargarNivel();
}

NivelBoss::~NivelBoss()
{
    delete jefe;

    delete ia;

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
    jugador = new Jugador(400,700);

    jefe = new JefeFinal(400,100);

    ia = new AgenteIA(
        jugador,
        jefe,
        1
    );
}

void NivelBoss::actualizar()
{
    temporizador.actualizar();

    jugador->actualizar();

    jefe->actualizar();

    ia->actualizarIA();

    if(temporizador.getTiempoActual() >= 30
        && !modoFuria)
    {
        modoFuria = true;

        jefe->setVelocidadX(12);

        jefe->setVida(400);
    }

    for(Dardo* dardo : dardos)
    {
        dardo->actualizar();
    }

    for(Balon* balon : balones)
    {
        balon->actualizar();
    }

    if(jefe->getTiempoAtaque() % 120 == 0)
    {
        lanzarDardo();
    }

    for(Balon* balon : balones)
    {
        if(balon->estaActivo())
        {
            float dx =
                balon->getX()
                - jefe->getX();

            float dy =
                balon->getY()
                - jefe->getY();

            if(std::abs(dx) < 50
                && std::abs(dy) < 50)
            {
                balon->desactivar();

                jefe->recibirDanio(20);

                puntaje.agregarPuntos(100);
            }
        }
    }

    for(Dardo* dardo : dardos)
    {
        if(dardo->estaActivo())
        {
            float dx =
                dardo->getX()
                - jugador->getX();

            float dy =
                dardo->getY()
                - jugador->getY();

            if(std::abs(dx) < 40
                && std::abs(dy) < 40)
            {
                dardo->desactivar();

                jugador->recibirDanio(10);
            }
        }
    }

    for(auto it = balones.begin();
        it != balones.end();)
    {
        if(!(*it)->estaActivo())
        {
            delete *it;

            it = balones.erase(it);
        }
        else
        {
            ++it;
        }
    }

    for(auto it = dardos.begin();
        it != dardos.end();)
    {
        if(!(*it)->estaActivo())
        {
            delete *it;

            it = dardos.erase(it);
        }
        else
        {
            ++it;
        }
    }

    if(!jefe->estaVivo())
    {
        terminado = true;
    }

    if(!jugador->estaVivo())
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

int NivelBoss::getPuntaje() const
{
    return puntaje.getPuntos();
}

int NivelBoss::getTiempo() const
{
    return temporizador.getTiempoActual();
}

JefeFinal* NivelBoss::getJefe() const
{
    return jefe;
}

std::vector<Dardo*>&
NivelBoss::getDardos()
{
    return dardos;
}

std::vector<Balon*>&
NivelBoss::getBalones()
{
    return balones;
}
