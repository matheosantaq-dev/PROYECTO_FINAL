#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "Nivel.h"
#include "NivelSelva.h"
#include "NivelBoss.h"

#include "ConfiguracionJuego.h"

class GameManager
{
private:

    Nivel* nivelActual;

    ConfiguracionJuego configuracion;

    int numeroNivel;

    bool juegoTerminado;

public:

    GameManager();

    ~GameManager();

    void iniciarJuego();

    void actualizar();

    void cambiarNivel();

    Nivel* getNivelActual() const;

    ConfiguracionJuego& getConfiguracion();

    bool estaTerminado() const;
};

#endif
