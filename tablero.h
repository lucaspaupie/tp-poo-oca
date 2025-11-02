#ifndef TABLERO_H
#define TABLERO_H

#include <QVector>
#include <QPoint>
#include "casilla.h"
#include <QJsonObject>
// #include "casillaespecial.h"  quitado por el momento
// ver esto de arriba por que lo agregue y no ocupo ninguna funcion, me tira warning
class jugador;

class tablero
{
private:
    QVector<casilla*> casillas;

    QVector<QVector<QPoint>> posicionesJugadores;

    int     m_numCasillas;
    void generarCasillasEspeciales(); // <-- NUEVA: Función privada
public:
    // MODIFICADO: Acepta el número máximo de la casilla (ej: 63 o 90)
    tablero(int numCasillasMaximas=63);
    ~tablero();

    void aplicarAccion(jugador& j);
    QString moverJugador(jugador& j, int pasos);
    QPoint getCoordenadaCasilla(int casilla, int jugadorID = 0); // Coordenada para X jugador
    void cargarCoordenadas();
    casilla* getCasilla(int numero); //obtener casilla por su numero
    int getNumCasillas() const { return m_numCasillas; }
    void setNumCasillas(int n);
    QJsonObject toJson() const; //
    static tablero* fromJson(const QJsonObject& json);
};

#endif // TABLERO_H

