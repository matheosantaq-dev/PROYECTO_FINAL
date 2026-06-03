#include "NivelSelva.h"
#include <stdexcept>
#include <cmath>
#include <algorithm>

NivelSelva::NivelSelva()
    : distanciaRecorrida(0), tiempoNivel(0),
    enemigosDerrotados(0), metaX(4544.0f),
    ticksInvulnerable(0)
{
    try
    {
        cargarNivel();
    }
    catch (const std::exception& e)
    {
        throw std::runtime_error(
            std::string("NivelSelva::NivelSelva — error al cargar: ") + e.what());
    }
}

NivelSelva::~NivelSelva()
{
    for (Obstaculo* o : obstaculos)
        delete o;
    obstaculos.clear();
}

void NivelSelva::cargarNivel()
{
    // Jugador en posición inicial — la hitbox física se asienta sobre el suelo en y=550 
    jugador = new Jugador(120, 900, 550.0f);


    
    enemigos.push_back(new Enemigo(450,  550.0f, 350.0f,  650.0f));
    enemigos.push_back(new Enemigo(700,  550.0f, 600.0f,  950.0f));
    enemigos.push_back(new Enemigo(950,  550.0f, 850.0f, 1200.0f));

    enemigos.push_back(new Enemigo(1250, 550.0f, 1150.0f, 1450.0f));
    enemigos.push_back(new Enemigo(1500, 550.0f, 1400.0f, 1700.0f));
    enemigos.push_back(new Enemigo(1750, 550.0f, 1650.0f, 1950.0f));

    enemigos.push_back(new Enemigo(2000, 550.0f, 1900.0f, 2200.0f));
    enemigos.push_back(new Enemigo(2250, 550.0f, 2150.0f, 2450.0f));
    enemigos.push_back(new Enemigo(2500, 550.0f, 2400.0f, 2700.0f));

    enemigos.push_back(new Enemigo(2750, 550.0f, 2650.0f, 2950.0f));
    enemigos.push_back(new Enemigo(3000, 550.0f, 2900.0f, 3200.0f));
    enemigos.push_back(new Enemigo(3250, 550.0f, 3150.0f, 3450.0f));

    enemigos.push_back(new Enemigo(3500, 550.0f, 3400.0f, 3700.0f));
    enemigos.push_back(new Enemigo(3700, 550.0f, 3600.0f, 3900.0f));
    enemigos.push_back(new Enemigo(3900, 550.0f, 3800.0f, 4100.0f));

    enemigos.push_back(new Enemigo(4100, 550.0f, 4000.0f, 4300.0f));
    enemigos.push_back(new Enemigo(4250, 550.0f, 4150.0f, 4400.0f));
    enemigos.push_back(new Enemigo(4400, 550.0f, 4300.0f, 4550.0f));


    obstaculos.push_back(new Obstaculo(350,  490, 130, 18));
    obstaculos.push_back(new Obstaculo(700,  430, 110, 18));
    obstaculos.push_back(new Obstaculo(1050, 370, 140, 18));
    obstaculos.push_back(new Obstaculo(1400, 310, 120, 18));
    obstaculos.push_back(new Obstaculo(2000, 440, 150, 18));
    obstaculos.push_back(new Obstaculo(2600, 380, 130, 18));
    obstaculos.push_back(new Obstaculo(3200, 420, 140, 18));
    obstaculos.push_back(new Obstaculo(3800, 350, 120, 18));
}

void NivelSelva::actualizar()
{
    if (!jugador)
        throw std::runtime_error("NivelSelva::actualizar — jugador nulo");

    if (estado == TRANSICION)
    {
        actualizarTransicion();
        return;
    }
    if (estado == TERMINADO) return;

    tiempoNivel++;
    jugador->actualizar();

    // Colisión jugador con plataformas 
    for (Obstaculo* o : obstaculos)
    {
        if (jugador->colisionaCon(o))
        {
            float jBase = jugador->getY() + jugador->getAlto();
            float pTop  = o->getY();

            if (jugador->getVelocidadY() > 0 && jBase <= pTop + 12)
            {
                jugador->setY(pTop - jugador->getAlto());
                jugador->setVelocidadY(0);
            }
        }
    }

    //  Colisión jugador con enemigos
    if (ticksInvulnerable > 0)
        --ticksInvulnerable;

    for (Enemigo* e : enemigos)
    {
        if (!e->estaVivo()) continue;

        e->actualizar();

        if (ticksInvulnerable == 0 && jugador->colisionaCon(e))
        {
            jugador->recibirDanio(5);
            ticksInvulnerable = 60;
            jugador->activarVeloz(120);
        }
    }

    distanciaRecorrida = static_cast<int>(jugador->getX());

    // ─Condiciones de finalización 
    if (!jugador->estaVivo())
    {
        estado = TERMINADO;
        return;
    }

    bool todosMuertos = true;

    for (Enemigo* e : enemigos)
    {
        if (e && e->estaVivo())
        {
            todosMuertos = false;
            break;
        }
    }

    if (distanciaRecorrida >= static_cast<int>(metaX) && todosMuertos)
    {
        puntaje.guardarNivel();
        iniciarTransicion(180);
    }

} 

void NivelSelva::lanzarBalon()
{


    const float RANGO_PATADA = 150.0f;

    for (Enemigo* e : enemigos)
    {
        if (!e->estaVivo()) continue;

        float dx = jugador->getX() - e->getX();
        float dy = jugador->getY() - e->getY();
        float dist = std::sqrt(dx * dx + dy * dy);

        if (dist < RANGO_PATADA)
        {
        
            e->recibirDanio(17);

            if (!e->estaVivo())
            {
                ++enemigosDerrotados;
                // Sumamos los 10 puntos estrictos
                jugador->agregarPuntos(10);
                jugador->activarFortachon(300);
            }
            break; 
        }
    }
}
int   NivelSelva::getDistancia()          const { return distanciaRecorrida; }
int   NivelSelva::getTiempoSegundos()     const { return tiempoNivel / 60; }
int   NivelSelva::getEnemigosDerrotados() const { return enemigosDerrotados; }
float NivelSelva::getProgresoMeta()       const
{
    return std::min(1.0f, distanciaRecorrida / metaX);
}

const std::vector<Obstaculo*>& NivelSelva::getObstaculos() const
{
    return obstaculos;
}
