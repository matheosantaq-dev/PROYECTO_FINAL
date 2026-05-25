#ifndef NIVELSELVA_H
#define NIVELSELVA_H

#include "Nivel.h"

class NivelSelva : public Nivel
{
private:

    // Distancia recorrida
    int distanciaRecorrida;

    // Tiempo nivel
    int tiempoNivel;

    // Puntos
    int puntos;

    // Enemigos derrotados
    int enemigosDerrotados;

public:

    NivelSelva();

    void actualizar() override;

    void cargarNivel() override;

   
    // GETTERS
   

    int getDistancia() const;

    int getTiempo() const;

    int getPuntos() const;

    int getEnemigosDerrotados() const;
};

#endif
