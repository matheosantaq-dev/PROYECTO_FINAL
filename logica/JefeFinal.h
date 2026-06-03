#ifndef JEFEFINAL_H
#define JEFEFINAL_H

#include "Enemigo.h"
#include <cmath>

class JefeFinal : public Enemigo {
private:
    int vida;
    int vidaMaxima; 
    int fase;
    int tiempoAtaque;
    float xCentro;
    float amplitud;
    float omega;
    int ticksGlobales;

public:
    JefeFinal(float x, float y);

    void actualizar() override;
    void cambiarFase();


    int getVida() const { return vida; }
    int getVidaMaxima() const { return vidaMaxima; }
    int getFase() const { return fase; }
    int getTiempoAtaque() const { return tiempoAtaque; }
    float getXCentro() const { return xCentro; }

    void setVida(int v);
    void setDificultad(int dif);
};

#endif 
