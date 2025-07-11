#include "casilla.h"
#include "jugador.h"

casilla::casilla(int numero) : numero(numero) {}

casilla::~casilla(){}

void casilla::accion(jugador& j){

}

int casilla::getNumero() const {
    return numero;
}
