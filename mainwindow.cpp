#include "mainwindow.h"
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Crear jugadores
    juegoActual.agregarJugador("Lucas");
    juegoActual.agregarJugador("Axel");
    juegoActual.agregarJugador("Luciano");

    iniciarjuego();
    // Conexión
   // connect(ui->btnTirar, &QPushButton::clicked, this, &MainWindow::tirarDado);
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




void MainWindow::iniciarjuego()
{
    connect(ui->botoncerrar, &QPushButton::clicked, this, &MainWindow::cerrarJuego);

}
void MainWindow::cerrarJuego() {
    QApplication::quit();
}

void MainWindow::on_botoncomenzar_clicked()
{
    connect(ui->botoncomenzar, &QPushButton::clicked, this, &MainWindow::mostrarSeleccionPersonajes);
}

void MainWindow::mostrarSeleccionPersonajes() {
    qDebug() << "Cambiando a seleccionpjs";
    ui->stackedWidget->setCurrentWidget(ui->seleccionpjs);
}



void MainWindow::on_comboBox_activated(int index)
{
    connect(ui->numpj, QOverload<int>::of(&QComboBox::activated),
            this, &MainWindow::cantjug);
}

void MainWindow::cantjug()
{
    qDebug() << "Función cantjug llamada correctamente";
    actualizarUI();  // Para mostrar el nuevo jugador actual
}

void MainWindow::on_siguiente_clicked()
{
    connect(ui->siguiente, &QPushButton::clicked, this, &MainWindow::pj);
}

void MainWindow::pj()
{
    ui->stackedWidget->setCurrentWidget(ui->elegirpj);
}
