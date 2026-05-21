#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "EscenaJuego.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:

    EscenaJuego* escena;

public:

    MainWindow(QWidget *parent = nullptr);

    ~MainWindow();
};

#endif
