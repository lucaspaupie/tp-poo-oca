#ifndef TABLERO_H
#define TABLERO_H

#include <QVector>
#include "casilla.h"
// #include "casillaespecial.h"
// ver esto de arriba por que lo agregue y no ocupo ninguna funcion, me tira warning
class jugador;

class tablero
{
private:
    QVector<casilla*> casillas;
public:
    tablero();
    ~tablero();

    void aplicarAccion(jugador& j);
};

#endif // TABLERO_H
