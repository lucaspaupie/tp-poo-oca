#include "Juego.h"
#include <QDebug>

Juego::Juego() : turnoActual(0) {
    miTablero.cargarCoordenadas();
}

void    Juego::agregarJugador(const QString& nombre){
    jugadores.append(jugador(nombre));
}

void Juego::iniciar(){
    turnoActual = 0;
    for(int i=0;i<jugadores.size();i++){
        jugadores[i].setPosicion(0);
        jugadores[i].penalizar(-jugadores[i].getTurnosPenalizados());
    }
}

int Juego::tirarDadoYAvanzar() {
    int valor = dado.tirar();
  //  jugadores[turnoActual].mover(valor);   esto lo saco para probar
    miTablero.moverJugador(jugadores[turnoActual], valor);
    return valor;
}


bool Juego::esFinDelJuego() const {
    return jugadores[turnoActual].getPosicion() >= 63;
}

QString Juego::ganador() const {
    return jugadores[turnoActual].getNombre();
}

void Juego::pasarTurno() {
    jugadores[turnoActual].restarTurnosPenalizado();

    int jugadoresTotales = jugadores.size();
    int intentos=0;
    const int max_intentos = jugadoresTotales * 2;

    // int inicioBusqueda = turnoActual;
    bool encontradoSiguienteJugador = false;

    for (int i = 0; i < jugadoresTotales; ++i) {
        turnoActual = (turnoActual + 1) % jugadoresTotales;
        if (jugadores[turnoActual].estaPenalizado()) {
            encontradoSiguienteJugador = true;
            break;
        }
    }


    if(jugadoresTotales==0){
        qDebug() <<"No hay jugadores en el juego";
        return;
    }
    do{
         turnoActual = (turnoActual + 1) % jugadores.size();
        intentos++;
         if(intentos>=max_intentos){
            break;
         }
    }while(jugadores[turnoActual].estaPenalizado());
    qDebug() << "Turno ahora para: " << jugadores[turnoActual].getNombre()
             << " en casilla " << jugadores[turnoActual].getPosicion();
}

jugador& Juego::getJugadorActual() {
    return jugadores[turnoActual];
}

jugador& Juego::getJugador(int i) {
    return jugadores[i];
}

void Juego::limpiarJugadores() {
    jugadores.clear();
    turnoActual = 0;
}
