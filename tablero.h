#ifndef TABLERO_H
#define TABLERO_H

#include <QVector>
#include <QPoint>
#include "casilla.h"
#include <QJsonObject>
#include <QDataStream> // <-- Asegúrate de incluir esto para QDataStream

class jugador; // Forward declaration

class tablero
{
private:
    QVector<casilla*> casillas;
    QVector<QVector<QPoint>> posicionesJugadores;
    int      m_numCasillas; // <-- Miembro privado correcto
    void generarCasillasEspeciales();

public:
    tablero(int numCasillasMaximas=63);
    ~tablero();

    void aplicarAccion(jugador& j);
    QString moverJugador(jugador& j, int pasos);
    QPoint getCoordenadaCasilla(int casilla, int jugadorID = 0);
    void cargarCoordenadas();
    casilla* getCasilla(int numero);
    int getNumCasillas() const { return m_numCasillas; }
    void setNumCasillas(int n);
    QJsonObject toJson() const;
    static tablero* fromJson(const QJsonObject& json);

    // Métodos de serialización BINARIA (Declaraciones Friend)
    // Al ser 'friend', pueden acceder a los miembros privados (m_numCasillas y casillas)
    friend QDataStream &operator<<(QDataStream &out, const tablero &t);
    friend QDataStream &operator>>(QDataStream &in, tablero &t);
};

#endif // TABLERO_H
