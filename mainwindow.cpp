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
#include <QFileDialog>
#include <QAction>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_fichasJugadores[0] = ui->Jugador_1;
    m_fichasJugadores[1] = ui->Jugador_2;
    m_fichasJugadores[2] = ui->Jugador_3;
    m_fichasJugadores[3] = ui->Jugador_4;

    //cosas del dado
    miDado = new dado();
    miDado2 = new dado();

    if (ui->comboCasillas) {
        ui->comboCasillas->clear();
        for (int n = 63; n <= 90; ++n) {
            ui->comboCasillas->addItem(QString::number(n));
        }
        // seleccionar por defecto 63 (o el índice que quieras)
        ui->comboCasillas->setCurrentIndex(0);

        // conectar señal
        connect(ui->comboCasillas, QOverload<int>::of(&QComboBox::activated),
                this, &MainWindow::on_comboCasillas_activated);
    }

    //aca vamos a poner todos los connect de botones
    connect(ui->botoncomenzar, &QPushButton::clicked, this, &MainWindow::mostrarSeleccionPersonajes);
    connect(ui->siguiente, &QPushButton::clicked, this, &MainWindow::pj);
    connect(ui->BTdado, &QPushButton::clicked, this, &MainWindow::BTdado);

    //seleccion de jugadores
    connect(ui->numpj, QOverload<int>::of(&QComboBox::activated), this, &MainWindow::on_numpj_activated);
    on_numpj_activated(ui->numpj->currentIndex());



    // NOTA IMPORTANTE: Para usar los slots de guardar/cargar (ej: on_actionGuardarBinario_triggered),
    // debes conectar un QAction (si usas menú) o un QPushButton (si usas un botón)
    // en tu archivo .ui a estos slots en tu código.

    iniciarjuego();
    actualizarUI();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete miDado;
    delete miDado2;
}

// --- SLOTS DE PERSISTENCIA JSON (Texto - Configuración) ---

void MainWindow::on_actionGuardar_triggered() {
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    "Guardar Configuración de Juego",
                                                    QDir::homePath(),
                                                    "Archivos JSON (*.json)");

    if (!fileName.isEmpty()) {
        if (juegoActual.guardarJuego(fileName)) {
            QMessageBox::information(this, "Guardar", "Configuración de juego (JSON) guardada correctamente.");
        } else {
            QMessageBox::critical(this, "Error", "Fallo al guardar la configuración (JSON).");
        }
    }
}

void MainWindow::on_actionCargar_triggered() {
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    "Cargar Configuración de Juego",
                                                    QDir::homePath(),
                                                    "Archivos JSON (*.json)");

    if (!fileName.isEmpty()) {
        if (juegoActual.cargarJuego(fileName)) {
            QMessageBox::information(this, "Cargar", "Configuración cargada (JSON) correctamente.");
            ui->stackedWidget->setCurrentWidget(ui->tablero);
            actualizarTablero();
            actualizarUI();
        } else {
            QMessageBox::critical(this, "Error", "Fallo al cargar la configuración (JSON).");
        }
    }
}

// --- SLOTS DE PERSISTENCIA BINARIA (Avance de Partida) ---

void MainWindow::on_actionGuardarBinario_triggered() {
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    "Guardar Partida (Binario)",
                                                    QDir::homePath(),
                                                    "Archivos de Partida (*.dat)");

    if (!fileName.isEmpty()) {
        if (juegoActual.guardarPartidaBinario(fileName)) {
            QMessageBox::information(this, "Guardar", "Partida (Binario) guardada correctamente.");
        } else {
            QMessageBox::critical(this, "Error", "Fallo al guardar la partida (Binario).");
        }
    }
}

void MainWindow::on_actionCargarBinario_triggered() {
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    "Cargar Partida (Binario)",
                                                    QDir::homePath(),
                                                    "Archivos de Partida (*.dat)");

    if (!fileName.isEmpty()) {
        if (juegoActual.cargarPartidaBinario(fileName)) {
            QMessageBox::information(this, "Cargar", "Partida cargada (Binario) correctamente.");
            ui->stackedWidget->setCurrentWidget(ui->tablero);
            actualizarTablero();
            actualizarUI();
        } else {
            QMessageBox::critical(this, "Error", "Fallo al cargar la partida (Binario).");
        }
    }
}

