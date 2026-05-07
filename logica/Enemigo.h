#ifndef ENEMIGO_H
#define ENEMIGO_H

#include "Entidad.h"

class Enemigo : public Entidad
{
protected:

    int vida;

    float velocidadMovimiento;

    bool vivo;

    bool moviendoDerecha;

public:

    Enemigo(float x, float y);

    virtual ~Enemigo();

    void mover() override;

    virtual void actualizar() override;

    void recibirDanio(int cantidad);

    bool estaVivo() const;

    int getVida() const;
};

#endif
