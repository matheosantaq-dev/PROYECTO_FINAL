#include "EscenaJuego.h"
#include <QDebug>

EscenaJuego::EscenaJuego(QWidget* parent)
    : QWidget(parent)
{
    setFixedSize(1280, 720);
    setWindowTitle("Jumanji Rugby");

    jugadorActual = nullptr;
    bossActual = nullptr;
    menuActivo = true;
    musicaIniciada = false;
    sonidoVictoriaReproducido = false;
    gameOverReproducido = false;
    victoria = false;
    gameOver = false;
    nivelCompletado = false;
    dificultadSeleccionada = 1;
    tiempoPartida = 0;
    puntajeFinal = 0;
    teclaIzq = false;
    teclaDer = false;
    teclaArriba = false;
    teclaAbajo = false;
    teclaEspacio = false;
    espacioAnterior = false;
    frameActual = 0;
    frameBoar = 0;
    frameBoss = 0;
    ticksFrame = 0;
    ticksBoar = 0;
    ticksBoss = 0;
    camaraX = 0;

    alphaTransicion = 0;
    transicionOscureciendo = true;
    ticksParpadeo = 0;

    gm = new GameManager();
    gm->iniciarJuego();

    musica = new QMediaPlayer(this);
    audio = new QAudioOutput(this);
    musica->setAudioOutput(audio);

    sonidoGolpe = new QMediaPlayer(this);
    audioGolpe = new QAudioOutput(this);
    sonidoGolpe->setAudioOutput(audioGolpe);

    sonidoVictoria = new QMediaPlayer(this);
    audioVictoria = new QAudioOutput(this);
    sonidoVictoria->setAudioOutput(audioVictoria);

    cargarSprites();
    iniciarMusica();

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &EscenaJuego::tick);
    timer->start(16);

    setFocusPolicy(Qt::StrongFocus);
    setFocus();
}

EscenaJuego::~EscenaJuego()
{
    delete gm;
}

Jugador* EscenaJuego::obtenerJugadorActual()
{
    if (gm && gm->getNivelActual()) {
        return gm->getNivelActual()->getJugador();
    }
    return nullptr;
}

NivelBoss* EscenaJuego::obtenerNivelBossActual()
{
    if (gm && gm->getNivelActual() && gm->getNumeroNivel() == 2) {
        return dynamic_cast<NivelBoss*>(gm->getNivelActual());
    }
    return nullptr;
}

