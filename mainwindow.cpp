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

    ui->widgetSelector->hide();
    ui->btnIniciar->show();

    // Conexión
   // connect(ui->btnTirar, &QPushButton::clicked, this, &MainWindow::tirarDado);
    connect(ui->btnIniciar, &QPushButton::clicked, this, &MainWindow::iniciarJuego);
    connect(ui->btnCerrar, &QPushButton::clicked, this, &MainWindow::close);
    connect(ui->confJugadores, &QPushButton::clicked, this, &MainWindow::confirmarCantidadJugadores);

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
    ui->btnIniciar->hide();
    ui->btnCerrar->hide();



    // Aquí iniciás tu lógica del juego

    ui->widgetSelector->show();

  //  actualizarUI();  // Por ejemplo
}
void MainWindow::confirmarCantidadJugadores(){
    int cantidad = ui->canJugadores->currentText().toInt();

    //arreglar   juegoActual.reiniciar();
    if (cantidad >= 2) juegoActual.agregarJugador("Jugador 1");
    if (cantidad >= 3) juegoActual.agregarJugador("Jugador 2");
    if (cantidad >= 4) juegoActual.agregarJugador("Jugador 3");
    if (cantidad == 4) juegoActual.agregarJugador("Jugador 4");

    ui->widgetSelector->hide();
}


