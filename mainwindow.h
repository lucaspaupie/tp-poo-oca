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
   // void tirarDado(); // conectado al botón
    void iniciarjuego();
    void confirmarCantidadJugadores();
    void BTdado(bool);

    void on_botoncomenzar_clicked();

    void on_numpj_activated(int index);

    void on_siguiente_clicked();

private:
    Ui::MainWindow *ui;
    Juego juegoActual;
    void cerrarJuego();
    void actualizarUI();
    void mostrarSeleccionPersonajes();
    void cantjug();
    void pj();
    void verificarFinDelJuego();
    Juego juego;
    dado* miDado;
    void mostrarGanadorEnPantalla(const QString& nombre, bool esTT);


    void actualizarTablero();
  //  QVector<QVector<QPoint>> posicionesJugadores;

};




#endif // MAINWINDOW_H