void EscenaJuego::cargarSprites()
{
    shIdle.load(":/new/Recursos/jugador/spritejugador1.png");
    shRun1.load(":/new/Recursos/jugador/spritejugador2.png");
    shRun2.load(":/new/Recursos/jugador/spritejugador3.png");
    shThrow.load(":/new/Recursos/jugador/spritejugador4.png");
    shJump.load(":/new/Recursos/jugador/spritejugador5.png");
    shCrouch.load(":/new/Recursos/jugador/spritejugador6.png");

    shBoar.load(":/new/Recursos/enemigos/enemigo1.png");
    shBossSwingL.load(":/new/Recursos/enemigos/enemigo2.png");
    shBossSwingR.load(":/new/Recursos/enemigos/enemigo3.png");
    shBossFire.load(":/new/Recursos/enemigos/enemigo4.png");
    shBossHit.load(":/new/Recursos/enemigos/enemigo5.png");

    shDartH.load(":/new/Recursos/proyectil/proyectil1.png");
    shDartA.load(":/new/Recursos/proyectil/proyectil2.png");
    shArrow.load(":/new/Recursos/proyectil/proyectil3.png");
    shBall.load(":/new/Recursos/proyectil/proyectil4.png");
    shHud.load(":/new/Recursos/hud/hud.png");

    QPixmap bg1_raw(":/new/Recursos/fondos/fondo1.png");
    bgNivel1 = bg1_raw.scaled(4608, 720, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);

    QPixmap bg2_raw(":/new/Recursos/fondos/fondo2.png");
    bgNivel2 = bg2_raw.scaled(1280, 720, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
}

void EscenaJuego::iniciarMusica()
{
    audio->setVolume(0.4f);
    musica->setSource(QUrl("qrc:/new/Recursos/musica/jumaji.mp3"));
    musica->setLoops(QMediaPlayer::Infinite);
    musica->play();
    musicaIniciada = true;
}

void EscenaJuego::reproducirGolpe()
{
    sonidoGolpe->setSource(QUrl("qrc:/new/Recursos/musica/golpe.mp3"));
    audioGolpe->setVolume(0.5f);
    sonidoGolpe->play();
}

void EscenaJuego::reproducirVictoria()
{
    if (!sonidoVictoriaReproducido) {
        musica->stop();
        sonidoVictoria->setSource(QUrl("qrc:/new/Recursos/musica/victoria.mp3"));
        audioVictoria->setVolume(0.6f);
        sonidoVictoria->play();
        sonidoVictoriaReproducido = true;
    }
}

QPixmap EscenaJuego::frame(const QPixmap& sheet, int idx, int frameW, int frameH)
{
    if (sheet.isNull()) return QPixmap(frameW, frameH);
    int posX = idx * frameW;
    if (posX + frameW > sheet.width()) posX = 0;
    return sheet.copy(posX, 0, frameW, frameH);
}

QPixmap EscenaJuego::escalar(const QPixmap& src, int destW, int destH)
{
    return src.scaled(destW, destH, Qt::IgnoreAspectRatio, Qt::FastTransformation);
}

void EscenaJuego::reiniciarJuego()
{
    if (gm) {
        delete gm;
        gm = new GameManager();
        gm->iniciarJuego();
    }
    jugadorActual = nullptr;
    bossActual = nullptr;
    menuActivo = true;
    musicaIniciada = false;
    sonidoVictoriaReproducido = false;
    gameOverReproducido = false;
    victoria = false;
    gameOver = false;
    nivelCompletado = false;
    dificultadSeleccionada = 1;
    tiempoPartida = 0;
    puntajeFinal = 0;
    teclaIzq = false;
    teclaDer = false;
    teclaArriba = false;
    teclaAbajo = false;
    teclaEspacio = false;
    espacioAnterior = false;
    frameActual = 0;
    frameBoar = 0;
    frameBoss = 0;
    ticksFrame = 0;
    ticksBoar = 0;
    ticksBoss = 0;
    camaraX = 0;

    iniciarMusica();
    update();
}

void EscenaJuego::setConfiguracion(const QString& nombre, int dificultad)
{
    dificultadSeleccionada = dificultad;
    if (gm) {
        gm->setNombreJugador(nombre);
        if (dificultad == 0)      gm->setDificultad(Dificultad::FACIL);
        else if (dificultad == 1) gm->setDificultad(Dificultad::INTERMEDIO);
        else if (dificultad == 2) gm->setDificultad(Dificultad::DIFICIL);
    }
}

void EscenaJuego::tick()
{
    if (menuActivo) return;

    jugadorActual = obtenerJugadorActual();
    bossActual = obtenerNivelBossActual();

    if (jugadorActual) {
        if (teclaIzq)    jugadorActual->moverIzquierda();
        if (teclaDer)    jugadorActual->moverDerecha();
        if (teclaArriba) jugadorActual->saltar();

        if (teclaAbajo)  jugadorActual->agacharse();
        else             jugadorActual->levantarse();

        if (teclaEspacio && !espacioAnterior) {
            if (gm && gm->getNivelActual()) {
                gm->getNivelActual()->lanzarBalon();
            }
            reproducirGolpe();
        }
    }
    espacioAnterior = teclaEspacio;

    if (gm) {
        gm->actualizar();
    }

    if (gm) {
        if (gm->getNumeroNivel() == 1) {
            if (gm->getNivelActual() && gm->getNivelActual()->getEstado() == EstadoNivel::TRANSICION) {
                nivelCompletado = true;
            }
        } else if (gm->getNumeroNivel() == 2) {
            nivelCompletado = false;
        }
    }

    if (jugadorActual && jugadorActual->getVida() <= 0) {
        gameOver = true;
    }

    ticksFrame++;
    if (ticksFrame >= 6) {
        ticksFrame = 0;
        frameActual = (frameActual + 1) % 7;
    }

    ticksBoar++;
    if (ticksBoar >= 5) {
        ticksBoar = 0;
        frameBoar = (frameBoar + 1) % 4;
    }

    if (bossActual) {
        ticksBoss++;
        if (ticksBoss >= 7) {
            ticksBoss = 0;
            frameBoss = (frameBoss + 1) % 4;
        }
        tiempoPartida = bossActual->getTiempoSegundos();

        JefeFinal* jefe = bossActual->getJefe();
        if (jefe && !jefe->estaVivo() && jugadorActual && jugadorActual->getVida() > 0) {
            victoria = true;
            puntajeFinal = jugadorActual->getPuntos();
        }
    }

    if (gm && jugadorActual && gm->getNumeroNivel() == 1) {
        camaraX = jugadorActual->getX() - 640;
        if (camaraX < 0)    camaraX = 0;
        if (camaraX > 3328) camaraX = 3328;
    } else {
        camaraX = 0;
    }

    update();
}

void EscenaJuego::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, false);

    if (menuActivo) {
        dibujarMenu(painter);
        return;
    }
    if (victoria) {
        dibujarVictoria(painter);
        return;
    }
    if (gameOver) {
        dibujarGameOver(painter);
        return;
    }
    if (nivelCompletado) {
        dibujarTransicion(painter);
        return;
    }

    if (gm) {
        if (gm->getNumeroNivel() == 1)      dibujarNivel1(painter);
        else if (gm->getNumeroNivel() == 2) dibujarNivel2(painter);
    }
}

