#include "casillaespecial.h"
#include "jugador.h"

casillaespecial::casillaespecial(int numero, const QString& tipo)
    : casilla(numero), tipo(tipo) {}

void casillaespecial::accion(jugador& j) {
    if (tipo == "puente") {
        j.mover(6);
    } else if (tipo == "posada") {
        j.penalizar(1);
    } else if (tipo == "pozo") {
        j.atrapar();
    } else if (tipo == "laberinto") {
        j.retrocederACasilla(30);
    } else if (tipo == "carcel") {
        j.penalizar(2);
    } else if (tipo == "calavera") {
        j.reiniciar();
    }
}
QString casillaespecial::getTipo() const {
    return tipo;
}
