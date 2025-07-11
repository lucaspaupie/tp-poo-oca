#include "casillaespecial.h"

casillaespecial::casillaespecial(int numero, const Qstring& tipo)
    _: casilla(numero), tipo(tipo){}


void casillaespecial::accion(jugador& j) {
    if (tipo == "puente") {
        j.mover(6); // Avanza 6 casillas mas
    } else if (tipo == "posada") {
        // Penalización: no implementada todavía en clase jugador
        // j.penalizar(1);
    } else if (tipo == "laberinto") {
        // Penalización: no implementada todavía
        // j.penalizar(2);
    }
}
