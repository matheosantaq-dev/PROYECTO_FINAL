#ifndef TEMPORIZADORJUEGO_H
#define TEMPORIZADORJUEGO_H

class TemporizadorJuego
{
private:

    int tiempoActual;

public:

    TemporizadorJuego();

    void actualizar();

    int getTiempoActual() const;
};

#endif
