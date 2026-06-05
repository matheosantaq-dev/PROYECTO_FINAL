#ifndef NIVELBOSS_H
#define NIVELBOSS_H

#include "Nivel.h"
#include "JefeFinal.h"
#include "Dardo.h"
#include "Balon.h"
#include "AgenteIA.h"
#include "TemporizadorJuego.h"
#include <stdexcept>
#include <cstdlib>

// Nivel 2: Combate contra el jefe en la arena de Jumanji.
// Vista fija. El jugador lanza balones hacia arriba para golpear al boss
// que oscila en una liana (fisica sinusoidal).
class NivelBoss : public Nivel
{
private:
    JefeFinal*           jefe;
    AgenteIA*            ia;
    TemporizadorJuego    temporizador;

    std::vector<Dardo*>  dardos;
    std::vector<Balon*>  balones;

    int  dificultad;
    bool modoFuria;
    int  ultimoTickAtaque;
    int  intervaloAtaque;     // ticks entre dardos (varia con dificultad)
    int  ticksInvulnerable;

    void limpiarProyectilesInactivos();
    void verificarColisiones();

public:
    NivelBoss(int dificultad = 1);
    ~NivelBoss();

    void actualizar()         override;
    void cargarNivel()        override;
    void lanzarBalon()        override;
    void lanzarDardo();

    JefeFinal*            getJefe()    const;
    std::vector<Dardo*>&  getDardos();
    std::vector<Balon*>&  getBalones();
    int                   getTiempoSegundos() const;
    bool                  getModoFuria()      const;
};

#endif
