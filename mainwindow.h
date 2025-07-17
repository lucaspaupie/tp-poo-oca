#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "juego.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void tirarDado(); // conectado al botón
    void iniciarJuego();
    void confirmarCantidadJugadores();

private:
    Ui::MainWindow *ui;
    Juego juegoActual;
    void actualizarUI();
};




#endif // MAINWINDOW_H
