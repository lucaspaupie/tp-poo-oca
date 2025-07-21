#include "tablero.h"
#include "jugador.h"
#include "casillaespecial.h"
#include <QMap>

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
