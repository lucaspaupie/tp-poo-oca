#include "mainwindow.h"
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QDebug>
#include <QPixmap>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //cosas del dado
    miDado = new dado();

    //aca vamos a poner todos los connect de botones
    connect(ui->botoncomenzar, &QPushButton::clicked, this, &MainWindow::mostrarSeleccionPersonajes);
    connect(ui->siguiente, &QPushButton::clicked, this, &MainWindow::pj);
    connect(ui->BTdado, &QPushButton::clicked, this, &MainWindow::BTdado);

    // Crear jugadores
    juegoActual.agregarJugador("Lucas");
    juegoActual.agregarJugador("Axel");
    juegoActual.agregarJugador("Luciano");

    iniciarjuego();
    actualizarUI();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete miDado;
}

void MainWindow::actualizarUI()
{
    jugador &actual = juegoActual.getJugadorActual();
    setWindowTitle("Turno de: " + actual.getNombre() + " (Casilla "
                   + QString::number(actual.getPosicion()) + ")");
}

void MainWindow::BTdado(bool)
{
    int resultado1 = miDado->tirar();

    qDebug() << "Dado 1:" << resultado1;

    QString rutaImagen1 = QString(":/new/prefix1/imagenes/dado%1.png").arg(resultado1);
    QPixmap skin1(rutaImagen1);

    if (skin1.isNull()) qDebug() << "❌ ERROR: No se pudo cargar imagen dado 1.";

    if (!ui->labelDado ) {
        qDebug() << "❌ QLabel no encontrado.";
        return;
    }

    ui->labelDado->setPixmap(skin1.scaled(ui->labelDado->size(), Qt::KeepAspectRatio));
}

// void MainWindow::tirarDado()
// {
//     int resultado = juegoActual.tirarDadoYAvanzar();
//     if (juegoActual.esFinDelJuego()) {
//         QMessageBox::information(this, "Fin del juego", juegoActual.ganador() + " ha ganado 🎉");
//     } else {
//         juegoActual.pasarTurno();
//         actualizarUI();
//     }
// }

void MainWindow::iniciarjuego()
{
    connect(ui->botoncerrar, &QPushButton::clicked, this, &MainWindow::cerrarJuego);
}

void MainWindow::cerrarJuego()
{
    QApplication::quit();
}

void MainWindow::mostrarSeleccionPersonajes()
{
    qDebug() << "Cambiando a seleccionpjs";
    ui->stackedWidget->setCurrentWidget(ui->seleccionpjs);
}

void MainWindow::on_comboBox_activated(int index)
{
    Q_UNUSED(index);  // para que no dé warning dsp lo saco

    connect(ui->numpj, QOverload<int>::of(&QComboBox::activated),
            this, &MainWindow::cantjug);
}

void MainWindow::cantjug()
{
    qDebug() << "Función cantjug llamada correctamente";
    actualizarUI();
}

void MainWindow::pj()
{
    ui->stackedWidget->setCurrentWidget(ui->tablero);
}
