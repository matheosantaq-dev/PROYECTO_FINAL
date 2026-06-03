#ifndef PROYECTIL_H
#define PROYECTIL_H

#include "Entidad.h"


class Proyectil : public Entidad
{
protected:
    int  danio;
    bool activo;

public:
    Proyectil(float x, float y, float velocidadX, float velocidadY, int danio = 10);
    virtual ~Proyectil();

    void mover() override;
    virtual void actualizar() override;

    bool estaActivo() const;
    void desactivar();
    int  getDanio() const;
};

#endif
