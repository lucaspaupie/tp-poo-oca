#ifndef CASILLA_H
#define CASILLA_H
#include <QString>

class jugador;

class casilla
{
protected:
    int numero;
    QString tipo;
public:
    casilla(int numero);
    virtual ~casilla();

    casilla(QString tipo = "normal") : tipo(tipo) {}

    QString getTipo() const { return tipo; }
    void setTipo(const QString &nuevoTipo) { tipo = nuevoTipo; }


    virtual QString accion(jugador& j);
    int getNumero() const;
    friend QDataStream &operator<<(QDataStream &out, const casilla &c);
    friend QDataStream &operator>>(QDataStream &in, casilla &c);
};

#endif // CASILLA_H
