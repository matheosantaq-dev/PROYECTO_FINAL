#include "TemporizadorJuego.h"

TemporizadorJuego::TemporizadorJuego(int fps) : ticks(0), fps(fps) {}

void TemporizadorJuego::actualizar() { ticks++; }
void TemporizadorJuego::reiniciar()  { ticks = 0; }

int   TemporizadorJuego::getTicks()          const { return ticks; }
int   TemporizadorJuego::getTiempoSegundos() const { return ticks / fps; }
float TemporizadorJuego::getTiempoExacto()   const { return static_cast<float>(ticks) / fps; }
