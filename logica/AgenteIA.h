#ifndef AGENTEIA_H
#define AGENTEIA_H

#include "Jugador.h"
#include "JefeFinal.h"
#include <vector>

// Registro de percepcion: captura el estado del jugador en un instante
struct RegistroPercepcion
{
    float posX;
    float posY;
    float velX;
    bool  agachado;
    int   tick;
};

// Agente Inteligente que controla al JefeFinal.
// Implementa los 4 componentes obligatorios:
//   a) PERCEPCION  — lee posicion, velocidad y estado del jugador
//   b) RAZONAMIENTO — calcula donde va a estar el jugador y decide accion
//   c) ACCION       — mueve al jefe hacia la posicion predicha
//   d) APRENDIZAJE  — guarda historial y mejora la prediccion con el tiempo
class AgenteIA
{
private:
    Jugador*   jugador;
    JefeFinal* jefe;
    int        dificultad;

    // (d) APRENDIZAJE: historial de posiciones (ventana deslizante de 30 registros)
    std::vector<RegistroPercepcion> historial;
    float tendenciaAprendida;  
    int   contadorTicks;
    int   intervaloDecision;    
    int   aciertosTotales;      
    int   prediccionesTotales;  

    // (a) PERCEPCION
    RegistroPercepcion percibir();

    // (b) RAZONAMIENTO
    float razonar(const RegistroPercepcion& p);

    // (d) APRENDIZAJE
    void aprender(const RegistroPercepcion& p);

public:
    AgenteIA(Jugador* jugador, JefeFinal* jefe, int dificultad);

    // (c) ACCION — punto de entrada principal
    void actualizarIA();

    // Metricas de aprendizaje (utiles para HUD debug y sustentacion)
    float getTendenciaAprendida()  const;
    int   getTamanoHistorial()     const;
    float getTasaAcierto()         const;
};

#endif
