#include "Juego.h"
#include <QDebug>
#include <QFile>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QDataStream> // Añadido para binario

Juego::Juego() : turnoActual(0), miTablero(63){
   // miTablero.cargarCoordenadas();
}

// --- PERSISTENCIA BINARIA (Guardado de Partida) ---

bool Juego::guardarPartidaBinario(const QString& nombreArchivo) {
    QFile saveFile(nombreArchivo);
    // Abrir en modo escritura, binario
    if (!saveFile.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        qWarning("No se pudo abrir el archivo binario para escribir.");
        return false;
    }

    QDataStream out(&saveFile);
    // Establecer una versión para el stream, vital para la compatibilidad futura
    out.setVersion(QDataStream::Qt_6_0);

    // 1. Guardar turno actual
    out << turnoActual;

    // 2. Guardar cantidad de jugadores y luego cada jugador
    out << jugadores.size();
    for (const jugador& j : jugadores) {
        out << j; // Usa el operador<< implementado en jugador.cpp
    }

    saveFile.close();
    qDebug() << "Partida guardada binariamente en:" << nombreArchivo;
    return true;
}

bool Juego::cargarPartidaBinario(const QString& nombreArchivo) {
    QFile loadFile(nombreArchivo);
    // Abrir en modo lectura, binario
    if (!loadFile.open(QIODevice::ReadOnly)) {
        qWarning("No se pudo abrir el archivo binario para leer.");
        return false;
    }

    QDataStream in(&loadFile);
    // Establecer la misma versión
    in.setVersion(QDataStream::Qt_6_0);

    // Variables de carga
    int loadedTurnoActual = 0;
    int numJugadores = 0;
    QVector<jugador> loadedJugadores;

    // 1. Cargar turno actual
    in >> loadedTurnoActual;

    // 2. Cargar cantidad de jugadores
    in >> numJugadores;

    // 3. Cargar cada jugador
    for (int i = 0; i < numJugadores; ++i) {
        jugador j("Temp"); // Se inicializa con un nombre temporal
        in >> j; // Usa el operador>> implementado en jugador.cpp
        loadedJugadores.append(j);
    }

    // 4. Aplicar el estado cargado SÓLO si la carga fue exitosa
    if (in.status() == QDataStream::Ok) {
        jugadores = loadedJugadores;
        turnoActual = loadedTurnoActual;
        loadFile.close();
        qDebug() << "Partida cargada binariamente exitosamente desde:" << nombreArchivo;
        return true;
    } else {
        qWarning("Error durante la lectura del archivo binario.");
        loadFile.close();
        return false;
    }
}

// --- PERSISTENCIA JSON (Guardado de Configuración - Texto) ---

bool Juego::guardarJuego(const QString& nombreArchivo) {
    QJsonObject juegoJson;

    // 1. Guardar turno actual
    juegoJson["turnoActual"] = turnoActual;

    // 2. Guardar jugadores
    QJsonArray jugadoresArray;
    for (const jugador& j : jugadores) {
        jugadoresArray.append(j.toJson());
    }
    juegoJson["jugadores"] = jugadoresArray;

    // 3. Escribir al archivo
    QFile saveFile(nombreArchivo);
    if (!saveFile.open(QIODevice::WriteOnly)) {
        qWarning("No se pudo abrir el archivo para escribir.");
        return false;
    }

    QJsonDocument saveDoc(juegoJson);
    saveFile.write(saveDoc.toJson(QJsonDocument::Indented));
    saveFile.close();
    qDebug() << "Configuración guardada en:" << nombreArchivo;
    return true;
}

bool Juego::cargarJuego(const QString& nombreArchivo) {
    QFile loadFile(nombreArchivo);

    if (!loadFile.open(QIODevice::ReadOnly)) {
        qWarning("No se pudo abrir el archivo para leer.");
        return false;
    }

    QByteArray saveData = loadFile.readAll();
    QJsonDocument loadDoc(QJsonDocument::fromJson(saveData));

    if (loadDoc.isNull()) {
        qWarning("El archivo no es un JSON válido.");
        return false;
    }

    QJsonObject juegoJson = loadDoc.object();

    if (juegoJson.contains("turnoActual") && juegoJson["turnoActual"].isDouble()) {
        turnoActual = juegoJson["turnoActual"].toInt();
    } else {
        qWarning("Datos de turnoActual faltantes o inválidos.");
        return false;
    }

    if (juegoJson.contains("jugadores") && juegoJson["jugadores"].isArray()) {
        jugadores.clear();
        QJsonArray jugadoresArray = juegoJson["jugadores"].toArray();
        for (const QJsonValue& value : jugadoresArray) {
            jugadores.append(jugador::fromJson(value.toObject()));
        }
    } else {
        qWarning("Datos de jugadores faltantes o inválidos.");
        return false;
    }

    qDebug() << "Configuración cargada exitosamente desde:" << nombreArchivo;
    return true;
}

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
/*
int Juego::tirarDadoYAvanzar() {
    int valor = dado.tirar();
    miTablero.moverJugador(jugadores[turnoActual], valor);
    return valor;
}
*/
QString Juego::jugarTurno() {
    jugador& j = getJugadorActual();
    int posActual = j.getPosicion();
    int meta = miTablero.getNumCasillas() - 1; // La casilla final (ej: 63)

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
            miTablero.moverJugador(j, totalPasos);
        }
    } else {
        // Movimiento normal
        log += "Avanza " + QString::number(totalPasos) + ". ";
        miTablero.moverJugador(j, totalPasos);
    }

    // El propio moverJugador ya aplica la acción de la casilla
    // y maneja los saltos de "Oca"
    log += "Cae en " + QString::number(j.getPosicion()) + ".";

    return log;
}

bool Juego::esFinDelJuego() const {
    int meta = miTablero.getNumCasillas() - 1; // Ej: 63
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
