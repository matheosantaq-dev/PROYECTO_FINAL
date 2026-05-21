#include "NivelBoss.h"

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
    // Crear jugador
    jugador = new Jugador(400, 700);

    // Crear jefe
    jefe = new JefeFinal(400, 100);

    // Crear IA
    ia = new AgenteIA(
        jugador,
        jefe,
        1
    );
}

void NivelBoss::actualizar()
{
    // Actualizar tiempo
    temporizador.actualizar();

   
    jugador->actualizar();

  
    jefe->actualizar();

    
    ia->actualizarIA();

    // Activar modo furia
    if(temporizador.getTiempoActual() >= 30
        && !modoFuria)
    {
        modoFuria = true;

        jefe->setVelocidadX(12);

        jefe->setVida(
            jefe->getVida() + 200
        );
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

    // Colisiones balones vs jefe
    for(Balon* balon : balones)
    {
        if(balon->estaActivo())
        {
            float dx =
                balon->getX() - jefe->getX();

            float dy =
                balon->getY() - jefe->getY();

            if(dx < 50 && dx > -50 &&
               dy < 50 && dy > -50)
            {
                balon->desactivar();

                jefe->recibirDanio(20);

                puntaje.agregarPuntos(100);
            }
        }
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
