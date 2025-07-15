#include "mainwindow.h"
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include "ui_mainwindow.h"
#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Crear jugadores
    juegoActual.agregarJugador("Lucas");
    juegoActual.agregarJugador("Axel");
    juegoActual.agregarJugador("Luciano");

    // Conexión
    connect(ui->btnTirar, &QPushButton::clicked, this, &MainWindow::tirarDado);

    actualizarUI();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::actualizarUI()
{
    jugador &actual = juegoActual.getJugadorActual();
     //antes jugadorActual();
    setWindowTitle("Turno de: " + actual.getNombre() + " (Casilla "
                   + QString::number(actual.getPosicion()) + ")");
}

void MainWindow::tirarDado()
{
    /*int resultado =*/ juegoActual.tirarDadoYAvanzar();


    if (juegoActual.esFinDelJuego()) {
        QMessageBox::information(this, "Fin del juego", juegoActual.ganador() + " ha ganado 🎉");
    } else {
        juegoActual.pasarTurno();
        actualizarUI();
    }
}
void Juego::aplicarCasilla(){

}

void MainWindow::iniciarJuego() {
    // Aquí iniciás tu lógica del juego
    actualizarUI();  // Por ejemplo
}




