#ifndef CONFIGURACIONJUEGO_H
#define CONFIGURACIONJUEGO_H

#include <QString>
#include "Dificultad.h"

class ConfiguracionJuego
{
private:
    QString    nombreJugador;
    Dificultad dificultad;

public:
    ConfiguracionJuego();

    void       setNombreJugador(const QString& nombre);
    void       setDificultad(Dificultad dificultad);

    QString    getNombreJugador() const;
    Dificultad getDificultad()    const;
    int        getDificultadInt() const; 
};

#endif