void EscenaJuego::dibujarMenu(QPainter& p)
{
    p.fillRect(rect(), QColor("#122b15"));
    p.setPen(QColor("#D4A326"));
    p.setFont(QFont("Courier", 32, QFont::Bold));
    p.drawText(rect(), Qt::AlignHCenter | Qt::AlignTop, "\n\nJUMANJI RUGBY");

    p.setFont(QFont("Courier", 14, QFont::Bold));
    p.setPen(QColor("#FFFFFF"));

    QString selector = QString("1 = FACIL %1\n"
                               "2 = INTERMEDIO %2\n"
                               "3 = DIFICIL %3\n\n"
                               "ENTER = INICIAR COMPATIBLE\n\n"
                               "[DEBUG MODES: F2 = SALTAR DIRECTO AL BOSS]")
                           .arg(dificultadSeleccionada == 0 ? "<=" : "")
                           .arg(dificultadSeleccionada == 1 ? "<=" : "")
                           .arg(dificultadSeleccionada == 2 ? "<=" : "");

    p.drawText(rect(), Qt::AlignCenter, selector);
}

void EscenaJuego::dibujarNivel1(QPainter& p)
{
    p.drawPixmap(0, 0, bgNivel1, static_cast<int>(camaraX), 0, 1280, 720);


    if (jugadorActual) {
        dibujarJugadorNivel1(p, jugadorActual);
        dibujarHUD(p, jugadorActual, 0, jugadorActual->getPuntos());
    }

    if (gm && gm->getNivelActual()) {
        auto enemigosSelva = gm->getNivelActual()->getEnemigos();
        for (auto* enemigo : enemigosSelva)
        {
            if (enemigo && enemigo->estaVivo())
            {
                p.drawPixmap(
                    static_cast<int>(enemigo->getX()) - static_cast<int>(camaraX),
                    static_cast<int>(enemigo->getY()),
                    escalar(frame(shBoar, frameBoar, 64, 64), 64, 64));
                );
                // ===== BARRA DE VIDA =====

                int xBarra =
                    static_cast<int>(enemigo->getX()) -
                    static_cast<int>(camaraX);

                int yBarra =
                    static_cast<int>(enemigo->getY()) - 12;


                p.fillRect(
                    xBarra,
                    yBarra,
                    50,
                    6,
                    Qt::red
                );

                // Vida actual
                p.fillRect(
                    xBarra,
                    yBarra,
                    enemigo->getVida(),
                    6,
                    Qt::green
                );
            }
        }
    }
}


void EscenaJuego::dibujarNivel2(QPainter& p)
{
    p.drawPixmap(0, 0, bgNivel2);

    if (jugadorActual) {
        dibujarJugadorNivel2(p, jugadorActual);
    }

    if (bossActual) {
        JefeFinal* jefe = bossActual->getJefe();
        if (jefe) {
            dibujarBoss(p, jefe);
        }
        dibujarProyectiles(p, bossActual);

        if (bossActual->getModoFuria()) {
            p.setPen(QColor("#FF1111"));
            p.setFont(QFont("Courier", 14, QFont::Bold));
            p.drawText(580, 40, "¡MODO FURIA!");
        }
    }

    if (jugadorActual) {
        dibujarHUD(p, jugadorActual, tiempoPartida, jugadorActual->getPuntos());
    }
}

