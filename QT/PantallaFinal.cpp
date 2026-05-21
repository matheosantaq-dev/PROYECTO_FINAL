#include "PantallaFinal.h"

#include <QVBoxLayout>
#include <QLabel>

PantallaFinal::PantallaFinal()
{
    QVBoxLayout* layout =
        new QVBoxLayout(this);

    QLabel* texto =
        new QLabel(
            "GANASTE"
        );

    layout->addWidget(texto);
}
