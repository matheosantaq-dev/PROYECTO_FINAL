#ifndef JEFEFINAL_H
#define JEFEFINAL_H

#include "Enemigo.h"

class JefeFinal : public Enemigo
{
private:

    int fase;

    float velocidadAtaque;

    int tiempoAtaque;

public:

    JefeFinal(float x, float y);

    void actualizar() override;

    void cambiarFase();

    int getFase() const;

    int getTiempoAtaque() const;
};

#endif
