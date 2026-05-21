#ifndef ESCENAJUEGO_H
#define ESCENAJUEGO_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QTimer>
#include <QKeyEvent>

#include "NivelBoss.h"

class EscenaJuego : public QGraphicsView
{
    Q_OBJECT

private:

    QGraphicsScene* escena;

    NivelBoss* nivel;

    QTimer* timer;

    QGraphicsPixmapItem* spriteJugador;

    QGraphicsPixmapItem* spriteBoss;

public:

    EscenaJuego(QWidget* parent = nullptr);

    void actualizarJuego();

protected:

    void keyPressEvent(QKeyEvent* event) override;
};

#endif
