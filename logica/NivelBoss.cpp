#include "NivelBoss.h"
#include <cmath>
#include <stdexcept>
#include <vector>

NivelBoss::NivelBoss(int dificultad)
    : jefe(nullptr), ia(nullptr),
    dificultad(dificultad), modoFuria(false),
    ultimoTickAtaque(-1), ticksInvulnerable(0)
{
    if (dificultad < 0 || dificultad > 2)
        throw std::invalid_argument("NivelBoss: dificultad invalida");

    // Intervalo entre dardos segun dificultad
    switch (dificultad)
    {
    case 0: intervaloAtaque = 150; break; // FACIL: 2.5s
    case 1: intervaloAtaque = 100; break; // MEDIO: ~1.7s
    case 2: intervaloAtaque =  60; break; // DIFICIL: 1s
    }

    try
    {
        cargarNivel();
    }
    catch (const std::exception& e)
    {
        throw std::runtime_error(
            std::string("NivelBoss: error al cargar — ") + e.what());
    }
}

NivelBoss::~NivelBoss()
{
    delete jefe;
    delete ia;

    for (Dardo* d : dardos)   delete d;
    for (Balon* b : balones)  delete b;
    dardos.clear();
    balones.clear();
}

void NivelBoss::cargarNivel()
{
    // Jugador en la parte inferior — piso en y=680
    jugador = new Jugador(560, 380, 520.0f);

    // CORRECCIÓN: Se cambia Y de 500.0f a 220.0f para ubicar al jefe claramente por encima de la mitad
    // de la pantalla (720 / 2 = 360). Así simula estar colgado y es alcanzable por los balones.
    jefe = new JefeFinal(560, 60.0f);
    jefe->setDificultad(dificultad);

    // Agente IA con los 4 componentes
    ia = new AgenteIA(jugador, jefe, dificultad);
}

void NivelBoss::actualizar()
{
    if (!jugador || !jefe)
        throw std::runtime_error("NivelBoss::actualizar — punteros nulos");

    if (estado == TRANSICION)
    {
        actualizarTransicion();
        return;
    }
    if (estado == TERMINADO) return;

    temporizador.actualizar();

    jugador->actualizar();
    jefe->actualizar();
    ia->actualizarIA();

    // ── Modo furia al 50% de vida ─────────────────────────
    if (!modoFuria && jefe->getVida() <= (dificultad == 0 ? 35 : dificultad == 1 ? 50 : 70))
    {
        modoFuria = true;
        intervaloAtaque = std::max(40, intervaloAtaque - 30);
    }

    // ── Disparo automatico de dardos ──────────────────────
    int tiempoActual = temporizador.getTicks();
    if (tiempoActual - ultimoTickAtaque >= intervaloAtaque)
    {
        lanzarDardo();
        ultimoTickAtaque = tiempoActual;
    }

    // ── Actualizar proyectiles ────────────────────────────
    for (Dardo* d : dardos)  d->actualizar();
    for (Balon* b : balones) b->actualizar();

    // ── Colisiones ───────────────────────────────────────
    verificarColisiones();
    limpiarProyectilesInactivos();

    // ── Condiciones de fin ────────────────────────────────
    if (!jefe->estaVivo())
    {
        // CORRECCIÓN: Se otorgan los +30 puntos exactos al jugador al derrotar al jefe antes de guardar el nivel
        jugador->agregarPuntos(30);
        puntaje.guardarNivel();
        iniciarTransicion(210); // 3.5s celebracion
        return;
    }

    if (!jugador->estaVivo())
    {
        estado = TERMINADO;
    }
}

void NivelBoss::verificarColisiones()
{
    // ── Balon golpea al jefe ──────────────────────────────
    for (Balon* b : balones)
    {
        if (!b->estaActivo()) continue;

        if (jefe && jefe->estaVivo() && b->colisionaCon(jefe))
        {
            b->desactivar();

            // Daño dinámico escalonado basado en el 50% de HP del jefe
            int danioDinamico = (jefe->getVida() <= (jefe->getVidaMaxima() / 2)) ? 10 : 5;

            jefe->setVida(jefe->getVida() - danioDinamico);
        }
    }

    // ── Dardo golpea al jugador ───────────────────────────
    if (ticksInvulnerable > 0)
    {
        --ticksInvulnerable;
        return;
    }

    for (Dardo* d : dardos)
    {
        if (!d->estaActivo()) continue;
        if (d->colisionaCon(jugador))
        {
            d->desactivar();
            jugador->recibirDanio(d->getDanio());
            ticksInvulnerable = 45;
        }
    }
}

void NivelBoss::limpiarProyectilesInactivos()
{
    for (auto it = balones.begin(); it != balones.end(); )
    {
        if (!(*it)->estaActivo() || (*it)->getY() < -50.0f)
        {
            delete *it;
            it = balones.erase(it);
        }
        else ++it;
    }

    for (auto it = dardos.begin(); it != dardos.end(); )
    {
        if (!(*it)->estaActivo()) { delete *it; it = dardos.erase(it); }
        else ++it;
    }
}

void NivelBoss::lanzarBalon()
{
    float offsetX = jugador->estaMirandoDerecha() ? 30.0f : -30.0f;
    balones.push_back(
        new Balon(
            jugador->getX() + offsetX,
            jugador->getY() - 10,
            0.0f,
            jugador->esFortachon()
            )
        );
}

void NivelBoss::lanzarDardo()
{
    std::vector<Dardo*>& d = dardos;
    d.push_back(new Dardo(jefe->getX(), jefe->getY() + 40, dificultad));

    if (modoFuria)
    {
        d.push_back(new Dardo(jefe->getX() - 30, jefe->getY() + 30, dificultad));
        d.push_back(new Dardo(jefe->getX() + 30, jefe->getY() + 30, dificultad));
    }
}

JefeFinal* NivelBoss::getJefe()            const { return jefe; }
std::vector<Dardo*>& NivelBoss::getDardos()                { return dardos; }
std::vector<Balon*>& NivelBoss::getBalones()               { return balones; }
int                  NivelBoss::getTiempoSegundos()   const { return temporizador.getTiempoSegundos(); }
bool                 NivelBoss::getModoFuria()         const { return modoFuria; }



