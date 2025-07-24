#include "tablero.h"
#include "jugador.h"
#include "casillaespecial.h"
#include <QMap>
#include "mainwindow.h"
tablero::tablero() {
    QMap<int, QString> especiales = {
        {6, "puente"},
        {19, "posada"},
        {31, "pozo"},
        {42, "laberinto"},
        {56, "carcel"},
        {58, "calavera"}
    };

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

void tablero::moverJugador(jugador& j,int pasos){
    int nuevaPos = j.getPosicion() + pasos;
    if(nuevaPos>= casillas.size()){
        nuevaPos = casillas.size()-1;
    }
    j.retrocederACasilla(nuevaPos);            // actualiza posicion del jugador
    aplicarAccion(j);

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
    // Aquí cargás las posiciones de cada jugador como ya hiciste en MainWindow

    this->posicionesJugadores[0] = {
        QPoint(120, 620), QPoint(250, 620), QPoint(320, 620),
        QPoint(390, 620), QPoint(450, 620), QPoint(520, 620),
        QPoint(600, 620), QPoint(670, 620), QPoint(720, 620),
        QPoint(800, 600), QPoint(850, 550), QPoint(880, 500),
        QPoint(910, 450), QPoint(920, 400), QPoint(950, 600),
        QPoint(940, 240), QPoint(930, 170), QPoint(890, 120),
        QPoint(800, 50),  QPoint(720, 20),  QPoint(640, 10),
        QPoint(580, 10),  QPoint(510, 10),  QPoint(450, 10),
        QPoint(380, 10),  QPoint(320, 10),  QPoint(250, 10),
        QPoint(180, 30),  QPoint(120, 70),  QPoint(130, 49),
        QPoint(40, 180),  QPoint(30, 250),  QPoint(40, 320),
        QPoint(40, 400),  QPoint(70, 470),  QPoint(160, 480),
        QPoint(210, 510), QPoint(270, 520), QPoint(320, 10),
        QPoint(390, 10),  QPoint(450, 10),  QPoint(520, 10),
        QPoint(600, 10),  QPoint(660, 10),  QPoint(720, 510),
        QPoint(780, 460), QPoint(810, 410), QPoint(820, 360),
        QPoint(820, 310), QPoint(850, 230), QPoint(780, 150),
        QPoint(720, 120), QPoint(620, 110), QPoint(530, 110),
        QPoint(450, 110), QPoint(380, 110), QPoint(310, 110),
        QPoint(240, 110), QPoint(190, 170), QPoint(140, 280),
        QPoint(200, 350), QPoint(230, 400), QPoint(270, 420),
        QPoint(490, 310)
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
};
