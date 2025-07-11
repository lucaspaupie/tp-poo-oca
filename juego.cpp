#include "Juego.h"

Juego::Juego() : turnoActual(0) {}

void    Juego::agregarJugador(const QString& nombre){
    jugadores.append(jugador(nombre));
}

void Juego::iniciar(){
    while (!jugadores[turnoActual].ganador()) {
        jugador& actual = jugadores[turnoActual];
        int tiro = dado.tirar();
        actual.mover(tiro);

        turnoActual = (turnoActual + 1) % jugadores.size();
    }
}
