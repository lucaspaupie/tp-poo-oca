#ifndef JUGADOR_H
#define JUGADOR_H

#include <QString>

class jugador
{
private:
    QString nombre;
    int posicion;
public:
    jugador(const QString& nombre);
    void mover(int pasos);
    int getPosicion() const;
    QString getNombre() const;
    bool ganador() const;
};

#endif // JUGADOR_H
