#ifndef JUEGO_H
#define JUEGO_H

#include <QVector>
#include <QString>
#include "jugador.h"
#include "dado.h"
class Juego
{
private:
    Qvector<jugador> jugadores;
    dado dado;
    int turnoActual;
public:
    juego();
    void agregarJugador(const QString& nombre);
    void iniciar();
};

#endif // JUEGO_H
