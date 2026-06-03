

#include "Jugador.h"
#include <stdexcept>
#include <algorithm>

Jugador::Jugador(float x, float y, float yPiso)
    : Entidad(x, y, 64, 64), 
    vida(100), vidaMaxima(100),
    saltando(false), agachado(false),
    tieneBalon(true), mirandoDerecha(true),
    gravedad(0.5f), fuerzaSalto(-13.0f),
    velocidadMaxH(5.0f), friccion(0.3f),
    yPiso(yPiso),
    modoFortachon(false), ticksFortachon(0),
    modoVeloz(false), ticksVeloz(0),
    puntos(0)
{}

void Jugador::mover()
{
    
    // MODELO CINEMÁTICO INTEGRADO (Simulación de Movimiento Continuo)
    // Coordenadas actualizadas por adición vectorial discreta
   
    x += velocidadX;
    y += velocidadY;

    
    // En NivelBoss yPiso es 680.0f. El límite derecho es: 1280 (Ventana) - 48 (Jugador) = 1232
    float limiteDerechoX = (yPiso >= 680.0f) ? 1232.0f : 4544.0f;

    if (x > limiteDerechoX) x = limiteDerechoX;
    if (x < 0)              x = 0;

    // Comprobación de colisión con el plano de tierra del escenario
    if (y >= yPiso)
    {
        y = yPiso;
        velocidadY = 0;
        saltando = false;
    }
}

void Jugador::actualizar()
{
    // ── RÚBRICA FÍSICA 1: Gravedad (Aceleración vertical uniforme) ───────────
    velocidadY += gravedad;
    if (velocidadY > 20.0f) velocidadY = 20.0f; // Velocidad terminal límite

    // ── RÚBRICA FÍSICA 3: Fricción horizontal (Desaceleración lineal) ───────
    if (velocidadX > 0)
    {
        velocidadX -= friccion;
        if (velocidadX < 0) velocidadX = 0;
    }
    else if (velocidadX < 0)
    {
        velocidadX += friccion;
        if (velocidadX > 0) velocidadX = 0;
    }

    mover();

    // Redimensión dinámica de la Hitbox estructural para agacharse bajo dardos
    if (agachado) alto = 48;
    else          alto = 80;

    // Manejadores internos de enfriamiento de habilidades
    if (modoFortachon)
    {
        --ticksFortachon;
        if (ticksFortachon <= 0)
            modoFortachon = false;
    }

    if (modoVeloz)
    {
        --ticksVeloz;
        if (ticksVeloz <= 0)
        {
            modoVeloz = false;
            velocidadMaxH = 5.0f;
        }
    }
}

void Jugador::moverIzquierda()
{
    mirandoDerecha = false;
    float vMax = modoVeloz ? 9.0f : velocidadMaxH;
    velocidadX -= 1.5f;
    if (velocidadX < -vMax) velocidadX = -vMax;
}

void Jugador::moverDerecha()
{
    mirandoDerecha = true;
    float vMax = modoVeloz ? 9.0f : velocidadMaxH;
    velocidadX += 1.5f;
    if (velocidadX > vMax) velocidadX = vMax;
}

void Jugador::detener()
{
    velocidadX = 0;
}

void Jugador::saltar()
{
    if (!saltando)
    {
        velocidadY = fuerzaSalto; 
        saltando = true;
    }
}

void Jugador::agacharse()  { agachado = true; }
void Jugador::levantarse() { agachado = false; }

void Jugador::recibirDanio(int danio)
{
    if (danio < 0)
        throw std::invalid_argument("recibirDanio: El value no puede ser negativo");
    vida -= danio;
    if (vida < 0) vida = 0;
}

void Jugador::curar(int cantidad)
{
    vida += cantidad;
    if (vida > vidaMaxima) vida = vidaMaxima;
}

void Jugador::activarFortachon(int ticks)
{
    modoFortachon = true;
    ticksFortachon = ticks;
}

void Jugador::activarVeloz(int ticks)
{
    modoVeloz = true;
    ticksVeloz = ticks;
    velocidadMaxH = 9.0f; 
}

void Jugador::agregarPuntos(int cantidad)
{
    puntos += cantidad;
}

bool Jugador::estaVivo()           const { return vida > 0; }
int  Jugador::getVida()            const { return vida; }
int  Jugador::getVidaMaxima()      const { return vidaMaxima; }
bool Jugador::getSaltando()        const { return saltando; }
bool Jugador::getAgachado()        const { return agachado; }
bool Jugador::getTieneBalon()      const { return tieneBalon; }
bool Jugador::estaMirandoDerecha() const { return mirandoDerecha; }
bool Jugador::esFortachon()        const { return modoFortachon; }
bool Jugador::esVeloz()            const { return modoVeloz; }
int  Jugador::getPuntos()          const { return puntos; }
void Jugador::setTieneBalon(bool v)      { tieneBalon = v; }
void Jugador::setYPiso(float y)          { this->yPiso = y; }
