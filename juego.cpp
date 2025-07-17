#include "Juego.h"

Juego::Juego() : turnoActual(0) {}

void    Juego::agregarJugador(const QString& nombre){
    jugadores.append(jugador(nombre));
}

void Juego::iniciar(){
    turnoActual = 0;
}

int Juego::tirarDadoYAvanzar() {
    int valor = dado.tirar();
    jugadores[turnoActual].mover(valor);
    return valor;
}

bool Juego::esFinDelJuego() const {
    return jugadores[turnoActual].getPosicion() >= 63;
}

QString Juego::ganador() const {
    return jugadores[turnoActual].getNombre();
}

void Juego::pasarTurno() {
    turnoActual = (turnoActual + 1) % jugadores.size();
}

jugador& Juego::getJugadorActual() {
    return jugadores[turnoActual];
}
