

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

#include "GameManager.h"

class EscenaJuego : public QGraphicsView
{
    Q_OBJECT

private:

    QGraphicsScene* escena;

    GameManager* gameManager;

    Nivel* nivelActual;

    QTimer* timer;

    QGraphicsPixmapItem* spriteJugador;

    QGraphicsPixmapItem* spriteBoss;

    QGraphicsTextItem* textoVida;

    QGraphicsTextItem* textoPuntos;

    QGraphicsTextItem* textoTiempo;

    QGraphicsRectItem* barraVidaFondo;

    QGraphicsRectItem* barraVida;

    QMediaPlayer* musica;

    QAudioOutput* audio;

    QPixmap spriteSheetJugador;

    int frameJugador;

public:

    EscenaJuego(QWidget* parent = nullptr);

    ~EscenaJuego();

    void actualizarJuego();

protected:

    void keyPressEvent(
        QKeyEvent* event
    ) override;

    void keyReleaseEvent(
        QKeyEvent* event
    ) override;
};

#endif
