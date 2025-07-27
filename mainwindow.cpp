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
#include <QComboBox>

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

    //conecto boton
    connect(ui->numpj, QOverload<int>::of(&QComboBox::activated), this, &MainWindow::on_numpj_activated);
    on_numpj_activated(ui->numpj->currentIndex());



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

    // aca se fija si alguno termino el juego
    verificarFinDelJuego();

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

void MainWindow::on_numpj_activated(int index)
{
    int numJugadoresSeleccionados = ui->numpj->currentText().toInt();
    if (numJugadoresSeleccionados < 2 || numJugadoresSeleccionados > 4) {
        numJugadoresSeleccionados = 2; // Valor por defecto si hay un error
    }
    juegoActual.limpiarJugadores();

    QStringList nombresBase = {"Lucas", "Axel", "Luciano", "Marco"}; // Nombres predefinidos
    for (int i = 0; i < numJugadoresSeleccionados; ++i) {
        juegoActual.agregarJugador(nombresBase.at(i));
    }
    QList<QLabel*> fichas = {ui->Jugador_1, ui->Jugador_2, ui->Jugador_3, ui->Jugador_4};

    for (int i = 0; i < fichas.size(); ++i) {
        if (fichas.at(i)) { // Asegúrate de que el QLabel exista
            if (i < numJugadoresSeleccionados) {
                fichas.at(i)->setVisible(true); // Hacer visible la ficha
            } else {
                fichas.at(i)->setVisible(false); // Ocultar la ficha restante
            }
        }
    }
    actualizarTablero();
    actualizarUI();
//     connect(ui->numpj, QOverload<int>::of(&QComboBox::activated),
//             this, &MainWindow::cantjug);
//
}

void MainWindow::on_botoncomenzar_clicked() {
    juegoActual.iniciar();
    ui->stackedWidget->setCurrentWidget(ui->tablero);
    actualizarTablero();
    actualizarUI();
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
    QList<QLabel*> allFichas = {ui->Jugador_1, ui->Jugador_2, ui->Jugador_3, ui->Jugador_4};
    for(int i = juegoActual.getCantidadJugadores(); i < allFichas.size(); ++i) {
        if(allFichas.at(i)) allFichas.at(i)->setVisible(false);
    }
}

void MainWindow::on_siguiente_clicked() {
}
void MainWindow::confirmarCantidadJugadores() {
}

void MainWindow::verificarFinDelJuego()
{
    for (int i = 0; i < juegoActual.getCantidadJugadores(); ++i) {
        jugador& j = juegoActual.getJugador(i);
        if (j.getPosicion() >= 63) {
            qDebug() << "Jugador" << i + 1 << "ganó en la casilla 63.";

            QString nombreGanador = j.getNombre();
            bool esTT = (i == 0 || i == 1); // jugador 1 o 2 = TT
            mostrarGanadorEnPantalla(nombreGanador, esTT);

            return;
        }
    }
}

void MainWindow::mostrarGanadorEnPantalla(const QString& nombre, bool esTT)
{
    if (esTT) {
        ui->fichaganadoratt->setText("Ganador: " + nombre);
        ui->stackedWidget->setCurrentWidget(ui->ganadortt);
    } else {
        ui->fichaganadoract->setText("Ganador: " + nombre);
        ui->stackedWidget->setCurrentWidget(ui->ganadorct);
    }
}
