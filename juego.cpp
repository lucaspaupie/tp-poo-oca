#include "juego.h"

juego::juego() : turnoActual(0) {}

void    juego::agregarJugador(const QString& nombre){
    jugadores.append(jugador(nombre));
}

void juego::iniciar(){
    while (!jugadores[turnoActual].ganador()) {
        jugador& actual = jugadores[turnoActual];
        int tiro = dado.tirar();
        actual.mover(tiro);

        turnoActual = (turnoActual + 1) % jugadores.size();
    }
}
