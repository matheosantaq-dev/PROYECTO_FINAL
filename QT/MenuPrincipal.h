#ifndef MENUPRINCIPAL_H
#define MENUPRINCIPAL_H

#include <QWidget>

class QPushButton;
class QComboBox;
class QLineEdit;

class MenuPrincipal : public QWidget
{
    Q_OBJECT

private:

    QPushButton* botonJugar;

    QComboBox* selectorDificultad;

    QLineEdit* nombreJugador;

public:

    MenuPrincipal();
};

#endif