// --- MÉTODOS EXISTENTES Y CORREGIDOS ---

void MainWindow::actualizarUI()
{
    if (juegoActual.getCantidadJugadores() == 0) return;

    jugador& actual = juegoActual.getJugadorActual();
    setWindowTitle("Turno de: " + actual.getNombre() + " (Casilla "
                   + QString::number(actual.getPosicion()) + ")");

    // ** CORRECCIÓN DE ERROR 'labelTurno' **
    // Usamos 'mensaje' como alternativa para evitar el error de compilación.
    if (ui->mensaje && ui->mensaje->text().isEmpty()) {
        ui->mensaje->setText("Turno actual: " + actual.getNombre());
    }
}

void MainWindow::BTdado(bool)
{
    // Tirar ambos dados
    int resultado1 = miDado->tirar();
    int resultado2 = miDado2->tirar();

    qDebug() << "Dado 1:" << resultado1 << " Dado 2:" << resultado2;

    // Cargar imágenes
    QString ruta1 = QString(":/new/prefix1/imagenes/dado%1.png").arg(resultado1);
    QString ruta2 = QString(":/new/prefix1/imagenes/dado%1.png").arg(resultado2);

    QPixmap skin1(ruta1);
    QPixmap skin2(ruta2);

    if (!skin1.isNull()) {
        ui->labelDado->setPixmap(skin1.scaled(ui->labelDado->size(), Qt::KeepAspectRatio));
    }

    if (ui->labelDado2_2 && !skin2.isNull()) {
        ui->labelDado2_2->setPixmap(skin2.scaled(ui->labelDado2_2->size(), Qt::KeepAspectRatio));
    }

    // Sumar los resultados de ambos dados
    int avance = resultado1 + resultado2;

    jugador& actual = juegoActual.getJugadorActual();

    if (!actual.puedeJugar()) {
        QString msg;

        if (actual.getTurnosPenalizado() > 0) {
            msg = "Estás penalizado. Te quedan " + QString::number(actual.getTurnosPenalizado()) + " turno(s) para descansar.";
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

    // Mover al jugador la suma de los dos dados
    QString mensajeEspecial = juegoActual.getTablero()->moverJugador(actual, avance);

    actualizarTablero();
    ui->mensaje->setText("Sacaste " + QString::number(resultado1) + " y " +
                         QString::number(resultado2) +
                         " → avanzás " + QString::number(avance) + " casillas.\n" +
                         mensajeEspecial);

    if (!mensajeEspecial.isEmpty()) {
        QTimer::singleShot(3000, this, [this]() {
            ui->mensaje->clear();
        });
    }

    if (actual.getRepetirTurno()) {
        actual.setRepetirTurno(false);
        ui->mensaje->setText("Caíste en la Oca. ¡Volvé a tirar!");
        actualizarUI();
        return;
    }

    if (juegoActual.esFinDelJuego()) {
        QMessageBox::information(this, "Fin del Juego", "¡" + actual.getNombre() + " ha ganado!");
        cerrarJuego();
        return;
    }

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

    Q_UNUSED(index);

    int numJugadoresSeleccionados = ui->numpj->currentText().toInt();
    if (numJugadoresSeleccionados < 2 || numJugadoresSeleccionados > 4) {
        numJugadoresSeleccionados = 2;
    }

    juegoActual.limpiarJugadores();

    QStringList nombresBase = {"Lucas", "Axel", "Luciano", "Julio"};
    for (int i = 0; i < numJugadoresSeleccionados; ++i) {
        juegoActual.agregarJugador(nombresBase.at(i));
    }
/*
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
*/
    for (int i = 0; i < m_fichasJugadores.size(); ++i){
        QLabel* ficha = m_fichasJugadores[i];
        if (ficha) {
            // Mostrar la ficha si su índice es menor que la cantidad de jugadores
            ficha->setVisible(i < numJugadoresSeleccionados);
        }
    }

    actualizarTablero();
    actualizarUI();
}
void MainWindow::pj()
{
    ui->stackedWidget->setCurrentWidget(ui->tablero);
}
/*
void MainWindow::actualizarTablero() {
   /* for (int i = 0; i < juegoActual.getCantidadJugadores(); ++i) {
        int posicion = juegoActual.getJugador(i).getPosicion();
        QPoint baseCoord = juegoActual.getTablero()->getCoordenadaCasilla(posicion, i);

        QLabel* ficha = nullptr;
        switch (i) {
        case 0: ficha = ui->Jugador_1; break;
        case 1: ficha = ui->Jugador_2; break;
        case 2: ficha = ui->Jugador_3; break;
        case 3: ficha = ui->Jugador_4; break;
        }

        if (ficha) ficha->move(baseCoord);
    }

   //funcion modificada lucho 29/10
   for (int i = 0; i < juegoActual.getCantidadJugadores(); ++i) {

       // 1. Obtenemos la posición LÓGICA (ej: casilla 25)
       int posicion = juegoActual.getJugador(i).getPosicion();


       // 2. Pedimos a la clase Tablero las coordenadas (x, y) de esa casilla
       //    (Tu función ya incluye el offset para que no se pisen)
       QPoint baseCoord = juegoActual.getTablero()->getCoordenadaCasilla(posicion, i);

       // 3. Obtenemos el QLabel de la ficha usando nuestro MAPA
       QLabel* ficha = m_fichasJugadores[i];

       // 4. Movemos el QLabel a esas coordenadas
       if (ficha) {
           ficha->move(baseCoord);
           ficha->raise(); // (Opcional) Pone la ficha "encima" de todo
       }
   }
}
*/

void MainWindow::actualizarTablero()
{
    int numCasillas = juegoActual.getTablero()->getNumCasillas();

    // Mostrar solo las casillas que existen
    for (int i = 0; i <= 90; ++i) {  // <= en lugar de < 90
        QString nombreCasilla = QString("casilla%1").arg(i);
        QLabel* label = findChild<QLabel*>(nombreCasilla);
        if (label) {
            label->setVisible(i < numCasillas); // ocultará las que sobran
        }
    }


    // Ahora actualizamos las fichas de los jugadores
    for (int i = 0; i < juegoActual.getCantidadJugadores(); ++i) {
        int posicion = juegoActual.getJugador(i).getPosicion();

        if (posicion >= numCasillas) posicion = numCasillas - 1;

        QString nombreCasilla = QString("casilla%1").arg(posicion);
        QLabel* labelCasilla = findChild<QLabel*>(nombreCasilla);

        if (!labelCasilla) continue;

        QLabel* ficha = m_fichasJugadores[i];
        if (!ficha) continue;

        QPoint destino = labelCasilla->pos();

        // pequeño offset visual
        switch (i) {
        case 1: destino += QPoint(10, 0); break;
        case 2: destino += QPoint(0, 10); break;
        case 3: destino += QPoint(10, 10); break;
        }

        ficha->move(destino);
        ficha->raise();
    }
}

void MainWindow::on_botoncomenzar_clicked() {
    qDebug() << "on_botoncomenzar_clicked: Iniciando el juego.";

    juegoActual.reiniciarTablero(casillasElegidas);

    juegoActual.iniciar();
    ui->stackedWidget->setCurrentWidget(ui->tablero);
    actualizarTablero();
    actualizarUI();
}

void MainWindow::on_siguiente_clicked() {
    // Código para pasar al siguiente turno (parece no tener funcionalidad directa en este botón)
}

void MainWindow::cantjug(){}

void MainWindow::on_comboCasillas_activated(int index) {
    Q_UNUSED(index);
    if (!ui->comboCasillas) return;
    casillasElegidas = ui->comboCasillas->currentText().toInt();
    qDebug() << "Casillas elegidas:" << casillasElegidas;
}
