#include "ConfiguracionJuego.h"

ConfiguracionJuego::ConfiguracionJuego()
    : nombreJugador("Jugador"), dificultad(INTERMEDIO)
{}

void ConfiguracionJuego::setNombreJugador(const QString& nombre)
{
    nombreJugador = nombre;
}

void ConfiguracionJuego::setDificultad(Dificultad d)
{
    dificultad = d;
}

QString    ConfiguracionJuego::getNombreJugador() const { return nombreJugador; }
Dificultad ConfiguracionJuego::getDificultad()    const { return dificultad; }

int ConfiguracionJuego::getDificultadInt() const
{
    switch (dificultad)
    {
    case FACIL:      return 0;
    case INTERMEDIO: return 1;
    case DIFICIL:    return 2;
    default:         return 1;
    }
}
