#ifndef JUGADOR_H
#define JUGADOR_H

#include "Entidad.h"

class Jugador : public Entidad
{
private:

    int vida;

    bool saltando;
    bool agachado;

    bool tieneBalon;

public:

    Jugador(float x, float y);

    void mover() override;
    void actualizar() override;

    void moverIzquierda();
    void moverDerecha();

    void detener();

    void saltar();

    void agacharse();
    void levantarse();

    int getVida() const;

    bool getTieneBalon() const;
    void setTieneBalon(bool valor);
};

#endif
