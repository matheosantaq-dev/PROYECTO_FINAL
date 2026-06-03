#ifndef NIVEL_H
#define NIVEL_H

#include <vector>
#include "Jugador.h"
#include "Enemigo.h"
#include "PuntajeJuego.h"

// Estado en que puede estar la transicion del nivel
enum EstadoNivel
{
    JUGANDO,
    TRANSICION, 
    TERMINADO
};

// Clase abstracta base para todos los niveles.
class Nivel
{
protected:
    Jugador*             jugador;
    std::vector<Enemigo*> enemigos;
    PuntajeJuego         puntaje;
    EstadoNivel          estado;
    int                  ticksTransicion;  

public:
    Nivel();
    virtual ~Nivel();

    virtual void actualizar()   = 0;
    virtual void cargarNivel()  = 0;
    virtual void lanzarBalon()  = 0;

    // Inicia la secuencia de transicion (duracion en ticks)
    void iniciarTransicion(int duracionTicks = 180);
    void actualizarTransicion();

    bool estaTerminado()   const;
    bool enTransicion()    const;
    EstadoNivel getEstado() const;

    Jugador*                    getJugador()  const;
    const std::vector<Enemigo*>& getEnemigos() const;
    int                          getPuntaje()  const;
};

#endif
