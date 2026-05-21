// =========================
// EscenaJuego.cpp
// =========================

#include "EscenaJuego.h"

#include <QPixmap>
#include <QBrush>
#include <QString>

EscenaJuego::EscenaJuego(QWidget* parent)
    : QGraphicsView(parent)
{
    escena = new QGraphicsScene(this);

    escena->setSceneRect(0,0,1200,800);

    setScene(escena);

    gameManager = new GameManager();

    gameManager->iniciarJuego();

    nivelActual =
        gameManager->getNivelActual();

    setBackgroundBrush(
        QBrush(Qt::darkGreen)
    );

    spriteJugador =
        escena->addPixmap(
            QPixmap(80,80)
        );

    spriteJugador->setPos(
        nivelActual->getJugador()->getX(),
        nivelActual->getJugador()->getY()
    );

    spriteBoss =
        escena->addPixmap(
            QPixmap(120,120)
        );

    spriteBoss->hide();

    textoVida =
        escena->addText("");

    textoVida->setDefaultTextColor(
        Qt::white
    );

    textoVida->setPos(20,20);

    textoPuntos =
        escena->addText("");

    textoPuntos->setDefaultTextColor(
        Qt::yellow
    );

    textoPuntos->setPos(20,60);

    textoTiempo =
        escena->addText("");

    textoTiempo->setDefaultTextColor(
        Qt::red
    );

    textoTiempo->setPos(20,100);

    barraVidaFondo =
        escena->addRect(
            800,
            20,
            300,
            30
        );

    barraVidaFondo->setBrush(
        Qt::black
    );

    barraVida =
        escena->addRect(
            800,
            20,
            300,
            30
        );

    barraVida->setBrush(
        Qt::red
    );

    barraVida->hide();

    barraVidaFondo->hide();

    timer = new QTimer(this);

    connect(timer,
            &QTimer::timeout,
            this,
            &EscenaJuego::actualizarJuego);

    timer->start(16);
}

EscenaJuego::~EscenaJuego()
{
    delete gameManager;
}

void EscenaJuego::actualizarJuego()
{
    gameManager->actualizar();

    nivelActual =
        gameManager->getNivelActual();

    if(gameManager->estaTerminado())
    {
        timer->stop();

        textoTiempo->setPlainText(
            "GANASTE"
        );

        return;
    }

    spriteJugador->setPos(
        nivelActual->getJugador()->getX(),
        nivelActual->getJugador()->getY()
    );

    NivelBoss* bossNivel =
        dynamic_cast<NivelBoss*>(
            nivelActual
        );

    if(bossNivel != nullptr)
    {
        spriteBoss->show();

        barraVida->show();

        barraVidaFondo->show();

        spriteBoss->setPos(
            bossNivel->getJefe()->getX(),
            bossNivel->getJefe()->getY()
        );

        textoVida->setPlainText(
            "Vida Boss: "
            + QString::number(
                bossNivel->getJefe()->getVida()
            )
        );

        textoPuntos->setPlainText(
            "Puntos: "
            + QString::number(
                bossNivel->getPuntaje()
            )
        );

        textoTiempo->setPlainText(
            "Tiempo: "
            + QString::number(
                bossNivel->getTiempo()
            )
        );

        float vida =
            bossNivel->getJefe()->getVida();

        float ancho =
            (vida / 400.0f) * 300;

        barraVida->setRect(
            800,
            20,
            ancho,
            30
        );

        if(bossNivel->getTiempo() >= 30)
        {
            spriteBoss->setScale(1.5);

            barraVida->setBrush(
                Qt::darkRed
            );
        }
    }
    else
    {
        spriteBoss->hide();

        barraVida->hide();

        barraVidaFondo->hide();
    }
}

void EscenaJuego::keyPressEvent(
        QKeyEvent* event)
{
    if(nivelActual == nullptr)
    {
        return;
    }

    if(event->key() == Qt::Key_A)
    {
        nivelActual->getJugador()
                ->moverIzquierda();
    }

    if(event->key() == Qt::Key_D)
    {
        nivelActual->getJugador()
                ->moverDerecha();
    }

    if(event->key() == Qt::Key_W)
    {
        nivelActual->getJugador()
                ->saltar();
    }

    if(event->key() == Qt::Key_Space)
    {
        nivelActual->lanzarBalon();
    }
}

void EscenaJuego::keyReleaseEvent(
        QKeyEvent* event)
{
    if(event->key() == Qt::Key_A
        || event->key() == Qt::Key_D)
    {
        nivelActual->getJugador()
                ->detener();
    }
}
