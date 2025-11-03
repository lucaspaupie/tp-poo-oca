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
QDataStream &operator<<(QDataStream &out, const casilla &c) {
    // Almacena el tipo para saber qué clase restaurar (polimorfismo)
    out << c.tipo;
    out << c.numero;
    return out;
}

// Nota: El operador >> para 'casilla' base rara vez se usa directamente
// La restauración se maneja en 'casillaespecial' y 'tablero'
QDataStream &operator>>(QDataStream &in, casilla &c) {
    in >> c.tipo;
    in >> c.numero;
    return in;
}
