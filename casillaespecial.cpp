#include "casillaespecial.h"
#include "jugador.h"
#include <QVector>

casillaespecial::casillaespecial(int numero, const QString& tipo)
    : casilla(numero), tipo(tipo) {}

QString casillaespecial::accion(jugador& j) {
    if (tipo == "puente") {
        j.setPosicion(12);
        return "Caíste en el puente. Avanzás a la casilla 12.";
    } else if (tipo == "posada") {
        j.penalizar(1);
        return "Caíste en la posada. Perdés un turno.";
    } else if (tipo == "pozo") {
        static jugador* atrapado = nullptr;

        if (atrapado == nullptr) {
            atrapado = &j;
            j.atrapar();
            return "Caíste en el pozo. Quedás atrapado hasta que otro jugador caiga aquí.";
        } else if (atrapado != &j) {
            atrapado->liberar();
            atrapado = &j;
            j.atrapar();
            return "Caíste en el pozo. Liberaste al jugador anterior, y ahora quedás atrapado vos.";
        } else {
            return "Seguís atrapado en el pozo.";
        }
        return "Caíste en el pozo. Quedás atrapado hasta que otro jugador caiga aquí.";
    } else if (tipo == "laberinto") {
        j.retrocederACasilla(30);
        return "Caíste en el laberinto. Retrocedés a la casilla 30.";
    } else if (tipo == "carcel") {
        j.penalizar(2);
        return "Caíste en la cárcel. Perdés 2 turnos.";
    } else if (tipo == "calavera") {
        j.reiniciar();
        return "Caíste en la calavera. Volvés al inicio.";
    } else if (tipo == "oca") {
        j.setRepetirTurno(true);
        return "Caíste en una Oca. ¡Volvé a tirar!";
    }

    return "";
}

casillaespecial::~casillaespecial() {
    // vacio, pero necesario para evitar error de vtable
}
QString casillaespecial::getTipo() const {
    return tipo;
}

int casillaespecial::siguienteOca(int posActual) {
    static QVector<int> ocas = {9, 18, 27, 36, 45, 54};
    for (int i = 0; i < ocas.size() - 1; ++i) {
        if (ocas[i] == posActual) {
            return ocas[i + 1]; // próxima oca
        }
    }
    return -1; // no hay siguiente oca
}
