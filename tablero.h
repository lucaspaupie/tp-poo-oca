#ifndef TABLERO_H
#define TABLERO_H

#include <QVector>
#include <QPoint>
#include "casilla.h"
#include "casillaespecial.h"
// ver esto de arriba por que lo agregue y no ocupo ninguna funcion, me tira warning
class jugador;

class tablero
{
private:
    QVector<casilla*> casillas;
     QVector<QVector<QPoint>> posicionesJugadores;
public:
    tablero();
    ~tablero();

    void aplicarAccion(jugador& j);
    void moverJugador(jugador& j, int pasos);
    QPoint getCoordenadaCasilla(int casilla, int jugadorID = 0); // Coordenada para X jugador
    void cargarCoordenadas();
    casilla* getCasilla(int numero); //obtener casilla por su numero
};

#endif // TABLERO_H
