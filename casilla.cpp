#include "casilla.h"
#include "jugador.h"
#include <QString>

casilla::casilla(int numero) : numero(numero) {}

casilla::~casilla(){}

QString casilla::accion(jugador& j) {
    Q_UNUSED(j);
    return "";
}

int casilla::getNumero() const {
    return numero;
}
