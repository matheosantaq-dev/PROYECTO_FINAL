include "AgenteIA.h"
#include <cmath>
#include <stdexcept>

AgenteIA::AgenteIA(Jugador* jugador, JefeFinal* jefe, int dificultad)
    : jugador(jugador), jefe(jefe), dificultad(dificultad),
    tendenciaAprendida(0.0f), contadorTicks(0),
    aciertosTotales(0), prediccionesTotales(0)
{
    if (!jugador)
        throw std::invalid_argument("AgenteIA: jugador no puede ser nulo");
    if (!jefe)
        throw std::invalid_argument("AgenteIA: jefe no puede ser nulo");
    if (dificultad < 0 || dificultad > 2)
        throw std::invalid_argument("AgenteIA: dificultad debe ser 0, 1 o 2");

   
    // FACIL: decide cada 60 ticks (1s) — DIFICIL: cada 8 ticks (muy rapido)
    switch (dificultad)
    {
    case 0: intervaloDecision = 60; break;
    case 1: intervaloDecision = 30; break;
    case 2: intervaloDecision =  8; break;
    }
}


// (a) PERCEPCION

RegistroPercepcion AgenteIA::percibir()
{
    RegistroPercepcion r;
    r.posX     = jugador->getX();
    r.posY     = jugador->getY();
    r.velX     = jugador->getVelocidadX();
    r.agachado = jugador->getAgachado();
    r.tick     = contadorTicks;
    return r;
}


// (d) APRENDIZAJE
// Guarda el registro en una ventana deslizante de 30 entradas.
// Calcula la tendencia promedio de movimiento del jugador.
// Con mas historial, la prediccion se vuelve mas precisa.
// ════════════════════════════════════════════════════════════
void AgenteIA::aprender(const RegistroPercepcion& p)
{
    historial.push_back(p);
    if (historial.size() > 30)
        historial.erase(historial.begin());

    // Calcular tendencia: promedio de deltas de posicion recientes
    if (historial.size() >= 2)
    {
        float sumaDeltas = 0.0f;
        int n = static_cast<int>(historial.size());
        int ventana = std::min(n - 1, 5); 

        for (int i = n - ventana - 1; i < n - 1; ++i)
            sumaDeltas += historial[i + 1].posX - historial[i].posX;

        tendenciaAprendida = sumaDeltas / ventana;
    }
}


// (b) RAZONAMIENTO
// Interpreta el historial y decide a donde deberia moverse el jefe.
// Con poco historial: persigue directamente.
// Con mas historial: predice posicion futura del jugador.
// Si el jugador esta agachado: sospecha de trampa y reduce prediccion.

float AgenteIA::razonar(const RegistroPercepcion& p)
{
    float xObjetivo = p.posX;

    prediccionesTotales++;

    if (historial.size() >= 5)
    {
        // Prediccion: donde estara el jugador en N ticks
        float pasos;
        switch (dificultad)
        {
        case 0: pasos = 2.0f; break;
        case 1: pasos = 6.0f; break;
        case 2: pasos = 14.0f; break;
        default: pasos = 4.0f;
        }

        // Si el jugador esta agachado, la prediccion se reduce
        // (puede estar esperando para cambiar de direccion)
        if (p.agachado)
            pasos *= 0.3f;

        xObjetivo = p.posX + tendenciaAprendida * pasos;

        // Verificar si la prediccion anterior fue acertada
        if (historial.size() >= 2 && prediccionesTotales > 1)
        {
            float errorPrediccion = std::abs(jefe->getX() - p.posX);
            if (errorPrediccion < 60.0f)
                aciertosTotales++;
        }
    }

    // Limitar objetivo a area valida
    xObjetivo = std::max(50.0f, std::min(xObjetivo, 1100.0f));
    return xObjetivo;
}


// (c) ACCION
// Mueve al jefe hacia la posicion objetivo con velocidad
// proporcional a la dificultad. La sinusoide del jefe se
// ajusta en xCentro — esto interactua con la fisica del jefe.

void AgenteIA::actualizarIA()
{
    contadorTicks++;

    RegistroPercepcion percepcion = percibir();
    aprender(percepcion);


    if (contadorTicks % intervaloDecision != 0)
        return;

    float xObjetivo = razonar(percepcion);

    // Velocidad de reaccion segun dificultad
    float velBase;
    switch (dificultad)
    {
    case 0: velBase = 1.5f; break;
    case 1: velBase = 3.0f; break;
    case 2: velBase = 5.5f; break;
    default: velBase = 2.5f;
    }

    float dx = xObjetivo - jefe->getX();
    if (std::abs(dx) > 15.0f)
        jefe->setVelocidadX(dx > 0 ? velBase : -velBase);
    else
        jefe->setVelocidadX(0.0f);
}

float AgenteIA::getTendenciaAprendida() const { return tendenciaAprendida; }
int   AgenteIA::getTamanoHistorial()    const { return static_cast<int>(historial.size()); }

float AgenteIA::getTasaAcierto() const
{
    if (prediccionesTotales == 0) return 0.0f;
    return static_cast<float>(aciertosTotales) / prediccionesTotales * 100.0f;
}
