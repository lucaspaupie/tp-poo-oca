#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "juego.h"
#include <map>      // <--- AÑADIR ESTO
#include <QLabel>

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
    void iniciarjuego();
    void BTdado(bool);
    void on_botoncomenzar_clicked();
    void on_numpj_activated(int index);
    void on_siguiente_clicked();
    void on_CargarPartida_clicked();
    void onGuardarPartidaClicked();
private:
    Ui::MainWindow *ui;
    Juego juegoActual;
    void cerrarJuego();
    void actualizarUI();
    void mostrarSeleccionPersonajes();
    void cantjug();
    void pj();
    Juego juego;
    dado* miDado;
    dado* miDado2;

    void moverJugadorACasilla(int indiceJugador, int numeroCasilla);
    void actualizarPosicionesJugadores();

    void actualizarTablero();
    QVector<QVector<QPoint>> posicionesJugadores;

    std::map<int, QLabel*> m_fichasJugadores;
    void dibujarCasillasEspeciales();

};

#endif // MAINWINDOW_H