void EscenaJuego::dibujarJugadorNivel1(QPainter& p, Jugador* jugador)
{
    if (!jugador) return;
    QPixmap sprite;

    if (jugador->getSaltando())      sprite = shJump;
    else if (jugador->getAgachado()) sprite = shCrouch;
    else if (teclaIzq || teclaDer)
    {
        sprite = frame(
            shRun1,
            frameActual,
            292,
            334
            );
    }
    else if (teclaEspacio)           sprite = shThrow;
    else                             sprite = shIdle;

    if (!jugador->estaMirandoDerecha()) {
        sprite = sprite.transformed(QTransform().scale(-1, 1));
    }
    
    p.drawPixmap(
        static_cast<int>(jugador->getX()) -
        static_cast<int>(camaraX) - 16,
        
        static_cast<int>(jugador->getY()) - 32,
        escalar(sprite, 96, 96));
}

void EscenaJuego::dibujarJugadorNivel2(QPainter& p, Jugador* jugador)
{
    if (!jugador) return;
    QPixmap sprite;

    if (jugador->getSaltando())      sprite = shJump;
    else if (jugador->getAgachado()) sprite = shCrouch;
    else if (teclaIzq || teclaDer)   sprite = (frameActual % 2 == 0) ? shRun1 : shRun2;
    else if (teclaEspacio)           sprite = shThrow;
    else                             sprite = shIdle;

    if (!jugador->estaMirandoDerecha()) {
        sprite = sprite.transformed(QTransform().scale(-1, 1));
    }

    p.drawPixmap(static_cast<int>(jugador->getX()) - 16,
                 static_cast<int>(jugador->getY()) - 32,
                 escalar(sprite, 96, 96));
}

void EscenaJuego::dibujarBoss(QPainter& p, JefeFinal* jefe)
{
    if (!jefe || !jefe->estaVivo()) return;
    QPixmap spriteBoss = (jefe->getFase() == 2) ? shBossHit : shBossSwingL;

    // Se dibuja fielmente con su nueva posición Y aérea elevada 
    p.drawPixmap(static_cast<int>(jefe->getX()),
                 static_cast<int>(jefe->getY()),
                 escalar(spriteBoss, 128, 128));

    int barraY = static_cast<int>(jefe->getY()) - 20;
    dibujarBarraVida(p, static_cast<int>(jefe->getX()), barraY, jefe->getVida(), jefe->getVidaMaxima(), 128);

    p.setPen(QColor("#FF3333"));
    p.setFont(QFont("Courier", 9, QFont::Bold));
    QString textoVida = QString("HP JEFE: %1 / %2").arg(jefe->getVida()).arg(jefe->getVidaMaxima());
    p.drawText(static_cast<int>(jefe->getX()), barraY - 8, textoVida);
}

void EscenaJuego::dibujarProyectiles(QPainter& p, NivelBoss* nivel)
{
    if (!nivel) return;

    auto dardosActuales = nivel->getDardos();
    for (auto* dardo : dardosActuales) {
        if (dardo) {
            p.drawPixmap(static_cast<int>(dardo->getX()), static_cast<int>(dardo->getY()), escalar(shDartH, 32, 16));
        }
    }

    auto balonesActuales = nivel->getBalones();
    for (auto* balon : balonesActuales) {
        if (balon) {
            p.drawPixmap(static_cast<int>(balon->getX()), static_cast<int>(balon->getY()), escalar(shBall, 24, 24));
        }
    }
}

void EscenaJuego::dibujarHUD(QPainter& p, Jugador* jugador, int tiempo, int puntaje)
{
    p.drawPixmap(10, 10, escalar(shHud, 240, 80));
    p.setPen(QColor("#FFFFFF"));
    p.setFont(QFont("Courier", 10, QFont::Bold));

    p.drawText(35, 32, QString("PUNTOS: %1").arg(puntaje));
    p.drawText(140, 32, QString("TIEMPO: %1s").arg(tiempo));
    if (gm) {
        p.drawText(35, 48, QString("NIVEL: %1").arg(gm->getNumeroNivel()));
    }

    dibujarBarraVida(p, 35, 62, jugador->getVida(), jugador->getVidaMaxima(), 120);

    p.setFont(QFont("Courier", 9, QFont::Bold));
    if (jugador->esFortachon()) {
        p.setPen(QColor("#FF3366"));
        p.drawText(260, 30, "FORTACHON");
    }
    if (jugador->esVeloz()) {
        p.setPen(QColor("#33FF66"));
        p.drawText(260, 48, "VELOZ");
    }
}

