#ifndef CONFIGURACIONJUEGO_H
#define CONFIGURACIONJUEGO_H

#include <QString>

#include "Dificultad.h"

class ConfiguracionJuego
{
private:

    QString nombreJugador;

    Dificultad dificultad;

public:

    ConfiguracionJuego();

    void setNombreJugador(QString nombre);

    QString getNombreJugador() const;

    void setDificultad(Dificultad dificultad);

    Dificultad getDificultad() const;
};

#endif
