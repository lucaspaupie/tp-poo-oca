#include "Juego.h"
#include <QDebug>
#include <QFile>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QDataStream> // Añadido para binario
#include <QTextStream>

Juego::Juego() : turnoActual(0), t(nullptr){
   // t-> = a tableros.
}

// --- PERSISTENCIA JSON (Guardado de Configuración - Texto) ---

// --- MÉTODOS EXISTENTES ---

void Juego::agregarJugador(const QString& nombre){
    jugadores.append(jugador(nombre));
}

void Juego::iniciar(){
    turnoActual = 0;
    for(int i=0;i<jugadores.size();i++){
        jugadores[i].setPosicion(0);
        jugadores[i].penalizar(-jugadores[i].getTurnosPenalizados());
    }
}
void Juego::iniciar(int numJugadores) {
    turnoActual = 0;

    // Validar tablero
    if (!t) {
        qWarning() << "Intentando iniciar sin tablero asignado.";
        return;
    }

    // Reiniciar jugadores
    for (int i = 0; i < numJugadores && i < jugadores.size(); ++i) {
        jugadores[i].setPosicion(0);
        jugadores[i].penalizar(-jugadores[i].getTurnosPenalizados());
    }
    qDebug() << "Juego iniciado con" << numJugadores << "jugadores y"
             << t->getNumCasillas() << "casillas.";
}

QString Juego::jugarTurno() {
    jugador& j = getJugadorActual();
    int posActual = j.getPosicion();
    if (!t) return "Error: tablero no inicializado.";
    int meta = t->getNumCasillas()  ; // La casilla final (ej: 63)

    int v1 = 0;
    int v2 = 0;
    int totalPasos = 0;

    QString log = j.getNombre() + " está en " + QString::number(posActual) + ". ";

    // Regla: "a partir de la casilla 60, sólo se usa un dado" [cite: 51]
    // (Asumimos que "60" es "meta - 3")
    int umbralUnDado = meta - 3;
    if (posActual >= umbralUnDado && posActual < meta) {
        v1 = dado1.tirar();
        totalPasos = v1;
        log += "Tira un dado (cerca de la meta): " + QString::number(v1) + ". ";
    } else {
        // Tiro normal con dos dados
        v1 = dado1.tirar();
        v2 = dado2.tirar();
        totalPasos = v1 + v2;
        log += "Tira dos dados: " + QString::number(v1) + " y " + QString::number(v2) + ". Total: " + QString::number(totalPasos) + ". ";
    }

    // Regla: "si se saca una suma de 9 puntos... en la casilla de salida" [cite: 48]
    if (posActual == 0 && totalPasos == 9) {
        if ((v1 == 3 && v2 == 6) || (v1 == 6 && v2 == 3)) {
            log += "¡Suma 9 (3 y 6)! Salta a la casilla 36. ";
            // Usamos setPosicion para un salto directo, no "mover"
            j.setPosicion(36);
        } else if ((v1 == 4 && v2 == 5) || (v1 == 5 && v2 == 4)) {
            log += "¡Suma 9 (4 y 5)! Salta a la casilla 54. ";
            j.setPosicion(54);
        } else {
            // Movimiento normal si saca 9 (ej: 2+7 si tuviéramos dados raros, o 4+5 en un tablero sin esa regla)
            // Por ahora, solo movemos si no es uno de esos saltos
            log += "Avanza " + QString::number(totalPasos) + ". ";
            if (!t) return "Error: tablero no inicializado.";
            t->moverJugador(j, totalPasos);
        }
    } else {
        // Movimiento normal
        log += "Avanza " + QString::number(totalPasos) + ". ";
        if (!t) return "Error: tablero no inicializado.";
        t->moverJugador(j, totalPasos);
    }

    // El propio moverJugador ya aplica la acción de la casilla
    // y maneja los saltos de "Oca"
    log += "Cae en " + QString::number(j.getPosicion()) + ".";

    return log;
}

bool Juego::esFinDelJuego() const {
    if (!t) return "Error: tablero no inicializado.";
    int meta = t->getNumCasillas(); // Ej: 63
    // La regla es "llegue exactamente"
    return jugadores[turnoActual].getPosicion() == meta;
}

QString Juego::ganador() const {
    if (esFinDelJuego()) {
        return jugadores[turnoActual].getNombre();
    }
    return QString();
}

void Juego::pasarTurno() {
    jugadores[turnoActual].restarTurnosPenalizado();

    int jugadoresTotales = jugadores.size();
    if(jugadoresTotales==0){
        qDebug() <<"No hay jugadores en el juego";
        return;
    }

    int inicioTurno = turnoActual;
    int intentos = 0;

    do {
        turnoActual = (turnoActual + 1) % jugadoresTotales;

        intentos++;
        if (intentos > jugadoresTotales) {
            qDebug() << "Advertencia: Todos los jugadores están inhabilitados. No se puede pasar el turno.";
            turnoActual = inicioTurno;
            return;
        }

    } while (!jugadores[turnoActual].puedeJugar());

    qDebug() << "Turno ahora para: " << jugadores[turnoActual].getNombre()
             << " en casilla " << jugadores[turnoActual].getPosicion();
}

jugador& Juego::getJugadorActual() {
    return jugadores[turnoActual];
}

jugador& Juego::getJugador(int i) {
    return jugadores[i];
}

void Juego::limpiarJugadores() {
    jugadores.clear();
    turnoActual = 0;
}

void Juego::aplicarCasilla() {
    // Implementación pendiente
}

void Juego::setTablero(tablero* t) {
    this->t = t;
}
// --- MÉTODOS DE PERSISTENCIA (BINARIO - avance de partida) ---

bool Juego::guardarPartidaBinario(const QString &nombreArchivo) {
    QFile file(nombreArchivo);
    if (!file.open(QIODevice::WriteOnly)) {
        qWarning() << "No se pudo abrir el archivo para guardar:" << file.errorString();
        return false;
    }

    QDataStream out(&file);

    // 1. Guardar el estado del juego:
    out << turnoActual;
    out << (quint32)jugadores.size(); // Cantidad de jugadores

    // 2. Guardar el estado de cada jugador:
    for (const jugador &j : jugadores) {
        out << j;
    }

    // 3. Guardar el estado del tablero:
    if (t) {
        out << true; // Indicador de que hay tablero
        out << *t;
    } else {
        out << false; // Indicador de que no hay tablero
    }

    qDebug() << "Partida guardada exitosamente en:" << nombreArchivo;
    return true;
}

bool Juego::cargarPartidaBinario(const QString &nombreArchivo) {
    QFile file(nombreArchivo);
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() << "No se pudo abrir el archivo para cargar:" << file.errorString();
        return false;
    }

    QDataStream in(&file);

    // 1. Cargar el estado del juego:
    quint32 numJugadores;
    in >> turnoActual;
    in >> numJugadores;

    // 2. Cargar el estado de cada jugador:
    jugadores.clear();
    for (quint32 i = 0; i < numJugadores; ++i) {
        jugador j;
        in >> j;
        jugadores.append(j);
    }

    // 3. Cargar el estado del tablero:
    bool tableroPresente;
    in >> tableroPresente;

    if (tableroPresente) {
        // Primero eliminamos el tablero anterior si existe
        if (t) {
            delete t;
            t = nullptr;
        }
        // Creamos un nuevo tablero y cargamos sus datos
        t = new tablero();
        in >> *t;
    } else {
        if (t) {
            delete t;
            t = nullptr;
        }
    }

    qDebug() << "Partida cargada exitosamente desde:" << nombreArchivo;
    return true;
}
