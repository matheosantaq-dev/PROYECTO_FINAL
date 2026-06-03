

#ifndef JUGADOR_H
#define JUGADOR_H

#include "Entidad.h"

// Caracteristica 1: Modo FORTACHON — activa mas daño en patada/lanzamiento (300 ticks)
// Caracteristica 2: Modo VELOZ    — incrementa velocidad maxima horizontal (180 ticks)
class Jugador : public Entidad
{
private:
    int vida;
    int vidaMaxima;

    bool saltando;
    bool agachado;
    bool tieneBalon;
    bool mirandoDerecha;

    // Fisicas parametricas (Fisica 1: gravedad + friccion)
    float gravedad;
    float fuerzaSalto;
    float velocidadMaxH;
    float friccion;
    float yPiso;           
    // Caracteristica 1: FORTACHON
    bool  modoFortachon;
    int   ticksFortachon;

    // Caracteristica 2: VELOZ
    bool  modoVeloz;
    int   ticksVeloz;


    int puntos;

public:
    Jugador(float x, float y, float yPiso = 600.0f);

    void mover()     override;
    void actualizar() override;

    void moverIzquierda();
    void moverDerecha();
    void detener();
    void saltar();
    void agacharse();
    void levantarse();
    void recibirDanio(int danio);
    void curar(int cantidad);

    // Caracteristicas especiales
    void activarFortachon(int ticks = 300);
    void activarVeloz(int ticks = 180);
    void agregarPuntos(int cantidad);

    // Getters
    bool estaVivo()          const;
    int  getVida()           const;
    int  getVidaMaxima()     const;
    bool getSaltando()       const;
    bool getAgachado()       const;
    bool getTieneBalon()     const;
    bool estaMirandoDerecha() const;
    bool esFortachon()       const;
    bool esVeloz()           const;
    int  getPuntos()         const;

    void setTieneBalon(bool valor);
    void setYPiso(float y);
};

#endif
