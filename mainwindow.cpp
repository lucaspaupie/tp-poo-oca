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

    //seleccion de jugadores
    connect(ui->numpj, QOverload<int>::of(&QComboBox::activated), this, &MainWindow::on_numpj_activated);
    on_numpj_activated(ui->numpj->currentIndex());


    // // Crear jugadores
    // juegoActual.agregarJugador("Lucas");
    // juegoActual.agregarJugador("Axel");
    // juegoActual.agregarJugador("Luciano");



    juegoActual.getTablero()->cargarCoordenadas();

    //jugadores coordenadas
   // posicionesJugadores.resize(4); //4 jugadores

    // posicionesJugadores[0] = {
    // QPoint(120, 620), QPoint(250, 620), QPoint(320, 620),
    // QPoint(390, 620), QPoint(450, 620), QPoint(520, 620),
    // QPoint(600, 620), QPoint(670, 620), QPoint(720, 620),
    // QPoint(800, 620), QPoint(850, 550), QPoint(880, 500),
    // QPoint(910, 450), QPoint(930, 390), QPoint(950, 300),
    // QPoint(940, 240), QPoint(930, 170), QPoint(890, 120),
    // QPoint(800, 50),  QPoint(720, 20),  QPoint(640, 10),
    // QPoint(580, 10),  QPoint(510, 10),  QPoint(450, 10),
    // QPoint(380, 10),  QPoint(320, 10),  QPoint(250, 10),
    // QPoint(180, 30),  QPoint(120, 70),  QPoint(80, 120),
    // QPoint(40, 180),  QPoint(30, 250),  QPoint(40, 320),
    // QPoint(40, 400),  QPoint(70, 470),  QPoint(160, 480),
    // QPoint(210, 510), QPoint(270, 520), QPoint(320, 520),
    // QPoint(390, 520), QPoint(450, 520), QPoint(520, 520),
    // QPoint(600, 520), QPoint(670, 520), QPoint(720, 510),
    // QPoint(780, 460), QPoint(810, 410), QPoint(820, 360),
    // QPoint(820, 310), QPoint(850, 230), QPoint(780, 150),
    // QPoint(720, 120), QPoint(620, 110), QPoint(530, 110),
    // QPoint(450, 110), QPoint(380, 110), QPoint(310, 110),
    // QPoint(240, 110), QPoint(190, 170), QPoint(140, 280),
    // QPoint(200, 350), QPoint(230, 400), QPoint(270, 420),
    // QPoint(490, 310)

    // };


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

    //comprueba si puede jugar
    if (!actual.puedeJugar()) {
        QString msg;

        if (actual.getTurnosPenalizado() > 0) {
            int turnosRestantes = actual.getTurnosPenalizado();
            msg = "Estás penalizado. Te quedan " + QString::number(turnosRestantes) + " turno(s).";
            actual.penalizar(-1);  // Restar un turno
        } else if (actual.estaAtrapado()) {
            msg = "Estás atrapado en el pozo. Esperá que otro jugador te libere.";
        }

        ui->mensaje->setText(msg);
        QTimer::singleShot(3000, this, [this]() {
            ui->mensaje->clear();
        });

        juegoActual.pasarTurno();
        actualizarUI();
        return;
    }

    QString mensajeEspecial = juegoActual.getTablero()->moverJugador(actual, resultado1);
    ui->mensaje->setText(mensajeEspecial);

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

void MainWindow::on_numpj_activated(int index){

    Q_UNUSED(index);  // para que no dé warning dsp lo saco

    int numJugadoresSeleccionados = ui->numpj->currentText().toInt();
    if (numJugadoresSeleccionados < 2 || numJugadoresSeleccionados > 4) {
        numJugadoresSeleccionados = 2; // Valor por defecto si hay un error
    }

    // qDebug() << "on_comboBox_activated: Seleccionados " << numJugadoresSeleccionados << " jugadores.";


    //agregar esto777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777
    juegoActual.limpiarJugadores();

    QStringList nombresBase = {"Lucas", "Axel", "Luciano", "Julio"}; // Nombres predefinidos
    for (int i = 0; i < numJugadoresSeleccionados; ++i) {
        juegoActual.agregarJugador(nombresBase.at(i));
    }

    QList<QLabel*> fichas = {ui->Jugador_1, ui->Jugador_2, ui->Jugador_3, ui->Jugador_4};

    for (int i = 0; i < fichas.size(); ++i) {
        if (fichas.at(i)) {
            if (i < numJugadoresSeleccionados) {
                fichas.at(i)->setVisible(true);
            } else {
                fichas.at(i)->setVisible(false);
            }
        }
    }

    actualizarTablero();
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



// Asegúrate de que esta función exista:
void MainWindow::on_botoncomenzar_clicked() {
    qDebug() << "on_botoncomenzar_clicked: Iniciando el juego.";
    // Ahora que los jugadores están configurados, puedes iniciar el juego
    juegoActual.iniciar(); // Resetea posiciones y penalizaciones
    ui->stackedWidget->setCurrentWidget(ui->tablero); // Cambia a la pantalla del tablero
    actualizarTablero(); // Asegura que las fichas estén en Start
    actualizarUI();
}

// Asegúrate de que esta función exista:
void MainWindow::on_siguiente_clicked() {
    // Código para pasar al siguiente turno, si este botón hace eso

    // Aquí podrías tener lógica como juegoActual.pasarTurno();
    // o cualquier otra acción que haga tu botón "siguiente".
}
