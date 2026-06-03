#ifndef ENEMIGO_H
#define ENEMIGO_H

#include "Entidad.h"

// Enemigo base: animal de la selva de Jumanji.
// Hereda de Entidad (herencia propia requerida).
class Enemigo : public Entidad
{
protected:
    int   vida;
    float velocidadMovimiento;
    bool  vivo;
    bool  moviendoDerecha;
    float limiteIzq;
    float limiteDer;

public:
    Enemigo(float x, float y,
            float limIzq = 0.0f,
            float limDer = 1150.0f);
    virtual ~Enemigo();

    void mover()     override;
    virtual void actualizar() override;

    void recibirDanio(int cantidad);

    bool estaVivo() const;
    int  getVida()  const;
};

#endif