void EscenaJuego::dibujarBarraVida(QPainter& p, int x, int y, int vida, int vidaMax, int ancho)
{
    if (vida < 0) vida = 0;
    if (vidaMax <= 0) vidaMax = 100;
    int tamVerde = static_cast<int>((static_cast<float>(vida) / vidaMax) * ancho);

    p.fillRect(x, y, ancho, 8, QColor("#300505"));
    p.fillRect(x, y, tamVerde, 8, QColor("#22BB33"));
    p.setPen(QColor("#000000"));
    p.drawRect(x, y, ancho, 8);
}

void EscenaJuego::dibujarTransicion(QPainter& p)
{
    p.fillRect(rect(), QColor(0, 0, 0, 220));
    p.setPen(QColor("#D4A326"));
    p.setFont(QFont("Courier", 22, QFont::Bold));
    p.drawText(rect(), Qt::AlignCenter, "NIVEL COMPLETADO\n\nPREPARATE PARA EL JEFE FINAL");
}

void EscenaJuego::dibujarVictoria(QPainter& p)
{
    reproducirVictoria();
    p.fillRect(rect(), QColor("#051208"));
    p.setPen(QColor("#D4A326"));
    p.setFont(QFont("Courier", 32, QFont::Bold));
    p.drawText(rect(), Qt::AlignHCenter | Qt::AlignTop, "\n¡GANASTE!");

    p.setFont(QFont("Courier", 16, QFont::Bold));
    p.setPen(QColor("#FFFFFF"));
    p.drawText(rect(), Qt::AlignCenter, QString("HAS COMPLETADO EL DESAFIO DEL JUEGO\n\nPUNTAJE FINAL: %1").arg(puntajeFinal));
}

void EscenaJuego::dibujarGameOver(QPainter& p)
{
    p.fillRect(rect(), QColor("#200505"));
    p.setPen(QColor("#FF3333"));
    p.setFont(QFont("Courier", 36, QFont::Bold));
    p.drawText(rect(), Qt::AlignCenter, "GAME OVER\n\nEL JUGADOR SE QUEDÓ SIN ENERGÍA");
}

void EscenaJuego::keyPressEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_F2) {
        if (gm) {
            menuActivo = false;
            nivelCompletado = false;
            gm->cambiarNivel();
            jugadorActual = obtenerJugadorActual();
            bossActual = obtenerNivelBossActual();
        }
        update();
        return;
    }

    if (menuActivo) {
        if (event->key() == Qt::Key_1) dificultadSeleccionada = 0;
        if (event->key() == Qt::Key_2) dificultadSeleccionada = 1;
        if (event->key() == Qt::Key_3) dificultadSeleccionada = 2;
        if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter) {
            setConfiguracion("Aventurero", dificultadSeleccionada);
            if (gm) gm->iniciarJuego();
            menuActivo = false;
        }
        update();
        return;
    }

    if (event->key() == Qt::Key_A || event->key() == Qt::Key_Left)  teclaIzq = true;
    if (event->key() == Qt::Key_D || event->key() == Qt::Key_Right) teclaDer = true;
    if (event->key() == Qt::Key_W || event->key() == Qt::Key_Up)    teclaArriba = true;
    if (event->key() == Qt::Key_S || event->key() == Qt::Key_Down)  teclaAbajo = true;
    if (event->key() == Qt::Key_Space)                              teclaEspacio = true;
}

void EscenaJuego::keyReleaseEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_A || event->key() == Qt::Key_Left)  teclaIzq = false;
    if (event->key() == Qt::Key_D || event->key() == Qt::Key_Right) teclaDer = false;
    if (event->key() == Qt::Key_W || event->key() == Qt::Key_Up)    teclaArriba = false;
    if (event->key() == Qt::Key_S || event->key() == Qt::Key_Down)  teclaAbajo = false;
    if (event->key() == Qt::Key_Space)                              teclaEspacio = false;
}
