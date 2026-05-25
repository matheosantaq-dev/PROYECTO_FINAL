#include "EscenaJuego.h"

#include <QPixmap>
#include <QBrush>
#include <QString>
#include <QFont>

EscenaJuego::EscenaJuego(QWidget* parent)
    : QGraphicsView(parent)
{
    escena = new QGraphicsScene(this);

    escena->setSceneRect(
        0,
        0,
        1200,
        800
        );

    setScene(escena);

    gameManager = new GameManager();

    gameManager->iniciarJuego();

    nivelActual =
        gameManager->getNivelActual();

    frameJugador=0;

    contadorAnimacion=0;

    mirandoDerecha=true;

    // =====================
    // FONDO
    // =====================

    QPixmap fondo(
        ":/Recursos/fondos/fondo_selva.png"
        );

    fondo=
        fondo.scaled(
            1200,
            800,
            Qt::IgnoreAspectRatio,
            Qt::SmoothTransformation
            );

    setBackgroundBrush(
        QBrush(
            fondo
            )
        );

    // =====================
    // SPRITESHEET JUGADOR
    // =====================

    spriteSheetJugador=
        QPixmap(
            ":/Recursos/fondos/spray jugador (1).png"
            );

    QPixmap frameInicial=
        spriteSheetJugador.copy(
            70,
            500,
            180,
            220
            );

    spriteJugador=
        escena->addPixmap(
            frameInicial
            );

    spriteJugador->setScale(
        0.8
        );

    spriteJugador->setPos(
        nivelActual->getJugador()->getX()-70,
        nivelActual->getJugador()->getY()-170
        );

    // =====================
    // BOSS
    // =====================

    spriteBoss=
        escena->addPixmap(
            QPixmap(120,120)
            );

    spriteBoss->hide();


    // =====================
    // PROYECTILES
    // =====================

    spriteSheetProyectiles=
        QPixmap(
            ":/Recursos/fondos/PROYECTILES.png"
            );

    // BALON

    QPixmap frameBalon=
        spriteSheetProyectiles.copy(
            0,
            0,
            64,
            64
            );

    spriteBalon=
        escena->addPixmap(
            frameBalon
            );

    spriteBalon->hide();

    spriteBalon->setScale(
        1.0
        );

    // DARDO

    QPixmap frameDardo=
        spriteSheetProyectiles.copy(
            0,
            320,
            64,
            64
            );

    spriteDardo=
        escena->addPixmap(
            frameDardo
            );

    spriteDardo->hide();

    spriteDardo->setScale(
        1.0
        );

    // =====================
    // HUD
    // =====================

    QFont fuenteHUD;

    fuenteHUD.setPointSize(
        18
        );

    fuenteHUD.setBold(
        true
        );

    textoVida=
        escena->addText(
            "Vida:100"
            );

    textoVida->setFont(
        fuenteHUD
        );

    textoVida->setDefaultTextColor(
        Qt::white
        );

    textoVida->setPos(
        30,
        20
        );

    textoPuntos=
        escena->addText(
            "Nivel 1"
            );

    textoPuntos->setFont(
        fuenteHUD
        );

    textoPuntos->setDefaultTextColor(
        Qt::yellow
        );

    textoPuntos->setPos(
        30,
        60
        );

    textoTiempo=
        escena->addText(
            "WASD + SPACE"
            );

    textoTiempo->setFont(
        fuenteHUD
        );

    textoTiempo->setDefaultTextColor(
        Qt::red
        );

    textoTiempo->setPos(
        30,
        100
        );

    // =====================
    // VIDA BOSS
    // =====================

    barraVidaFondo=
        escena->addRect(
            800,
            20,
            300,
            30
            );

    barraVidaFondo->setBrush(
        Qt::black
        );

    barraVida=
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

    timer=
        new QTimer(
            this
            );

    connect(
        timer,
        &QTimer::timeout,
        this,
        &EscenaJuego::actualizarJuego
        );

    timer->start(
        16
        );
}

EscenaJuego::~EscenaJuego()
{
    delete gameManager;
}

void EscenaJuego::actualizarAnimacionJugador()
{
    QPixmap frame=
        spriteSheetJugador.copy(
            70,
            500,
            180,
            220
            );

    spriteJugador->setPixmap(
        frame
        );
}

void EscenaJuego::actualizarJuego()
{
    gameManager->actualizar();

    nivelActual=
        gameManager->getNivelActual();

    actualizarAnimacionJugador();

    spriteJugador->setPos(
        nivelActual->getJugador()->getX()-70,
        nivelActual->getJugador()->getY()-170
        );

    textoVida->setPlainText(
        "Vida: "
        +
        QString::number(
            nivelActual
                ->getJugador()
                ->getVida()
            )
        );

    NivelBoss* bossNivel=
        dynamic_cast<NivelBoss*>(
            nivelActual
            );

    if(bossNivel!=nullptr)
    {
        if(!bossNivel->getBalones().empty())
        {
            Balon* b=
                bossNivel->getBalones()[0];

            spriteBalon->show();

            spriteBalon->setPos(
                b->getX(),
                b->getY()
                );
        }

        else
        {
            spriteBalon->hide();
        }

        if(!bossNivel->getDardos().empty())
        {
            Dardo* d=
                bossNivel->getDardos()[0];

            spriteDardo->show();

            spriteDardo->setPos(
                d->getX(),
                d->getY()
                );
        }

        else
        {
            spriteDardo->hide();
        }

        spriteBoss->show();

        barraVida->show();

        barraVidaFondo->show();
    }

    else
    {
        spriteBoss->hide();

        barraVida->hide();

        barraVidaFondo->hide();
    }
}

void EscenaJuego::keyPressEvent(
    QKeyEvent* event
    )
{
    if(event->key()==Qt::Key_A)
    {
        nivelActual
            ->getJugador()
            ->moverIzquierda();
    }

    if(event->key()==Qt::Key_D)
    {
        nivelActual
            ->getJugador()
            ->moverDerecha();
    }

    if(event->key()==Qt::Key_W)
    {
        nivelActual
            ->getJugador()
            ->saltar();
    }

    if(event->key()==Qt::Key_Space)
    {
        nivelActual
            ->lanzarBalon();
    }
}

void EscenaJuego::keyReleaseEvent(
    QKeyEvent* event
    )
{
    if(
        event->key()==Qt::Key_A
        ||
        event->key()==Qt::Key_D
        )
    {
        nivelActual
            ->getJugador()
            ->detener();
    }
}
