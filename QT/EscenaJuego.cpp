#include "EscenaJuego.h"

#include <QPixmap>

EscenaJuego::EscenaJuego(QWidget* parent)
    : QGraphicsView(parent)
{
  
    escena = new QGraphicsScene(this);

    escena->setSceneRect(0, 0, 1200, 800);

    setScene(escena);

   
    nivel = new NivelBoss();

   
    setBackgroundBrush(
        QBrush(
            QPixmap("fondodelbossagregarsprite")
        )
    );


    spriteJugador =
        escena->addPixmap(
            QPixmap("agregarspritedeljugador")
        );

    spriteJugador->setPos(
        nivel->getJugador()->getX(),
        nivel->getJugador()->getY()
    );


    spriteBoss =
        escena->addPixmap(
            QPixmap("spritedelbossqagregaraqwui")
        );

    spriteBoss->setPos(
        nivel->getJefe()->getX(),
        nivel->getJefe()->getY()
    );

    // Timer principal
    timer = new QTimer(this);

    connect(timer,
            &QTimer::timeout,
            this,
            &EscenaJuego::actualizarJuego);

    timer->start(16);
}

void EscenaJuego::actualizarJuego()
{
   
    nivel->actualizar();

   
    spriteJugador->setPos(
        nivel->getJugador()->getX(),
        nivel->getJugador()->getY()
    );

    spriteBoss->setPos(
        nivel->getJefe()->getX(),
        nivel->getJefe()->getY()
    );
}

void EscenaJuego::keyPressEvent(QKeyEvent* event)
{
    if(event->key() == Qt::Key_A)
    {
        nivel->getJugador()->moverIzquierda();
    }

    if(event->key() == Qt::Key_D)
    {
        nivel->getJugador()->moverDerecha();
    }

    if(event->key() == Qt::Key_Space)
    {
        nivel->lanzarBalon();
    }
}
