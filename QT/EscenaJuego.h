#ifndef ESCENAJUEGO_H
#define ESCENAJUEGO_H

#include <QWidget>
#include <QTimer>
#include <QKeyEvent>
#include <QPainter>
#include <QPixmap>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QUrl>

// Inclusión de dependencias del núcleo del motor de juego
#include "GameManager.h"
#include "Nivel.h"
#include "NivelSelva.h"
#include "NivelBoss.h"
#include "Jugador.h"
#include "JefeFinal.h"
#include "Balon.h"
#include "Dardo.h"
#include "Dificultad.h"

class EscenaJuego : public QWidget
{
    Q_OBJECT

private:
    // =========================================================================
    // INSTANCIAS DEL MOTOR Y CONTROL DE ENTIDADES
    // =========================================================================
    GameManager* gm;
    Jugador*     jugadorActual;
    NivelBoss*   bossActual;
    QTimer*      timer;

    // =========================================================================
    // MÁQUINA DE ESTADOS Y CONTROL DE FLUJO
    // =========================================================================
    bool menuActivo;
    bool musicaIniciada;
    bool sonidoVictoriaReproducido;
    bool gameOverReproducido;
    bool victoria;
    bool gameOver;
    bool nivelCompletado;
    int  dificultadSeleccionada;

    // =========================================================================
    // SISTEMA DE INPUT (TECLADO)
    // =========================================================================
    bool teclaIzq;
    bool teclaDer;
    bool teclaArriba;
    bool teclaAbajo;
    bool teclaEspacio;
    bool espacioAnterior;

    // =========================================================================
    // CONTADORES DE ANIMACIÓN (CICLOS HORIZONTALES)
    // =========================================================================
    int frameActual;
    int ticksFrame;
    int frameBoar;
    int ticksBoar;
    int frameBoss;
    int ticksBoss;

    // =========================================================================
    // VARIABLES DE CÁMARA, EFECTOS VISUALES Y MÉTRICAS DE ESCENA
    // =========================================================================
    float camaraX;
    int   alphaTransicion;
    bool  transicionOscureciendo;
    int   ticksParpadeo;
    int   tiempoPartida;
    int   puntajeFinal;

    // =========================================================================
    // CANALES DE TEXTURAS Y HOJAS DE SPRITES (SPRITESHEETS)
    // =========================================================================
    // ── Jugador ──────────────────────────────────────────────
    QPixmap shQuiet;   // spritejugador0: quieto   — 4 frames 637x416  ← NUEVO
    QPixmap shIdle;    // spritejugador1: idle     — 4 frames 636x416
    QPixmap shRun1;    // spritejugador2: correr1  — 7 frames 363x416
    QPixmap shRun2;    // spritejugador3: correr2  — 6 frames 344x512
    QPixmap shThrow;   // spritejugador4: lanzar   — 4 frames 448x592
    QPixmap shJump;    // spritejugador5: salto    — 4 frames 516x512
    QPixmap shCrouch;  // spritejugador6: agachado — 4 frames 516x512

    // ── Enemigos ─────────────────────────────────────────────
    QPixmap shBoar;
    QPixmap shBossSwingL;
    QPixmap shBossSwingR;
    QPixmap shBossFire;
    QPixmap shBossHit;

    // ── Proyectiles ───────────────────────────────────────────
    QPixmap shHud;
    QPixmap shDartH;
    QPixmap shDartA;
    QPixmap shArrow;
    QPixmap shBall;

    // ── Fondos ────────────────────────────────────────────────
    QPixmap bgNivel1;
    QPixmap bgNivel2;

    // =========================================================================
    // SUB-SISTEMA DE AUDIO MULTIMEDIA INDEPENDIENTE
    // =========================================================================
    QMediaPlayer* musica;
    QAudioOutput* audio;
    QMediaPlayer* sonidoGolpe;
    QAudioOutput* audioGolpe;
    QMediaPlayer* sonidoVictoria;
    QAudioOutput* audioVictoria;

    // =========================================================================
    // MÉTODOS PRIVADOS DE GESTIÓN Y RESOLUCIÓN DE ENLACES
    // =========================================================================
    Jugador*   obtenerJugadorActual();
    NivelBoss* obtenerNivelBossActual();

    void cargarSprites();
    void iniciarMusica();
    void reproducirGolpe();
    void reproducirVictoria();

    // Métodos de asistencia gráfica para transformaciones Pixel Art
    QPixmap frame(const QPixmap& sheet, int idx, int frameW, int frameH);
    QPixmap escalar(const QPixmap& src, int destW, int destH);

    // =========================================================================
    // PIPELINE DE RENDERIZADO (SUBSISTEMAS DE DIBUJO)
    // =========================================================================
    void dibujarMenu(QPainter& p);
    void dibujarNivel1(QPainter& p);
    void dibujarNivel2(QPainter& p);

    // Helper compartido: elige el QPixmap del jugador según estado/input
    QPixmap elegirSpriteJugador();                              // ← NUEVO

    void dibujarJugadorNivel1(QPainter& p, Jugador* jugador);
    void dibujarJugadorNivel2(QPainter& p, Jugador* jugador);

    void dibujarHUD(QPainter& p, Jugador* jugador, int tiempo, int puntaje);
    void dibujarBarraVida(QPainter& p, int x, int y, int vida, int vidaMax, int ancho);
    void dibujarBoss(QPainter& p, JefeFinal* jefe);
    void dibujarProyectiles(QPainter& p, NivelBoss* nivel);
    void dibujarTransicion(QPainter& p);
    void dibujarVictoria(QPainter& p);
    void dibujarGameOver(QPainter& p);

private slots:
    void tick();

protected:
    void paintEvent(QPaintEvent* event)    override;
    void keyPressEvent(QKeyEvent* event)   override;
    void keyReleaseEvent(QKeyEvent* event) override;

public:
    explicit EscenaJuego(QWidget* parent = nullptr);
    ~EscenaJuego();

    void reiniciarJuego();
    void setConfiguracion(const QString& nombre, int dificultad);
};

#endif // ESCENAJUEGO_H


   
  
