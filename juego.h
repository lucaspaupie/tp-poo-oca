#ifndef JUEGO_H
#define JUEGO_H

#include <QVector>
#include <QString>
#include <QJsonDocument>
#include "jugador.h"
#include "dado.h"
#include "tablero.h"

class Juego
{
private:
    tablero* t;  // usamos solo el puntero, no la versión duplicada
    QVector<jugador> jugadores;
    dado dado1;
    dado dado2;

    int turnoActual;

public:
    Juego();

    // MÉTODOS DE PERSISTENCIA (JSON - texto)
    bool guardarJuego(const QString& nombreArchivo);
    bool cargarJuego(const QString& nombreArchivo);

    // MÉTODOS DE PERSISTENCIA (BINARIO - avance de partida)
    bool guardarPartidaBinario(const QString& nombreArchivo);
    bool cargarPartidaBinario(const QString& nombreArchivo);

    void agregarJugador(const QString& nombre);
    void iniciar();                 // iniciar normal
    void iniciar(int numJugadores); // iniciar con cantidad
    QString jugarTurno();

    void aplicarCasilla();
    bool esFinDelJuego() const;
    QString ganador() const;
    void pasarTurno();
    jugador& getJugadorActual();
    jugador& getJugador(int i);
    int getCantidadJugadores() const { return jugadores.size(); }
    int getTurno() const { return turnoActual; }

    tablero* getTablero() { return t; }  //  devolvemos el puntero
    void limpiarJugadores();
    void setTablero(tablero* t);  //  para asignar el puntero

};

#endif // JUEGO_H
