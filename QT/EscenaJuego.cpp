#include "EscenaJuego.h"
#include <QDebug>

// ============================================================
//  CONSTANTES DE FRAMES POR SPRITESHEET
//  (ancho_total / número_de_columnas = frameW)
// ============================================================
//  spritejugador1 (idle)   : 2544x416  → 4 frames  de 636x416
//  spritejugador2 (run1)   : 2544x416  → 7 frames  de 363x416  (usa 7 para run)
//  spritejugador3 (run2)   : 2064x512  → 6 frames  de 344x512
//  spritejugador4 (throw)  : 1792x592  → 4 frames  de 448x592
//  spritejugador5 (jump)   : 2064x512  → 4 frames  de 516x512
//  spritejugador6 (crouch) : 2064x512  → 4 frames  de 516x512
//  enemigo1 (boar)         : 2064x512  → 4 frames  de 516x512
//  enemigo2 (bossSwingL)   : 2544x416  → 5 frames  de 508x416
//  enemigo3 (bossSwingR)   : 2544x416  → 5 frames  de 508x416
//  enemigo4 (bossFire)     : 2064x512  → 4 frames  de 516x512
//  enemigo5 (bossHit)      : 1792x592  → 4 frames  de 448x592
//  hud                     : 2064x512  → 4 iconos  de 516x512
//    icono 0=corazón  1=balón  2=reloj  3=rayo

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
    // Define el color exacto que rodea a las figuras para volverlo invisible
    QColor colorFondoARemover = Qt::white; 

    // Función lambda auxiliar para cargar la imagen y aplicar la máscara transparente
    auto cargarTransparente = [colorFondoARemover](QPixmap& pixmap, const QString& ruta) {
        if (pixmap.load(ruta)) {
            QBitmap mascara = pixmap.createMaskFromColor(colorFondoARemover, Qt::MaskInvertAlpha);
            pixmap.setMask(mascara);
        } else {
            qDebug() << "Error crítico: No se pudo cargar el archivo en la ruta:" << ruta;
        }
    };

    // ── 1. CANAL JUGADOR (Remoción de fondo sin alterar la figura) ──
    cargarTransparente(shIdle,   ":/new/Recursos/jugador/spritejugador1.png");
    cargarTransparente(shRun1,   ":/new/Recursos/jugador/spritejugador2.png");
    cargarTransparente(shRun2,   ":/new/Recursos/jugador/spritejugador3.png");
    cargarTransparente(shThrow,  ":/new/Recursos/jugador/spritejugador4.png");
    cargarTransparente(shJump,   ":/new/Recursos/jugador/spritejugador5.png");
    cargarTransparente(shCrouch, ":/new/Recursos/jugador/spritejugador6.png");

    // ── 2. CANAL ENEMIGOS (Remoción de fondo sin alterar la figura) ──
    cargarTransparente(shBoar,       ":/new/Recursos/enemigos/enemigo1.png");
    cargarTransparente(shBossSwingL, ":/new/Recursos/enemigos/enemigo2.png");
    cargarTransparente(shBossSwingR, ":/new/Recursos/enemigos/enemigo3.png");
    cargarTransparente(shBossFire,   ":/new/Recursos/enemigos/enemigo4.png");
    cargarTransparente(shBossHit,    ":/new/Recursos/enemigos/enemigo5.png");

    // ── 3. CANAL PROYECTILES (Remoción de fondo sin alterar la figura) ──
    cargarTransparente(shDartH, ":/new/Recursos/proyectil/proyectil1.png");
    cargarTransparente(shDartA, ":/new/Recursos/proyectil/proyectil2.png");
    cargarTransparente(shArrow, ":/new/Recursos/proyectil/proyectil3.png");
    cargarTransparente(shBall,  ":/new/Recursos/proyectil/proyectil4.png");

    // ── 4. CANAL HUD ──
    // Se carga nativo asumiendo que ya posee canal alpha transparente
    shHud.load(":/new/Recursos/hud/hud.png");

    // ── 5. CANALES DE FONDO (No se remueve color ya que llenan toda la pantalla) ──
    QPixmap bg1_raw(":/new/Recursos/fondos/fondo1.png");
    bgNivel1 = bg1_raw.scaled(4608, 720, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    QPixmap bg2_raw(":/new/Recursos/fondos/fondo2.png");
    bgNivel2 = bg2_raw.scaled(1280, 720, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
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

// ── Extrae un frame horizontal de un spritesheet ─────────────
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

    // ── Tick de animación del jugador ────────────────────────
    ticksFrame++;
    if (ticksFrame >= 9) {
        ticksFrame = 0;
        frameActual = (frameActual + 1) % 7;
    }

    // ── Tick de animación del jabalí ─────────────────────────
    ticksBoar++;
    if (ticksBoar >= 5) {
        ticksBoar = 0;
        frameBoar = (frameBoar + 1) % 4;
    }

    // ── Tick de animación del boss ───────────────────────────
    if (bossActual) {
        ticksBoss++;
        if (ticksBoss >= 7) {
            ticksBoss = 0;
            frameBoss = (frameBoss + 1) % 5;   // 5 frames en swing sheets
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

// ============================================================
//  DIBUJAR NIVEL 1
// ============================================================
void EscenaJuego::dibujarNivel1(QPainter& p)
{
    int camX = static_cast<int>(camaraX);

    // Dibujamos el fondo desde el offset calculado
    // Fuente: (camX, 0, 1280, 720)
    // Destino: (0, 0, 1280, 720)
    p.drawPixmap(0, 0, bgNivel1, camX, 0, 1280, 720);

    if (jugadorActual) {
        dibujarJugadorNivel1(p, jugadorActual);
        dibujarHUD(p, jugadorActual, 0, jugadorActual->getPuntos());
    }

    if (gm && gm->getNivelActual()) {
        auto enemigosSelva = gm->getNivelActual()->getEnemigos();
        for (auto* enemigo : enemigosSelva) {
            if (enemigo && enemigo->estaVivo()) {
                // Jabalí animado con 4 frames de 516x512
                QPixmap sprEnemy = frame(shBoar, frameBoar, 516, 512);
                p.drawPixmap(
                    static_cast<int>(enemigo->getX()) - static_cast<int>(camaraX),
                    static_cast<int>(enemigo->getY()),
                    escalar(sprEnemy, 64, 64));

                // Barra de vida del enemigo
                int xBarra = static_cast<int>(enemigo->getX()) - static_cast<int>(camaraX);
                int yBarra = static_cast<int>(enemigo->getY()) - 12;
                p.fillRect(xBarra, yBarra, 50, 6, Qt::red);
                p.fillRect(xBarra, yBarra, enemigo->getVida(), 6, Qt::green);
            }
        }
    }
}

// ============================================================
//  DIBUJAR NIVEL 2
// ============================================================
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

// ============================================================
//  DIBUJAR JUGADOR NIVEL 1  —  cada acción = su spritesheet
// ============================================================
void EscenaJuego::dibujarJugadorNivel1(QPainter& p, Jugador* jugador)
{
    if (!jugador) return;
    QPixmap sprite;

    if (jugador->getSaltando()) {
        // jump: 4 frames de 516x512
        sprite = frame(shJump, frameActual % 4, 516, 512);
    } else if (jugador->getAgachado()) {
        // crouch: 4 frames de 516x512
        sprite = frame(shCrouch, frameActual % 4, 516, 512);
    } else if (teclaEspacio) {
        // throw: 4 frames de 448x592
        sprite = frame(shThrow, frameActual % 4, 448, 592);
    } else if (teclaIzq || teclaDer) {
        // Solución al bug del parpadeo: tiramos de shRun1 estable con sus 7 frames de 363x416
        sprite = frame(shRun1, frameActual % 7, 363, 416);
    } else {
        // idle: 4 frames de 636x416
        sprite = frame(shIdle, frameActual % 4, 636, 416);
    }

    // Inversión horizontal fluida del sprite según la orientación lógica
    if (!jugador->estaMirandoDerecha()) {
        sprite = sprite.transformed(QTransform().scale(-1, 1));
    }

    // Centrado visual respecto a la Hitbox física del backend
    p.drawPixmap(
        static_cast<int>(jugador->getX()) - static_cast<int>(camaraX) - 16,
        static_cast<int>(jugador->getY()) - 32,
        escalar(sprite, 96, 96));
}

// ============================================================
//  DIBUJAR JUGADOR NIVEL 2  —  igual que nivel 1, sin cámara
// ============================================================
void EscenaJuego::dibujarJugadorNivel2(QPainter& p, Jugador* jugador)
{
    if (!jugador) return;
    QPixmap sprite;

    if (jugador->getSaltando()) {
        sprite = frame(shJump, frameActual % 4, 516, 512);
    } else if (jugador->getAgachado()) {
        sprite = frame(shCrouch, frameActual % 4, 516, 512);
    } else if (teclaEspacio) {
        sprite = frame(shThrow, frameActual % 4, 448, 592);
    } else if (teclaIzq || teclaDer) {
        sprite = frame(shRun1, frameActual % 7, 363, 416);
    } else {
        sprite = frame(shIdle, frameActual % 4, 636, 416);
    }

    if (!jugador->estaMirandoDerecha()) {
        sprite = sprite.transformed(QTransform().scale(-1, 1));
    }

    p.drawPixmap(
        static_cast<int>(jugador->getX()) - 16,
        static_cast<int>(jugador->getY()) - 32,
        escalar(sprite, 96, 96));
}
// ============================================================
//  DIBUJAR BOSS  —  cambia de sheet según fase + animado
// ============================================================
void EscenaJuego::dibujarBoss(QPainter& p, JefeFinal* jefe)
{
    if (!jefe || !jefe->estaVivo()) return;

    QPixmap spriteBoss;
    int bx = static_cast<int>(jefe->getX());
    int by = static_cast<int>(jefe->getY());

    if (jefe->getFase() == 2) {
        // Fase 2 (golpeado): sheet hit 4 frames de 448x592
        spriteBoss = frame(shBossHit, frameBoss % 4, 448, 592);
    } else {
        // Fase 1: alterna swing izquierda (frameBoss par) y derecha (impar)
        if (frameBoss % 2 == 0)
            spriteBoss = frame(shBossSwingL, frameBoss % 5, 508, 416);
        else
            spriteBoss = frame(shBossSwingR, frameBoss % 5, 508, 416);
    }

    p.drawPixmap(bx, by, escalar(spriteBoss, 160, 160));

    int barraY = by - 20;
    dibujarBarraVida(p, bx, barraY, jefe->getVida(), jefe->getVidaMaxima(), 160);

    p.setPen(QColor("#FF3333"));
    p.setFont(QFont("Courier", 9, QFont::Bold));
    p.drawText(bx, barraY - 8,
               QString("HP JEFE: %1 / %2").arg(jefe->getVida()).arg(jefe->getVidaMaxima()));
}

// ============================================================
//  DIBUJAR PROYECTILES
// ============================================================
void EscenaJuego::dibujarProyectiles(QPainter& p, NivelBoss* nivel)
{
    if (!nivel) return;

    // Dardos horizontales — proyectil1: 1 frame (usa directo)
    auto dardosActuales = nivel->getDardos();
    for (auto* dardo : dardosActuales) {
        if (dardo) {
            // proyectil1 tiene 2 frames de 1032x512 → usamos frame 0 (horizontal)
            QPixmap pxDart = frame(shDartH, 0, 1032, 512);
            p.drawPixmap(static_cast<int>(dardo->getX()),
                         static_cast<int>(dardo->getY()),
                         escalar(pxDart, 48, 16));
        }
    }

    // Balones — proyectil4: icono directo
    auto balonesActuales = nivel->getBalones();
    for (auto* balon : balonesActuales) {
        if (balon) {
            p.drawPixmap(static_cast<int>(balon->getX()),
                         static_cast<int>(balon->getY()),
                         escalar(shBall, 32, 32));
        }
    }
}

// ============================================================
//  DIBUJAR HUD  —  usa los 4 iconos del hud.png por separado
//
//  hud.png: 2064x512 → 4 iconos de 516x512
//    índice 0 = corazón (vida)
//    índice 1 = balón   (puntos)
//    índice 2 = reloj   (tiempo)
//    índice 3 = rayo    (power-ups)
// ============================================================
void EscenaJuego::dibujarHUD(QPainter& p, Jugador* jugador, int tiempo, int puntaje)
{
    const int ICO = 36;   // tamaño de cada icono en pantalla
    const int PAD = 10;   // margen izquierdo/superior
    const int SEP = 8;    // separación entre icono y texto

    // ── Fondo semitransparente del HUD ──
    p.fillRect(PAD, PAD, 340, 80, QColor(0, 0, 0, 140));

    // ── Icono corazón + barra de vida ──
    QPixmap icoCorazon = frame(shHud, 0, 516, 512);
    p.drawPixmap(PAD + 4, PAD + 4, escalar(icoCorazon, ICO, ICO));
    dibujarBarraVida(p,
                     PAD + 4 + ICO + SEP,
                     PAD + 14,
                     jugador->getVida(),
                     jugador->getVidaMaxima(),
                     200);

    // ── Icono balón + puntos ──
    QPixmap icoBalon = frame(shHud, 1, 516, 512);
    p.drawPixmap(PAD + 4, PAD + ICO + 10, escalar(icoBalon, ICO, ICO));
    p.setPen(QColor("#FFFFFF"));
    p.setFont(QFont("Courier", 11, QFont::Bold));
    p.drawText(PAD + 4 + ICO + SEP,
               PAD + ICO + 10 + ICO - 6,
               QString("PUNTOS: %1").arg(puntaje));

    // ── Icono reloj + tiempo (solo nivel 2) ──
    if (gm && gm->getNumeroNivel() == 2) {
        QPixmap icoReloj = frame(shHud, 2, 516, 512);
        p.drawPixmap(220, PAD + 4, escalar(icoReloj, ICO, ICO));
        p.setPen(QColor("#FFFFFF"));
        p.setFont(QFont("Courier", 11, QFont::Bold));
        p.drawText(220 + ICO + SEP, PAD + ICO - 2,
                   QString("T: %1s").arg(tiempo));
    }

    // ── Icono rayo + power-ups activos ──
    if (jugador->getModoFortachon() || jugador->getModoVeloz()) {
        QPixmap icoRayo = frame(shHud, 3, 516, 512);
        p.drawPixmap(220, PAD + ICO + 10, escalar(icoRayo, ICO, ICO));
        p.setFont(QFont("Courier", 9, QFont::Bold));
        QString powers;
        if (jugador->getModoFortachon()) { p.setPen(QColor("#FF3366")); powers += "FORTACHON "; }
        if (jugador->getModoVeloz())     { p.setPen(QColor("#33FF66")); powers += "VELOZ"; }
        p.drawText(220 + ICO + SEP, PAD + ICO + 10 + ICO - 6, powers);
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
    p.drawText(rect(), Qt::AlignCenter,
               QString("HAS COMPLETADO EL DESAFIO DEL JUEGO\n\nPUNTAJE FINAL: %1").arg(puntajeFinal));
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
    if (event->key() == Qt::Key_Space)                               teclaEspacio = true;
}

void EscenaJuego::keyReleaseEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_A || event->key() == Qt::Key_Left)  teclaIzq = false;
    if (event->key() == Qt::Key_D || event->key() == Qt::Key_Right) teclaDer = false;
    if (event->key() == Qt::Key_W || event->key() == Qt::Key_Up)    teclaArriba = false;
    if (event->key() == Qt::Key_S || event->key() == Qt::Key_Down)  teclaAbajo = false;
    if (event->key() == Qt::Key_Space)                               teclaEspacio = false;
}

