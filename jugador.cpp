#include "jugador.h"

jugador::jugador(const QString& nombre): nombre(nombre), posicion(0) {}

void jugador::mover(int pasos) {
    if (turnosPenalizado > 0) {
        turnosPenalizado--;
        return;
    }

    if (atrapado) return;

    if (posicion + pasos <= 63) {
        posicion += pasos;
    } else {
        int exceso = (posicion + pasos) - 63;
        posicion = 63 - exceso;
    }
}

int jugador::getPosicion() const{
    return posicion;
}
void jugador::setPosicion(int nuevaPos) { //set posicion para acomodarlo
    posicion = nuevaPos;
}
QString jugador::getNombre() const{
    return nombre;
}

bool jugador::ganador() const{
    return posicion == 63;
}

void jugador::penalizar(int turnos) {
    turnosPenalizado = turnos;
}

bool jugador::puedeJugar() const {
    return !atrapado && turnosPenalizado == 0;
}

void jugador::atrapar() {
    atrapado = true;
}

void jugador::liberar() {
    atrapado = false;
}

void jugador::retrocederACasilla(int nuevaPosicion) {
    posicion = nuevaPosicion;
}

void jugador::reiniciar() {
    posicion = 1;
}
