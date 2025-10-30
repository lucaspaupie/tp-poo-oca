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

    // SLOTS PARA PERSISTENCIA JSON (Texto)
    void on_actionGuardar_triggered(); // Asume que este es el JSON
    void on_actionCargar_triggered();  // Asume que este es el JSON

    // NUEVOS SLOTS PARA PERSISTENCIA BINARIA
    void on_actionGuardarBinario_triggered();
    void on_actionCargarBinario_triggered();

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

    void actualizarTablero();
    QVector<QVector<QPoint>> posicionesJugadores;

    std::map<int, QLabel*> m_fichasJugadores;

};

#endif // MAINWINDOW_H
