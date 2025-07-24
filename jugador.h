#ifndef JUGADOR_H
#define JUGADOR_H

#include <QString>

class jugador
{
private:
    QString nombre;
    int posicion;
    int turnosPenalizado = 0;
    bool atrapado = false;
public:
    jugador(const QString& nombre);
    void mover(int pasos);
    int getPosicion() const;
    QString getNombre() const;
    bool ganador() const;
    void penalizar(int turnos);
    bool puedeJugar() const;
    void atrapar();
    void liberar();
    void retrocederACasilla(int nuevaPosicion);
    void reiniciar();
    void setPosicion(int nuevaPos);
};

#endif // JUGADOR_H
