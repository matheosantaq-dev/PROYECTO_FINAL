#ifndef NIVELBOSS_H
#define NIVELBOSS_H

#include "Nivel.h"
#include "Enemigo.h" 
#include <vector>
#include <cmath>

class Obstaculo : public Entidad
{
public:
    Obstaculo(float x, float y, int w, int h) : Entidad(x, y, w, h) {}
    void mover() override {}
    void actualizar() override {}
};

class NivelSelva : public Nivel
{
private:
    int distanciaRecorrida;
    int tiempoNivel;
    int enemigosDerrotados;
    float metaX;
    int ticksInvulnerable;

    std::vector<Obstaculo*> obstaculos;

public:
    NivelSelva();
    ~NivelSelva();


    void actualizar() override;
    void cargarNivel() override;
    void lanzarBalon() override;

   
    int getDistancia() const;
    int getTiempoSegundos() const;
    int getEnemigosDerrotados() const;
    float getProgresoMeta() const;

    const std::vector<Obstaculo*>& getObstaculos() const;
};

#endif
