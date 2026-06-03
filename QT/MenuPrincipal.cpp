#include "MenuPrincipal.h"

#include <QVBoxLayout>
#include <QPushButton>
#include <QComboBox>
#include <QLineEdit>

MenuPrincipal::MenuPrincipal()
{
    QVBoxLayout* layout =
        new QVBoxLayout(this);

    nombreJugador =
        new QLineEdit();

    nombreJugador->setPlaceholderText(
        "Nombre jugador"
        );

    selectorDificultad =
        new QComboBox();

    selectorDificultad->addItem("Facil");

    selectorDificultad->addItem("Intermedio");

    selectorDificultad->addItem("Dificil");

    botonJugar =
        new QPushButton("JUGAR");

    layout->addWidget(nombreJugador);

    layout->addWidget(selectorDificultad);

    layout->addWidget(botonJugar);
}
