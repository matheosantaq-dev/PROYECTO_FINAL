

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

    bool mirandoDerecha;

    float gravedad;

    float fuerzaSalto;

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

    void recibirDanio(int danio);

    bool estaVivo() const;

    int getVida() const;

    bool getSaltando() const;

    bool getAgachado() const;

    bool getTieneBalon() const;

    bool estaMirandoDerecha() const;

    void setTieneBalon(bool valor);
};

#endif
