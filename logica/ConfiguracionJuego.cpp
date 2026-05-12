#include "ConfiguracionJuego.h"

ConfiguracionJuego::ConfiguracionJuego()
{
    nombreJugador = "Jugador";

    dificultad = INTERMEDIO;
}

void ConfiguracionJuego::setNombreJugador(QString nombre)
{
    nombreJugador = nombre;
}

QString ConfiguracionJuego::getNombreJugador() const
{
    return nombreJugador;
}

void ConfiguracionJuego::setDificultad(Dificultad dificultad)
{
    this->dificultad = dificultad;
}

Dificultad ConfiguracionJuego::getDificultad() const
{
    return dificultad;
}
