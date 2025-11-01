#ifndef JUGADOR_H
#define JUGADOR_H

#include <QString>
#include <QJsonObject>
#include <QDataStream> // Añadido para serialización binaria

class jugador
{
private:
    QString nombre;
    int posicion;
    int turnosPenalizado=0;
    bool atrapado = false;
    bool repetirTurno = false;
public:
    jugador() = default;
    jugador(const QString& nombre);

    // Métodos de serialización JSON (texto)
    QJsonObject toJson() const;
    static jugador fromJson(const QJsonObject& json);

    // Métodos de serialización BINARIA (NUEVO)
    friend QDataStream &operator<<(QDataStream &out, const jugador &j);
    friend QDataStream &operator>>(QDataStream &in, jugador &j);

    void mover(int pasos);
    int getPosicion() const;
    void setPosicion(int nuevaPos); //nuevo
    QString getNombre() const;
    bool ganador() const;

    // funciones casilla posada
    void penalizar(int turnos);
    bool estaPenalizado();
    void restarTurnosPenalizado();

    int getTurnosPenalizados();
  //  bool puedeJugar() const;

    void atrapar(); //pozo
    void liberar(); //para calavera
    void retrocederACasilla(int nuevaPosicion);
    void reiniciar();
    void setRepetirTurno(bool val);
    bool getRepetirTurno() const;
    int getTurnosPenalizado() const;
    bool estaAtrapado() const;

    bool puedeJugar(); // <-- ¡AÑADE ESTA LÍNEA! (sin const)
};

#endif // JUGADOR_H
