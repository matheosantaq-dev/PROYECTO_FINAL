#ifndef TEMPORIZADORJUEGO_H
#define TEMPORIZADORJUEGO_H


class TemporizadorJuego
{
private:
    int ticks;      
    int fps;         
public:
    TemporizadorJuego(int fps = 60);
    void actualizar();
    void reiniciar();

    int   getTicks()         const;
    int   getTiempoSegundos() const; 
    float getTiempoExacto()  const; 
};

#endif
