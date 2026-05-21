#ifndef PUNTAJEJUEGO_H
#define PUNTAJEJUEGO_H

class PuntajeJuego
{
private:

    int puntos;

public:

    PuntajeJuego();

    void agregarPuntos(int cantidad);

    int getPuntos() const;
};

#endif
