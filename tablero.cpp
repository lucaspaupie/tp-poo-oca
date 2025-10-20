#include "tablero.h"
#include "jugador.h"
#include "casillaespecial.h"
#include <QMap>
#include "mainwindow.h"
#include <random>   // <-- NUEVO
#include <QSet>     // <-- NUEVO (para evitar casillas duplicadas)
#include <QDebug>   // <-- NUEVO (opcional, para depurar)

tablero::tablero() {

   /* QMap<int, QString> especiales = {
        {6, "puente"},
        {9, "oca"}, {18, "oca"}, {27, "oca"}, {36, "oca"}, {45, "oca"}, {54, "oca"},
        {19, "posada"},
        {31, "pozo"},
        {42, "laberinto"},
        {56, "carcel"},
        {58, "calavera"}
    };
        */
    for (int i = 0; i < m_numCasillas; ++i) {
        casillas.append(new casilla(i));
    }

    generarCasillasEspeciales();

    cargarCoordenadas();

    for (int i = 0; i <= 63; ++i) {
        if (especiales.contains(i)) {
            casillas.append(new casillaespecial(i, especiales[i]));
        } else {
            casillas.append(new casilla(i));
        }
    }
}

tablero::~tablero() {
    qDeleteAll(casillas);
    casillas.clear();
}

void tablero::aplicarAccion(jugador& j) {
    int pos = j.getPosicion();
    if (pos >= 0 && pos < casillas.size()) {
        casillas[pos]->accion(j);
    }
}
QString tablero::moverJugador(jugador& j, int pasos) {
    int nuevaPos = j.getPosicion() + pasos;
    if (nuevaPos >= casillas.size()) {
        nuevaPos = casillas.size() - 1;
    }

    j.setPosicion(nuevaPos);

    QString mensaje = casillas[nuevaPos]->accion(j);

    // Si es una oca, saltamos automáticamente a la siguiente
    casillaespecial* especial = dynamic_cast<casillaespecial*>(casillas[nuevaPos]);
    if (especial && especial->getTipo() == "oca") {
        int siguiente = casillaespecial::siguienteOca(nuevaPos);
        if (siguiente != -1) {
            j.setPosicion(siguiente);  // Teletransporta
        }
    }
    return mensaje;
}

QPoint tablero::getCoordenadaCasilla(int casilla, int jugadorID) {
    if (jugadorID >= posicionesJugadores.size() || casilla >= posicionesJugadores[jugadorID].size())
        return QPoint(0, 0);  // fallback
    QPoint base = posicionesJugadores[0][casilla];
    switch (jugadorID) {
    case 1: return base + QPoint(15, 0);
    case 2: return base + QPoint(0, 15);
    case 3: return base + QPoint(15,15);
    default: return base;
        break;
    }
}
void tablero::cargarCoordenadas() {
    this->posicionesJugadores.resize(1);

    this->posicionesJugadores[0].resize(m_numCasillas);

    // Generamos coordenadas "dummy" solo para que funcione
    // Esto creará una simple línea recta

    for (int i = 0; i < m_numCasillas; ++i) {
        this->posicionesJugadores[0][i] = QPoint(10 + (i * 10), 300);
    }

    /*this->posicionesJugadores[0] = {
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
    */
    };



    /*
    // Copiá la misma para los demás con desplazamiento si querés
    for (int j = 1; j < 4; ++j) {
        for (int i = 0; i < 64; ++i) {
            QPoint base = posicionesJugadores[0][i];
            posicionesJugadores[j].append(QPoint(base.x() + j*10, base.y() + j*10)); // pequeño offset
        }
    }
}


QPoint tablero::getCoordenadaCasilla(int casilla, int jugadorID) {
    return posicionesJugadores[jugadorID][casilla];
}*/
}

casilla* tablero::getCasilla(int numero){
    if(numero>=0 && numero < casillas.size()){
        return casillas[numero];
    }
    return nullptr;
}


void tablero::generarCasillasEspeciales() {

    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution<> dis(1, m_numCasillas - 2);
    QSet<int> posicionesUsadas;

    // Hacemos que sea proporcional al tamaño del tablero
    int numOcas = m_numCasillas / 10;     // Ej: 64/10 = 6 ocas
    int numPuentes = m_numCasillas / 30;  // Ej: 64/30 = 2 puentes
    int numPozos = 1;
    int numPosadas = 1;
    int numLaberintos = 1;
    int numCarceles = 1;
    int numCalaveras = 1;

    // --- Función auxiliar (Lambda) para plantar una casilla ---
    // Esto es para no repetir código. Captura 'dis', 'gen', y 'posicionesUsadas'
    auto plantarEspecial = [&](const QString& tipo) {
        int pos;
        do {
            pos = dis(gen); // Elige un número al azar
        } while (posicionesUsadas.contains(pos)); // Si ya está usado, elige otro

        posicionesUsadas.insert(pos); // Marca la posición como usada

        // ¡IMPORTANTE! Borramos la casilla normal ANTES de reemplazarla
        delete casillas[pos];

        // Creamos y asignamos la nueva casilla especial
        casillas[pos] = new casillaespecial(pos, tipo);

       // qDebug() << "Generada casilla" << tipo << "en" << pos; // Para depurar
    };

    // --- Plantamos las casillas --- [cite: 31, 33]
    for (int i = 0; i < numOcas; ++i) {
        plantarEspecial("oca");
    }
    for (int i = 0; i < numPuentes; ++i) {
        plantarEspecial("puente");
    }
    plantarEspecial("posada");
    plantarEspecial("pozo");
    plantarEspecial("laberinto");
    plantarEspecial("carcel");
    plantarEspecial("calavera");
}
