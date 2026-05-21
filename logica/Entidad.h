#ifndef ENTIDAD_H
#define ENTIDAD_H

class Entidad
{
protected:

    // Posición
    float x;
    float y;

    // Velocidad
    float velocidadX;
    float velocidadY;

    // Tamaño hitbox
    int ancho;
    int alto;

public:

    Entidad(float x, float y);

    virtual ~Entidad();


    virtual void mover() = 0;

    virtual void actualizar() = 0;

    
   

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
