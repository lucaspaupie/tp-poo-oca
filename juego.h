#ifndef JUEGO_H
#define JUEGO_H

#include <QVector>
#include <QString>
#include "jugador.h"
#include "dado.h"
class Juego
{
private:
    QVector<jugador> jugadores;
    dado dado;
    int turnoActual;
public:
    Juego();
    void agregarJugador(const QString& nombre);
    void iniciar();

    int tirarDadoYAvanzar();
    void aplicarCasilla();
    bool esFinDelJuego() const;
    QString ganador() const;
    void pasarTurno();

    jugador& getJugadorActual(); // importante para reemplazar turnoActual()

};

#endif // JUEGO_H
