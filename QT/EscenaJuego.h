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
    
    // INSTANCIAS DEL MOTOR Y CONTROL DE ENTIDADES
  
    Jugador* jugadorActual;
    NivelBoss* bossActual;
    QTimer* timer; 

    // MÁQUINA DE ESTADOS Y CONTROL DE FLUJO
 
    bool menuActivo;
    bool musicaIniciada;
    bool sonidoVictoriaReproducido;
    bool gameOverReproducido;
    bool victoria;
    bool gameOver;
    bool nivelCompletado; 
    int dificultadSeleccionada;

   
    // SISTEMA DE INPUT (TECLADO)

    bool teclaIzq;
    bool teclaDer;
    bool teclaArriba;
    bool teclaAbajo;
    bool teclaEspacio;
    bool espacioAnterior;

    // CONTADORES DE ANIMACIÓN (CICLOS HORIZONTALES)

    int frameActual;
    int ticksFrame;
    int frameBoar;
    int ticksBoar;
    int frameBoss;
    int ticksBoss;


    // VARIABLES DE CÁMARA, EFECTOS VISUALES Y MÉTRICAS DE ESCENA
  
    int alphaTransicion;
    bool transicionOscureciendo;
    int ticksParpadeo;
    int tiempoPartida;
    int puntajeFinal;

 
    // CANALES DE TEXTURAS Y HOJAS DE SPRITES (SPRITESHEETS)

    QPixmap shIdle;
    QPixmap shRun1;
    QPixmap shRun2;
    QPixmap shThrow;
    QPixmap shJump;
    QPixmap shCrouch;
    QPixmap shBoar;
    QPixmap shBossSwingL;
    QPixmap shBossSwingR;
    QPixmap shBossFire;
    QPixmap shBossHit;
    QPixmap shHud;
    QPixmap shDartH;
    QPixmap shDartA;
    QPixmap shArrow;
    QPixmap shBall;
    QPixmap bgNivel1;
    QPixmap bgNivel2;


    // SUB-SISTEMA DE AUDIO MULTIMEDIA INDEPENDIENTE
   
    QMediaPlayer* musica;
    QAudioOutput* audio;
    QMediaPlayer* sonidoGolpe;
    QAudioOutput* audioGolpe;
    QMediaPlayer* sonidoVictoria;
    QAudioOutput* audioVictoria;

    // MÉTODOS PRIVADOS DE GESTIÓN Y RESOLUCIÓN DE ENLACES

    Jugador* obtenerJugadorActual();
    NivelBoss* obtenerNivelBossActual();

    void cargarSprites();
    void iniciarMusica();
    void reproducirGolpe();
    void reproducirVictoria();

 
    QPixmap frame(const QPixmap& sheet, int idx, int frameW, int frameH);
    QPixmap escalar(const QPixmap& src, int destW, int destH); 


    // PIPELINE DE RENDERIZADO (SUBSISTEMAS DE DIBUJO)

    void dibujarMenu(QPainter& p);
    void dibujarNivel1(QPainter& p);
    void dibujarNivel2(QPainter& p);
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
    void paintEvent(QPaintEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override;
    void keyReleaseEvent(QKeyEvent* event) override;

public:
    explicit EscenaJuego(QWidget* parent = nullptr);
    ~EscenaJuego();

    void reiniciarJuego();
    void setConfiguracion(const QString& nombre, int dificultad);
};

#endif /




   
  
