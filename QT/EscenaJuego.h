

#ifndef ESCENAJUEGO_H
#define ESCENAJUEGO_H

#include <QGraphicsView>
#include <QGraphicsScene>

#include <QGraphicsPixmapItem>
#include <QGraphicsTextItem>
#include <QGraphicsRectItem>

#include <QTimer>
#include <QKeyEvent>

#include <QPixmap>

#include "GameManager.h"

class EscenaJuego : public QGraphicsView
{
    Q_OBJECT

private:


    // ESCENA


    QGraphicsScene* escena;


    // GAME MANAGER


    GameManager* gameManager;

    Nivel* nivelActual;

    std::vector<QGraphicsPixmapItem*> spritesBalones;

    std::vector<QGraphicsPixmapItem*> spritesDardos;
    // TIMER PRINCIPAL


    QTimer* timer;


    // SPRITES

    QGraphicsPixmapItem* spriteJugador;

    QGraphicsPixmapItem* spriteBoss;

    QPixmap spriteSheetProyectiles;

    // HUD


    QGraphicsTextItem* textoVida;

    QGraphicsTextItem* textoPuntos;

    QGraphicsTextItem* textoTiempo;

   
    // BARRA VIDA


    QGraphicsRectItem* barraVidaFondo;

    QGraphicsRectItem* barraVida;

  
    // SPRITESHEET JUGADOR
    

    QPixmap spriteSheetJugador;

    // Frame actual
    int frameJugador;

    // Tiempo animación
    int contadorAnimacion;

    // Dirección
    bool mirandoDerecha;

public:

    EscenaJuego(QWidget* parent = nullptr);

    ~EscenaJuego();

    void actualizarJuego();

    void actualizarAnimacionJugador();

protected:

    void keyPressEvent(
        QKeyEvent* event
        ) override;

    void keyReleaseEvent(
        QKeyEvent* event
        ) override;
};

#endif
