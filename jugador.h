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
    void setPosicion(int nuevaPos); //nuevo
    QString getNombre() const;
    bool ganador() const;
    void penalizar(int turnos);
    bool puedeJugar() const;
    void atrapar(); //pozo
    void liberar(); //para calavera
    void retrocederACasilla(int nuevaPosicion);
    void reiniciar();
};

#endif // JUGADOR_H
