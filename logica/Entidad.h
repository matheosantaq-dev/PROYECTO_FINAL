#ifndef ENTIDAD_H
#define ENTIDAD_H

#include <stdexcept>

// Clase abstracta base para todas las entidades del juego.
// Implementa posicion, velocidad, hitbox y colision real.
class Entidad
{
protected:
    float x;
    float y;
    float velocidadX;
    float velocidadY;
    int ancho;
    int alto;

public:
    Entidad(float x, float y, int ancho = 64, int alto = 64);
    virtual ~Entidad();

    virtual void mover() = 0;
    virtual void actualizar() = 0;


    bool colisionaCon(const Entidad* otra) const;

    float getX() const;
    float getY() const;
    float getVelocidadX() const;
    float getVelocidadY() const;
    int getAncho() const;
    int getAlto() const;

    void setX(float x);
    void setY(float y);
    void setVelocidadX(float velocidad);
    void setVelocidadY(float velocidad);
    void setAncho(int ancho);
    void setAlto(int alto);
};

#endif
