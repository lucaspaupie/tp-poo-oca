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
#include <QInputDialog>
#include <QDir>
#include "Juego.h"

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

    //aca vamos a poner todos los connect de botones
    connect(ui->GuardarPartida, &QPushButton::clicked, this, &MainWindow::onGuardarPartidaClicked);
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

/*void MainWindow::on_actionGuardar_triggered() {
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
}*/

// --- SLOTS DE PERSISTENCIA BINARIA (Avance de Partida) ---

/*void MainWindow::on_actionGuardarBinario_triggered() {
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
*/
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
    // Verificar tablero
    tablero* tb = juegoActual.getTablero();
    if (!tb) {
        QMessageBox::warning(this, "Error", "No hay tablero inicializado. Primero presioná 'Comenzar' o 'Cargar juego'.");
        return;
    }

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

void MainWindow::on_numpj_activated(int index)
{
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

    for (int i = 0; i < m_fichasJugadores.size(); ++i) {
        QLabel* ficha = m_fichasJugadores[i];
        if (ficha) {
            ficha->setVisible(i < numJugadoresSeleccionados);
        }
    }

    actualizarUI();
}

void MainWindow::pj()
{
    ui->stackedWidget->setCurrentWidget(ui->tablero);
}


void MainWindow::actualizarTablero()
{
    tablero* tb = juegoActual.getTablero();
    if (!tb) {
        qDebug() << "actualizarTablero: tablero no inicializado";
        return;
    }

    int numCasillas = tb->getNumCasillas(); // por ejemplo 70

    // Si tus labels están nombrados casilla1..casilla90:
    for (int i = 1; i <= 90; ++i) {
        QString nombreCasilla = QString("casilla%1").arg(i);
        QLabel* label = findChild<QLabel*>(nombreCasilla);
        if (label) {
            // mostrar 1..numCasillas, ocultar numCasillas+1..90
            label->setVisible(i <= numCasillas);
        }
    }

    // Actualizamos fichas como antes (usando posiciones válidas)
    for (int i = 0; i < juegoActual.getCantidadJugadores(); ++i) {
        int posicion = juegoActual.getJugador(i).getPosicion();
        if (posicion < 1) posicion = 1; // si tu lógica usa 1-based
        if (posicion > numCasillas) posicion = numCasillas;

        QString nombreCasilla = QString("casilla%1").arg(posicion);
        QLabel* labelCasilla = findChild<QLabel*>(nombreCasilla);
        if (!labelCasilla) continue;

        QLabel* ficha = m_fichasJugadores[i];
        if (!ficha) continue;

        QPoint destino = labelCasilla->pos();
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
    juegoActual.iniciar();
    ui->stackedWidget->setCurrentWidget(ui->tablero);
    actualizarTablero();
    actualizarUI();
}

void MainWindow::on_siguiente_clicked() {

        // Tomamos cantidad de jugadores del combo
        int numJugadores = ui->numpj->currentText().toInt();

        // Tomamos cantidad de casillas del spinbox (el nuevo control)
        int numCasillas = ui->CANTcasillas->value();

        // Creamos el tablero con la cantidad elegida
        tablero* t = new tablero(numCasillas);
        juegoActual.setTablero(t);

        // Iniciamos el juego
        juegoActual.iniciar(numJugadores);

        dibujarCasillasEspeciales();

        // Actualizamos interfaz y tablero
        actualizarTablero();
        actualizarUI();

}

void MainWindow::cantjug(){}
void MainWindow::onGuardarPartidaClicked()
{
    QString nombre = QInputDialog::getText(
        this,
        tr("Guardar partida"),
        tr("Ingrese un nombre para la partida:")
        );

    if (nombre.trimmed().isEmpty()) {
        QMessageBox::warning(this, tr("Aviso"), tr("Debe ingresar un nombre válido."));
        return;
    }

    QDir dir;
    if (!dir.exists("partidas")) {
        dir.mkdir("partidas");
    }

    QString ruta = QString("partidas/%1.bin").arg(nombre.trimmed());

    if (juegoActual.guardarPartidaBinario(ruta)) {
        QMessageBox::information(this, tr("Guardado exitoso"),
                                 tr("La partida se guardó correctamente como:\n%1").arg(ruta));
    } else {
        QMessageBox::critical(this, tr("Error"),
                              tr("No se pudo guardar la partida."));
    }
}

void MainWindow::on_CargarPartida_clicked()
{
    // Abre el diálogo para seleccionar la partida
    QString nombreArchivo = QFileDialog::getOpenFileName(
        this,
        tr("Cargar partida"),
        "partidas/",                  // Carpeta por defecto
        tr("Partidas guardadas (*.bin)") // Filtro
        );

    // Si no se seleccionó ningún archivo, cancelar
    if (nombreArchivo.isEmpty()) {
        QMessageBox::information(this, tr("Carga cancelada"), tr("No se seleccionó ninguna partida."));
        return;
    }


    // Intentar cargar la partida
    if (juegoActual.cargarPartidaBinario(nombreArchivo)) {
        QMessageBox::information(this, tr("Éxito"), tr("Partida cargada correctamente."));

        // Mostrar la pantalla del tablero
        ui->stackedWidget->setCurrentWidget(ui->tablero);
        dibujarCasillasEspeciales();

        // Actualizar las fichas y datos
        actualizarTablero();
        actualizarUI();

        // Mostrar quién tiene el turno
        ui->mensaje->setText("Turno de: " + juegoActual.getJugadorActual().getNombre());
    } else {
        QMessageBox::warning(this, tr("Error"), tr("No se pudo cargar la partida seleccionada."));
    }
}

void MainWindow::dibujarCasillasEspeciales()
{
    tablero* tb = juegoActual.getTablero();
    if (!tb) return;

    // Cargar la imagen base para las casillas normales una sola vez
    QPixmap pixmapNormal(":/imagenes/normal.png"); // <--- ¡Nueva Ruta!

    // Recorrer todas las casillas del tablero (usamos 1-based index hasta getNumCasillas())
    for (int i = 1; i <= tb->getNumCasillas(); ++i) {
        casilla* c = tb->getCasilla(i);
        if (!c) continue;

        QString nombreCasilla = QString("casilla%1").arg(i);
        QLabel* labelCasilla = findChild<QLabel*>(nombreCasilla);
        if (!labelCasilla) continue;

        // Intentar hacer un downcast a casillaespecial
        casillaespecial* especial = dynamic_cast<casillaespecial*>(c);

        if (especial) {
            // --- CASILLA ESPECIAL ---
            QString tipo = especial->getTipo();
            QString rutaImagen = QString(":/imagenes/%1.png").arg(tipo);
            QPixmap pixmapEspecial(rutaImagen);

            if (!pixmapEspecial.isNull()) {
                // Colocamos la imagen especial
                labelCasilla->setPixmap(pixmapEspecial.scaled(labelCasilla->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
            } else {
                // Fallback si la imagen especial no se encuentra
                labelCasilla->clear();
                labelCasilla->setStyleSheet("background-color: darkblue; border: 2px solid yellow;");
            }
        } else {
            // --- CASILLA NORMAL ---
            if (!pixmapNormal.isNull()) {
                // Colocamos la imagen base
                labelCasilla->setPixmap(pixmapNormal.scaled(labelCasilla->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
            } else {
                // Fallback si la imagen base no se encuentra
                labelCasilla->clear();
                labelCasilla->setStyleSheet("background-color: lightgray; border: 1px solid black;");
            }
        }
        // Asegurarse de que el QLabel de la ficha esté visible, no el fondo de la casilla
        labelCasilla->lower();
    }
}
