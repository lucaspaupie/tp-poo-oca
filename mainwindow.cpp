#include "mainwindow.h"
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QDebug>
#include <QPixmap>
#include "tablero.h"
#include <QPoint>
#include "casillaespecial.h"
#include <QTimer>

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



    juegoActual.getTablero()->cargarCoordenadas();

    //jugadores coordenadas
    posicionesJugadores.resize(4); //4 jugadores

    posicionesJugadores[0] = {
    QPoint(120, 620), QPoint(250, 620), QPoint(320, 620),
    QPoint(390, 620), QPoint(450, 620), QPoint(520, 620),
    QPoint(600, 620), QPoint(670, 620), QPoint(720, 620),
    QPoint(800, 620), QPoint(850, 550), QPoint(880, 500),
    QPoint(910, 450), QPoint(930, 390), QPoint(950, 300),
    QPoint(940, 240), QPoint(930, 170), QPoint(890, 120),
    QPoint(800, 50),  QPoint(720, 20),  QPoint(640, 10),
    QPoint(580, 10),  QPoint(510, 10),  QPoint(450, 10),
    QPoint(380, 10),  QPoint(320, 10),  QPoint(250, 10),
    QPoint(180, 30),  QPoint(120, 70),  QPoint(80, 120),
    QPoint(40, 180),  QPoint(30, 250),  QPoint(40, 320),
    QPoint(40, 400),  QPoint(70, 470),  QPoint(160, 480),
    QPoint(210, 510), QPoint(270, 520), QPoint(320, 520),
    QPoint(390, 520), QPoint(450, 520), QPoint(520, 520),
    QPoint(600, 520), QPoint(670, 520), QPoint(720, 510),
    QPoint(780, 460), QPoint(810, 410), QPoint(820, 360),
    QPoint(820, 310), QPoint(850, 230), QPoint(780, 150),
    QPoint(720, 120), QPoint(620, 110), QPoint(530, 110),
    QPoint(450, 110), QPoint(380, 110), QPoint(310, 110),
    QPoint(240, 110), QPoint(190, 170), QPoint(140, 280),
    QPoint(200, 350), QPoint(230, 400), QPoint(270, 420),
    QPoint(490, 310)

    };


    iniciarjuego();
    actualizarUI();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::actualizarUI()
{
    jugador& actual = juegoActual.getJugadorActual();
    setWindowTitle("Turno de: " + actual.getNombre() + " (Casilla "
                   + QString::number(actual.getPosicion()) + ")");
}

void MainWindow::BTdado(bool)
{
    int resultado1 = miDado->tirar();

    qDebug() << "Dado 1:" << resultado1;

    QString rutaImagen1 = QString(":/new/prefix1/imagenes/dado%1.png").arg(resultado1);
    QPixmap skin1(rutaImagen1);

    if (!skin1.isNull()) {
        ui->labelDado->setPixmap(skin1.scaled(ui->labelDado->size(), Qt::KeepAspectRatio));
    }

    // Mover jugador actual
    jugador& actual = juegoActual.getJugadorActual();
    QString mensajeEspecial = juegoActual.getTablero()->moverJugador(actual, resultado1);

    // Verificar si cayó en casilla especial y obtener mensaje
    int currentPos = actual.getPosicion();

    // Actualizar posición visual
    actualizarTablero();

    // Mostrar mensaje especial (si lo hay) en labelMensaje
    ui->mensaje->setText(mensajeEspecial);

    // Si querés que el mensaje desaparezca después de 3 segundos:
    if (!mensajeEspecial.isEmpty()) {
        QTimer::singleShot(3000, this, [this]() {
            ui->mensaje->clear();
        });
    }

    if (actual.getRepetirTurno()) {
        actual.setRepetirTurno(false); // reseteamos
        actualizarUI();
        return; // no se pasa turno
    }

    // Pasar turno
    juegoActual.pasarTurno();
    actualizarUI();
}


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

void MainWindow::actualizarTablero() {
    for (int i = 0; i < juegoActual.getCantidadJugadores(); ++i) {
        int posicion = juegoActual.getJugador(i).getPosicion();
        QPoint baseCoord = juegoActual.getTablero()->getCoordenadaCasilla(posicion);

        int offsetX = 0 * i;
        int offsetY = 24 * i;

        QPoint coord = baseCoord + QPoint(offsetX, offsetY);

        QLabel* ficha = nullptr;
        switch (i) {
        case 0: ficha = ui->Jugador_1; break;
        case 1: ficha = ui->Jugador_2; break;
        case 2: ficha = ui->Jugador_3; break;
        case 3: ficha = ui->Jugador_4; break;
        }

        if (ficha) ficha->move(coord);
    }
}
