#ifndef ENTIDAD_H
#define ENTIDAD_H

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
    Entidad(float x, float y);

    virtual ~Entidad();

    virtual void mover() = 0;
    virtual void actualizar() = 0;

    float getX() const;
    float getY() const;

    void setX(float x);
    void setY(float y);
};

#endif
