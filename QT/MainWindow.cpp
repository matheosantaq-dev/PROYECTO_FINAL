#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    resize(1200, 800);

    escena = new EscenaJuego(this);

    setCentralWidget(escena);
}

MainWindow::~MainWindow()
{

}
