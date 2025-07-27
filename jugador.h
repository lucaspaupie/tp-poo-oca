#ifndef JUGADOR_H
#define JUGADOR_H

#include <QString>

class jugador
{
private:
    QString nombre;
    int posicion;
    int turnosPenalizado;
    bool atrapado = false;
    bool repetirTurno = false;
public:
    jugador(const QString& nombre);
    void mover(int pasos);
    int getPosicion() const;
    void setPosicion(int nuevaPos); //nuevo
    QString getNombre() const;
    bool ganador() const;
    // funciones casilla posada
    void penalizar(int turnos);
    bool estaPenalizado() const;
    void restarTurnosPenalizado();
    int getTurnosPenalizados() const;
  //  bool puedeJugar() const;

    void atrapar(); //pozo
    void liberar(); //para calavera
    void retrocederACasilla(int nuevaPosicion);
    void reiniciar();
    void setRepetirTurno(bool val);
    bool getRepetirTurno() const;
    int getTurnosPenalizado() const;
    bool estaAtrapado() const;
};

#endif // JUGADOR_H
