#include "EscenaJuego.h"

#include <QPixmap>
#include <QBrush>
#include <QString>

EscenaJuego::EscenaJuego(QWidget* parent)
    : QGraphicsView(parent)
{
    // Crear escena
    escena = new QGraphicsScene(this);

    escena->setSceneRect(0, 0, 1200, 800);

    setScene(escena);

    // Crear nivel
    nivel = new NivelBoss();

    // Fondo temporal
    setBackgroundBrush(
        QBrush(Qt::darkGreen)
    );

    // SPRITE JUGADOR


    spriteJugador =
        escena->addPixmap(
            QPixmap()
        );

    // Rectángulo temporal
    spriteJugador->setPixmap(
        QPixmap(80,80)
    );

    spriteJugador->setPos(
        nivel->getJugador()->getX(),
        nivel->getJugador()->getY()
    );


    // SPRITE BOSS


    spriteBoss =
        escena->addPixmap(
            QPixmap()
        );

    spriteBoss->setPixmap(
        QPixmap(120,120)
    );

    spriteBoss->setPos(
        nivel->getJefe()->getX(),
        nivel->getJefe()->getY()
    );

    // HUD


    textoVida =
        escena->addText("");

    textoVida->setDefaultTextColor(Qt::white);

    textoVida->setPos(20,20);


    textoPuntos =
        escena->addText("");

    textoPuntos->setDefaultTextColor(Qt::yellow);

    textoPuntos->setPos(20,60);


    textoTiempo =
        escena->addText("");

    textoTiempo->setDefaultTextColor(Qt::red);

    textoTiempo->setPos(20,100);


    // BARRA VIDA

    barraVidaFondo =
        escena->addRect(
            800,
            20,
            300,
            30
        );

    barraVidaFondo->setBrush(Qt::black);

    barraVida =
        escena->addRect(
            800,
            20,
            300,
            30
        );

    barraVida->setBrush(Qt::red);

    // TIMER


    timer = new QTimer(this);

    connect(timer,
            &QTimer::timeout,
            this,
            &EscenaJuego::actualizarJuego);

    timer->start(16);

    // FPS aprox 60
}

void EscenaJuego::actualizarJuego()
{
    // Actualizar lógica
    nivel->actualizar();

  
    // ACTUALIZAR POSICIONES


    spriteJugador->setPos(
        nivel->getJugador()->getX(),
        nivel->getJugador()->getY()
    );

    spriteBoss->setPos(
        nivel->getJefe()->getX(),
        nivel->getJefe()->getY()
    );


    // ACTUALIZAR HUD

    textoVida->setPlainText(
        "Vida Boss: "
        + QString::number(
            nivel->getJefe()->getVida()
        )
    );

    textoPuntos->setPlainText(
        "Puntos: "
        + QString::number(
            nivel->getPuntaje()
        )
    );

    textoTiempo->setPlainText(
        "Tiempo: "
        + QString::number(
            nivel->getTiempo()
        )
    );

    // ACTUALIZAR BARRA VIDA


    float vida =
        nivel->getJefe()->getVida();

    float ancho =
        (vida / 400.0) * 300;

    barraVida->setRect(
        800,
        20,
        ancho,
        30
    );


    // MODO FURIA VISUAL


    if(nivel->getTiempo() >= 30)
    {
        spriteBoss->setScale(1.5);

        barraVida->setBrush(
            Qt::darkRed
        );
    }
}

void EscenaJuego::keyPressEvent(QKeyEvent* event)
{

    // MOVIMIENTO


    if(event->key() == Qt::Key_A)
    {
        nivel->getJugador()->moverIzquierda();
    }

    if(event->key() == Qt::Key_D)
    {
        nivel->getJugador()->moverDerecha();
    }

    if(event->key() == Qt::Key_W)
    {
        nivel->getJugador()->saltar();
    }

  
    // ATAQUE


    if(event->key() == Qt::Key_Space)
    {
        nivel->lanzarBalon();
    }
}
