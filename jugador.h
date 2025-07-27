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
    bool repetirTurno = false;
public:
    jugador(const QString& nombre);
    void mover(int pasos);
    int getPosicion() const;
    void setPosicion(int nuevaPos); //nuevo
    QString getNombre() const;
    bool ganador() const;
    void penalizar(int turnos);
    bool puedeJugar() const;
    void atrapar(); //pozo
    void liberar(); //para calavera
    void retrocederACasilla(int nuevaPosicion);
    void reiniciar();
    void setRepetirTurno(bool val);
    bool getRepetirTurno() const;
};

#endif // JUGADOR_H
