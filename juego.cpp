#include "Juego.h"
#include <QDebug>

Juego::Juego() : turnoActual(0), miTablero(63){
   // miTablero.cargarCoordenadas();
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
/*
int Juego::tirarDadoYAvanzar() {
    int valor = dado.tirar();
  //  jugadores[turnoActual].mover(valor);   esto lo saco para probar
    miTablero.moverJugador(jugadores[turnoActual], valor);
    return valor;
}
*/
QString Juego::jugarTurno() {
    jugador& j = getJugadorActual();
    int posActual = j.getPosicion();
    int meta = miTablero.getNumCasillas() - 1; // La casilla final (ej: 63)

    int v1 = 0;
    int v2 = 0;
    int totalPasos = 0;

    QString log = j.getNombre() + " está en " + QString::number(posActual) + ". ";

    // Regla: "a partir de la casilla 60, sólo se usa un dado" [cite: 51]
    // (Asumimos que "60" es "meta - 3")
    int umbralUnDado = meta - 3;
    if (posActual >= umbralUnDado && posActual < meta) {
        v1 = dado1.tirar();
        totalPasos = v1;
        log += "Tira un dado (cerca de la meta): " + QString::number(v1) + ". ";
    } else {
        // Tiro normal con dos dados
        v1 = dado1.tirar();
        v2 = dado2.tirar();
        totalPasos = v1 + v2;
        log += "Tira dos dados: " + QString::number(v1) + " y " + QString::number(v2) + ". Total: " + QString::number(totalPasos) + ". ";
    }

    // Regla: "si se saca una suma de 9 puntos... en la casilla de salida" [cite: 48]
    if (posActual == 0 && totalPasos == 9) {
        if ((v1 == 3 && v2 == 6) || (v1 == 6 && v2 == 3)) {
            log += "¡Suma 9 (3 y 6)! Salta a la casilla 36. ";
            // Usamos setPosicion para un salto directo, no "mover"
            j.setPosicion(36);
        } else if ((v1 == 4 && v2 == 5) || (v1 == 5 && v2 == 4)) {
            log += "¡Suma 9 (4 y 5)! Salta a la casilla 54. ";
            j.setPosicion(54);
        } else {
            // Movimiento normal si saca 9 (ej: 2+7 si tuviéramos dados raros, o 4+5 en un tablero sin esa regla)
            // Por ahora, solo movemos si no es uno de esos saltos
            log += "Avanza " + QString::number(totalPasos) + ". ";
            miTablero.moverJugador(j, totalPasos);
        }
    } else {
        // Movimiento normal
        log += "Avanza " + QString::number(totalPasos) + ". ";
        miTablero.moverJugador(j, totalPasos);
    }

    // El propio moverJugador ya aplica la acción de la casilla
    // y maneja los saltos de "Oca"
    log += "Cae en " + QString::number(j.getPosicion()) + ".";

    return log;
}


bool Juego::esFinDelJuego() const {
    int meta = miTablero.getNumCasillas() - 1; // Ej: 63
    // La regla es "llegue exactamente"
    return jugadores[turnoActual].getPosicion() == meta;
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
