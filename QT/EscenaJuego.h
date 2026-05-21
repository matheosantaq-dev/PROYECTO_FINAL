#ifndef ESCENAJUEGO_H
#define ESCENAJUEGO_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QGraphicsTextItem>
#include <QGraphicsRectItem>

#include <QTimer>
#include <QKeyEvent>

#include <QMediaPlayer>
#include <QAudioOutput>

#include "NivelBoss.h"

class EscenaJuego : public QGraphicsView
{
    Q_OBJECT

private:

    // Escena principal
    QGraphicsScene* escena;

    // Nivel actual
    NivelBoss* nivel;

    // Timer del juego
    QTimer* timer;

    // Sprites
    QGraphicsPixmapItem* spriteJugador;

    QGraphicsPixmapItem* spriteBoss;

    // HUD
    QGraphicsTextItem* textoVida;

    QGraphicsTextItem* textoPuntos;

    QGraphicsTextItem* textoTiempo;

    // Barra de vida
    QGraphicsRectItem* barraVidaFondo;

    QGraphicsRectItem* barraVida;

    // Sonido
    QMediaPlayer* musica;

    QAudioOutput* audio;

    // Animaciones
    QPixmap spriteSheetJugador;

    int frameJugador;

public:

    EscenaJuego(QWidget* parent = nullptr);

    void actualizarJuego();

protected:

    void keyPressEvent(QKeyEvent* event) override;
};

#endif
