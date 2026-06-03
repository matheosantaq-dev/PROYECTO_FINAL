#ifndef PUNTAJEJUEGO_H
#define PUNTAJEJUEGO_H


class PuntajeJuego
{
private:
    int puntos;
    int puntosNivelAnterior; 

public:
    PuntajeJuego();
    void agregarPuntos(int cantidad);
    void guardarNivel();      
    int  getPuntos()      const;
    int  getPuntosTotal() const;
};

#endif
