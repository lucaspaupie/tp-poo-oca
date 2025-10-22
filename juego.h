#ifndef JUEGO_H
#define JUEGO_H

#include <QVector>
#include <QString>
#include "jugador.h"
#include "dado.h"
#include "tablero.h"

class Juego
{
private:
    QVector<jugador> jugadores;
    dado dado1;
    dado dado2;

    int turnoActual;
    tablero miTablero;
public:
    Juego();
    void agregarJugador(const QString& nombre);
    void iniciar();

    //int tirarDadoYAvanzar();
    QString jugarTurno();

    void aplicarCasilla();
    bool esFinDelJuego() const;
    QString ganador() const;
    void pasarTurno();
    jugador& getJugadorActual();
    jugador& getJugador(int i);
    int getCantidadJugadores() const { return jugadores.size(); }
    int getTurno() const { return turnoActual; }
    tablero* getTablero() { return &miTablero; }
    void limpiarJugadores();
};

#endif // JUEGO_H
