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
#include <QPropertyAnimation>


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
        QPoint(800, 600), QPoint(850, 550), QPoint(880, 500),
        QPoint(910, 450), QPoint(950, 300), QPoint(950, 600),
        QPoint(940, 240), QPoint(930, 170), QPoint(890, 120),
        QPoint(800, 50),  QPoint(720, 20),  QPoint(640, 10),
        QPoint(580, 10),  QPoint(510, 10),  QPoint(450, 10),
        QPoint(380, 10),  QPoint(320, 10),  QPoint(250, 10),
        QPoint(180, 30),  QPoint(120, 70),  QPoint(130, 49),
        QPoint(40, 180),  QPoint(30, 250),  QPoint(40, 320),
        QPoint(40, 400),  QPoint(70, 470),  QPoint(160, 480),
        QPoint(210, 510), QPoint(320, 520), QPoint(320, 10),
        QPoint(450, 520),  QPoint(450, 10),  QPoint(520, 10),
        QPoint(600, 10),  QPoint(660, 10),  QPoint(720, 510),
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
    delete miDado;
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

    // Mover jugador actual con lógica de rebote y victoria
    jugador& actual = juegoActual.getJugadorActual();
    int posicionActual = actual.getPosicion();
    int nuevaPosicion = posicionActual + resultado1;

    if (nuevaPosicion == 63) {
        actual.setPosicion(63);
        actualizarTablero();
        QMessageBox::information(this, "¡Ganaste!", actual.getNombre() + " ha ganado el juego 🎉");
        // Aquí podrías deshabilitar botones o finalizar el juego si querés
        return;
    } else if (nuevaPosicion > 63) {
        int exceso = nuevaPosicion - 63;
        nuevaPosicion = 63 - exceso;
        actual.setPosicion(nuevaPosicion);
    } else {
        actual.setPosicion(nuevaPosicion);
    }

    actualizarTablero();
    juegoActual.pasarTurno();
    actualizarUI();

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

void MainWindow::actualizarTablero() {
    for (int i = 0; i < juegoActual.getCantidadJugadores(); ++i) {
        int posicion = juegoActual.getJugador(i).getPosicion();
        QPoint baseCoord = juegoActual.getTablero()->getCoordenadaCasilla(posicion);

        int offsetX = 6 * i;
        int offsetY = 6 * i;

        QPoint destino = baseCoord + QPoint(offsetX, offsetY);

        QLabel* ficha = nullptr;
        switch (i) {
        case 0: ficha = ui->Jugador_1; break;
        case 1: ficha = ui->Jugador_2; break;
        case 2: ficha = ui->Jugador_3; break;
        case 3: ficha = ui->Jugador_4; break;
        }

        if (ficha) {
            // Crear animación para mover la ficha
            QPropertyAnimation* anim = new QPropertyAnimation(ficha, "pos");
            anim->setDuration(400); // en milisegundos
            anim->setStartValue(ficha->pos());
            anim->setEndValue(destino);
            anim->setEasingCurve(QEasingCurve::OutCubic); // curva de movimiento suave
            anim->start(QAbstractAnimation::DeleteWhenStopped); // borra animación al terminar
        }
       /*
         ARREGLEN ESTO QUE ME COSTO BASTANTE ES LO DE LA IMAGEN DE EL GANADOR, YA TERMINE LO DEL GANADOR Y EL EFFECTO REBOTE QUE SI SE PASA

VUELVE PARA ATRAS DEPENDIENDO DEL RESULTADO





          if (nuevaPosicion == 63) {
            jugadorActual->setPosicion(63);

            // Mostrar imagen de victoria
            QPixmap imagenVictoria(":/new/prefi1/imagenes/tt_wins.png"); // Cambiá la ruta según tu imagen
            ui->widgetGanador->setPixmap(imagenVictoria);
            ui->widgetGanador->setScaledContents(true); // Para que se ajuste al tamaño del label
            ui->widgetGanador->setVisible(true);

            QMessageBox::information(this, "¡Victoria!", "¡El jugador ha ganado!");
            return;}*/
    }
}


void MainWindow::on_botoncomenzar_clicked() {
    // Código para iniciar el juego
}
void MainWindow::on_siguiente_clicked() {
    // Código para pasar al siguiente turno
}
void MainWindow::confirmarCantidadJugadores() {
    // Código para pasar al siguiente turno
}
